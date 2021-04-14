# Final-Project-
Final Project for CS 207

Solar Tracker 
=============
By: Nathan Montgomery 

What is a Solar Tracker?
========================


  Well to begin a solar tracker is an automated solar panel that will be able to follow the sun along its path during the day.  Automated solar panels could help increase the voltage output of the panels by creating a face on view of the sun during the whole day. So long as you can use energy efficient motors to move the structure it could essentially power itself. 
  
  Initially I wanted to create a solar tracker that could follow the sun, read out wind speed, record temperature and relate its position, and charge its own batteries (Basically an autonomous weather station with solar panels). I had a few setbacks this semester with family issues and ordering parts within the timeline but I was able to create a solar tracker that follows a light sources path, records the panel’s position, and read out the value at which the solar panels are producing voltage and the temperature around the unit.  

  Starting off I want to give credit to Ingeimaks on Arduino project hub https://create.arduino.cc/projecthub/Ingeimaks/diy-solar-tracker-arduino-project-ita-78ad78 
The initial project shows a solar tracker that follows the sun.  Most of my project was based off the initial starting code Ingeimaks provided for their project.  Although my code differs greatly from the initial project I followed their code and all credit goes to them for the initial idea.  
Basically my solar tracker was attempted to be an improved version of Ingeimaks solar tracker; 

To implement my LCD screen I used code from an open source Arduino page https://www.arduino.cc/en/Tutorial/LibraryExamples/HelloWorld 
This page demonstrates how to connect the LCD to the arduino using 6 pins.
The code for the pinouts and how to wire the LCD were followed and adjust so that the LCD would read out the temerature from the LM36 temperature sensor and the voltage from the solar panels. 

![alt text](https://github.com/Montgomery51/Final-Project-/blob/main/img/Final%20Build.jpg  "Final Build")


Hardware 
========
* 1 x Arduino UNO
* 1 x Breadboard (or prototype boards and solder - Used in this project)
* 4 x PhotoResistors 
* 4 x 10k ohm Resistors 
* 1 x 220 ohm Resistor
* 1 x TMP36 Temperature Sensor 
* 2 x Servo motor (Bigger is Better! But not needed)
* 1 x 16 PIN LCD Screen 
* 1 x 10k ohm Potentiometer 
* Solar Panel (Salvaged or new)
* Wire for connections 
* External power supply ... I used a 20v Dewalt battery with an adapter connected to a buck converter (Worked Awesomely good) 
-----------------------
* For The base.... I created my base with a piece of wood, two scrap hinges for a shelf, and I found an old pan / tilt servo bracket with pieces missing....But i made it work 
* The base was supposed to be 3D printed but the 3D printer I had access to decided to melt everything and try to light on fire instead of building my base.... So the base you see in the above picture is what was built. 
-----------------------
Links to find this hardware 
-----------------------
* DeWalt Battery - https://www.amazon.ca/DEWALT-DCB201-Li-Ion-Compact-Battery/dp/B0052MIN3W/ref=sr_1_4?dchild=1&keywords=DeWalt+20v+1.5ah+battery&qid=1618267814&s=hi&sr=1-4  (Not needed to use this same power supply but it is what I had)

* Buck Converter - https://www.amazon.ca/gp/product/B07ZSHT1TZ/ref=ppx_yo_dt_b_asin_title_o02_s01?ie=UTF8&psc=1 (The LCD display shows voltage in/out and current - Pretty cool)

* Battery Adapter - https://www.amazon.ca/gp/product/B08B1GLBCV/ref=ppx_yo_dt_b_asin_title_o02_s01?ie=UTF8&psc=1 (awesome adapter for DeWalt batteries)

* 3 Pack Uno - https://www.amazon.ca/CANADUINO-ATmega328P-Module-Compatible-Arduino/dp/B07ZQQLDD9/ref=sr_1_7?dchild=1&keywords=Arduino+uno&qid=1618267950&sr=8-7

* 16 Pin LCD - https://www.amazon.ca/Character-Backlight-Raspberry-Electrical-Internet/dp/B07S7PJYM6/ref=sr_1_15?dchild=1&keywords=16+pin+LCD&qid=1618267979&sr=8-15

* TMP 36 Temp Sensor - https://www.digikey.ca/en/products/detail/analog-devices-inc/TMP36GT9Z/820404 

* LongRunner Servo motor - https://www.amazon.ca/gp/product/B01N6C66ZG/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1   
(These are kinda small for a project like this but it worked)

* PhotoResistor - https://www.adafruit.com/product/161      (I salvaged mine from nightlights I bought from the dollar store)

Wiring
=======
----------------------------
![alt text](https://github.com/Montgomery51/Final-Project-/blob/main/img/Final_SolarTrack_Schematic_V2.jpg "Wiring Diagram Picture")
Wiring diagram picture 
----------------------------
I always find these pictures to be really nice to read when trying out a new project, but also i have created a wiring diagram as well as seen below.
![alt text](https://github.com/Montgomery51/Final-Project-/blob/main/img/Final_SolarTrack_Schematic_schem.jpg "Wiring Diagram")
----------------------------
Software
========

The code I used initially was provided by Ingeimaks (I highly recommend 






Starting off I smoothed out the code by mapping the values from 0-50 and error checking the photo resistors-

-Original Ingeimaks Code for checking Lights Position-
```bash
 //Ingeimaks
#include <Servo.h>
//definiamo i servomotori orizzontale e verticale
Servo servohori;
int servoh = 0;
int servohLimitHigh = 160;
int servohLimitLow = 60;

Servo servoverti; 
int servov = 0; 
int servovLimitHigh = 160;
int servovLimitLow = 60;
//Pin fotoresistenze
int ldrtopl = 2; //top left 
int ldrtopr = 1; //top right 
int ldrbotl = 3; // bottom left 
int ldrbotr = 0; // bottom right 

 void setup () 
 {
  servohori.attach(10);
  servohori.write(60);
  servoverti.attach(9);
  servoverti.write(60);
  Serial.begin(9600);
  delay(500);
  
 }

void loop()
{
  servoh = servohori.read();
  servov = servoverti.read();
  //Valore Analogico delle fotoresistenza
  int topl = analogRead(ldrtopl);
  int topr = analogRead(ldrtopr);
  int botl = analogRead(ldrbotl);
  int botr = analogRead(ldrbotr);
  // Calcoliamo una Media
  int avgtop = (topl + topr) ; //average of top 
  int avgbot = (botl + botr) ; //average of bottom 
  int avgleft = (topl + botl) ; //average of left 
  int avgright = (topr + botr) ; //average of right 

  if (avgtop < avgbot)
  {
    servoverti.write(servov +1);
    if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
    delay(10);
  }
  else if (avgbot < avgtop)
  {
    servoverti.write(servov -1);
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
    delay(10);
  }
  else 
  {
    servoverti.write(servov);
  }
  
  if (avgleft > avgright)
  {
    servohori.write(servoh +1);
    if (servoh > servohLimitHigh)
    {
    servoh = servohLimitHigh;
    }
    delay(10);
  }
  else if (avgright > avgleft)
  {
    servohori.write(servoh -1);
    if (servoh < servohLimitLow)
     {
     servoh = servohLimitLow;
     }
    delay(10);
  }
  else 
  {
    servohori.write(servoh);
  }
  delay(50);
}
```

