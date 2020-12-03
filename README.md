# ECE4180_Project

/*

Attach brief description of project. 

*/

## Circuit 

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
