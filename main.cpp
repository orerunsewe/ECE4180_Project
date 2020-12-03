/*Kehinde Williams and Oreoluwa Runsewe ECE 4180 final project*/
//Mbed side: Home security system featuring an HC-04 sensor, uLCD, speaker, and I2C touch pad
#include "mbed.h"
#include "wave_player.h"
#include "uLCD_4DGL.h"
#include "rtos.h"
#include "SDFileSystem.h"
#include "ultrasonic.h"
#include "SongPlayer.h"
#include "Speaker.h"
#include <mpr121.h>
#define CODELENGTH 6 //Length of passcode to deactivate the alarm * 2. Needed because of the nature of the FallInterrupt routine call

//Set up SD card
SDFileSystem sd(p5, p6, p7, p8, "sd");
PwmOut speaker(p21);
//Speaker NotePlayer(p21);
//Setup I/O pins
//LED1-4 to display the code entered
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
//LED to signal alarm has been triggered
DigitalOut myLED(p20);

//Setup Mpr121 interrupt on p26
InterruptIn interrupt(p26);

//Setup I2C and MPR122
I2C i2c(p28,p27);
Mpr121 mpr121(&i2c, Mpr121::ADD_VSS);

//configure serial: For communication with Pi
Serial pc(USBTX,USBRX,9600);
uLCD_4DGL uLCD(p13,p14,p11); // serial tx, serial rx, reset pin;

//Global Variables:
int codeCounter;
int inputCode[CODELENGTH];
bool alarm = false;
int sonar_dist;

void playtone(){
    int i;
     for (i=0; i<26; i=i+2) {
        speaker.period(1.0/969.0);
        speaker = float(i)/50.0;
        wait(.001);
        speaker.period(1.0/800.0);
        wait(.001);
    }
// decrease volume
    for (i=25; i>=0; i=i-2) {
        speaker.period(1.0/969.0);
        speaker = float(i)/50.0;
        wait(.001);
        speaker.period(1.0/800.0);
        wait(.001);
    }

}

void dist(int distance)
{
    //put code here to execute when the distance has changed
    //mu.checkDistance();

}
ultrasonic mu(p18, p23, .1, 1, &dist);

//This thread checks the distance and sets the alarm to true if it is out of a certain range
//Start from 1 because the sensor starts from 0 on setup. Highest val is about 50 so use 30 as max safe
void dist_thread()
{
    while(1)
    {
        mu.startUpdates();
        mu.checkDistance();
        sonar_dist = mu.getCurrentDistance();
        pc.printf("Distance %d mm\r\n", sonar_dist); //Print to serial

        if(sonar_dist>1&& sonar_dist < 30)
        {
            alarm = true;

        }

        Thread::wait(700);
    }
}

//This function  checks if the alarm is set to true. If yes, it saves key presses into an array
void fallInterrupt()
{

    int key_code=0;
    int i=0;
    int value=http://mpr121.read(0x00);
    value +=http://mpr121.read(0x01)<<8;
    i=0;
    // puts key number out to LEDs for demo
    for (i=0; i<12; i++)
    {
        if (((value>>i)&0x01)==1) key_code=i+1;
    }
    led4=key_code & 0x01;
    led3=(key_code>>1) & 0x01;
    led2=(key_code>>2) & 0x01;
    led1=(key_code>>3) & 0x01;

//logic from referenced project
    if(alarm == true)
    {
        if(codeCounter < CODELENGTH)
        {
            // ignore odd numbers
            if(codeCounter % 2 != 0)
            {
                inputCode[codeCounter] = 0;
            }
            // only save the even numbers (see lines 6-10)
            else
            {
                inputCode[codeCounter] = key_code - 1;
            }
            codeCounter++;
        }
    }

}

//Function to check if the code entered is correct
bool code_check(int (&codeArr)[CODELENGTH])
{

    int j = 0;
    int k = 0;

    for(j = 0; j<CODELENGTH; j+=2)
    {
        if(inputCode[j] == codeArr[j])
        {
            k++;
        }
    }
    if(k == CODELENGTH/2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//The main thread checks the alarm boolean and takes the required action
int main()
{

    int passcode[CODELENGTH] = {1,0,2,0,8,0}; //Arbitrary passcode
    bool pass = false;
    while(1)
    {

        Thread thread1(dist_thread); //attach the distance checking thread
      //  Thread thread2(alarm_sound);
        pass = code_check(passcode);

//Conditions to execute if the alarm flag is true
        if(alarm == true)
        {
            playtone();
            interrupt.fall(&fallInterrupt);
            interrupt.mode(PullUp);
            myLED=1;
            uLCD.locate(0,1);
            uLCD.cls();
            uLCD.printf("Passcode: ");

        }

        //Check if the code entered is right
        if(pass == true)
        {
            alarm = false;
            codeCounter = 0;

            //reset
            for(int i =0; i<CODELENGTH; i++)
            {
                inputCode[i] = 0;
            }
        }

        //Once the key code is correctle entered and Alarm flag is reset:
        if(alarm == false)
        {
            speaker =0.0;
            myLED = 0;
            pass = false;
            uLCD.locate(0,1);
            uLCD.cls();
            uLCD.printf("Alarm Disabled                 ");

        Thread :: wait(100);
    }
}
}
