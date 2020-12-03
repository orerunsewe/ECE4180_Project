# ECE4180_Project

This project uses C++, Python and Flask to implement a model security system on an mbed LPC1768 and a Raspberry Pi. 

## Circuit 

I/O Devices: 
HC_SR04, MPR121 I2C Capacitive Touch Sensor are used for inputs. 
uLCD, TPA2005D1 Class D Audio Amp, Speaker and LED are all outputs of the mbed. 


The following table shows the pin connections used in this project:

|    mbed LPC1768   | uLCD | HC_SR04 | TPA2005D1 Class D Audio Amp | Speaker | MPR121 I2C Capacitive Touch Sensor | LED |
|:-----------------:|:----:|:-------:|:---------------------------:|:-------:|:----------------------------------:|:---:|
| Vout (3.3V or 5V) |  Vcc |   Vcc   |            PWR+             |         |                 Vcc                |     |
|        gnd        |  gnd |   gnd   |          PWR-, IN-          |         |                 gnd                |  -  |
|      RX - p14     |  TX  |         |                             |         |                                    |     |
|      TX - p13     |  RX  |         |                             |         |                                    |     |
|        p11        |  RST |         |                             |         |                                    |     |
|        p18        |      |   TRIG  |                             |         |                                    |     |
|        p23        |      |   ECHO  |                             |         |                                    |     |
|                   |      |         |             IN+             |         |                                    |     |
|                   |      |         |            OUT+             |    +    |                                    |     |
|                   |      |         |             OUT-            |    -    |                                    |     |
|        p26        |      |         |                             |         |                 IRQ                |     |
|        p28        |      |         |                             |         |                 SDA                |     |
|        p27        |      |         |                             |         |                 SCL                |     |
|        p20        |      |         |                             |         |                                    |  +  |


## mbed-Pi Communication 

mbed communicates with the Raspberry Pi via the mbed's virtual USB COM port with a baud rate of 9600 baud. 

## Web Server 

The webserver is hosted on localhost using the Flask framework on Python. See the file serialTemplate.py and main.html in the code section. 

## Schematic

Below is a link to a block diagram showing the component connections. 

![schematic](https://github.com/orerunsewe/ECE4180_Project/blob/master/Schematic.png?raw=true)

## References 
1. https://t.co/81FpWMtOCY?amp=1
2. https://t.co/ErXhpnJ2jv?amp=1
3. https://t.co/Bbxd6nq9ZM?amp=1
