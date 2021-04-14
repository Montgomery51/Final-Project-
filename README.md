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

* PhotoResistor - https://www.adafruit.com/product/161      (I salvaged mine from nightlights I bought from the dollar store but that is an expesive route)

*Pan/tilt for small servos - https://www.amazon.ca/gp/product/B07HQB95VY/ref=ox_sc_act_title_2?smid=A2YPMGYKJIIDP8&psc=1 


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
If you are going to put this onto an Arduino device I would recommend downloading the Arduino IDE here - https://www.arduino.cc/en/software 

Libraries
---------
My libraries were already isntalled when I got the Arduino IDE but to find these libraries (if you dont have them) you click the tools option on the top toolbar and then manage libraries... Once it pops up you can search LCD for the liquid crystal library and install it and also search for "Servo" and you will be able to download that library.  

```bash
#include <Servo.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
```

The code I used initially was provided by Ingeimaks (I highly recommend checking out their page https://create.arduino.cc/projecthub/Ingeimaks/diy-solar-tracker-arduino-project-ita-78ad78 ) they made a beautiful 3D printed base for their tracker. 

My Code For My Solar Tracker Station 
====================
```bash
#include <Servo.h> // Servo library 
#include <LiquidCrystal.h>
#include <EEPROM.h>

Servo Hori;  //Horizontal and Vertical Servos for tracking 
Servo Verti;

const int LightReadOut0= A0;
const int LightReadOut1= A1;
const int LightReadOut2= A2;
const int LightReadOut3= A3;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int VoltReadOut = A4;  // analog pins for analog values 
const int TempReadOut = A5;

int LightValue0 = 0; //Light variables 
int LightValue1 = 0;
int LightValue2 = 0;
int LightValue3 = 0;

int VoltageValue = 0; // variables 
int TempValue = 0;

int TopDiff = 0;  //Average checking variables 
int BotDiff = 0;
int LeftDiff = 0;
int RightDiff = 0;
int pHori = 180;
int pVerti = 180;

void setup() {
  
  EEPROM.get(0, pVerti);  // Position tracking with EEPROM 
  EEPROM.get(2, pHori);
  Hori.attach(9);      // Pin 9 to horizontal servo 
  Hori.write (pHori);  //Takes EEPROM Value and writes it to servo 
  Verti.attach(10);    // Pin 10 for vertical 
  Verti.write(pVerti);  //Takes EEPROM Value and writes it to servo
  lcd.begin(16, 2);    //Starts LCD 
  delay(500); //Startup Delay so everything warms up!
  Serial.begin(9600);
}

void loop() {

  VoltageValue = analogRead(VoltReadOut);
  TempValue = analogRead(TempReadOut);

  VoltageValue -= 190;    // This value was needed to correct the value of the solar panels on my unit 
                          // When testing with a digital mutimeter the reading was off by about 1.5 volts 
                          //After testing mutiple values I found this value of 190 to provide the correct results
                          
//  Serial.print("VOLTAGE =");      //Testing for voltage 
//  Serial.println(VoltageValue);
//  delay(2000);

  float Voltage = 5.0 * (VoltageValue/1023.0);  //voltage value is analog input 0-1023 so input/1023 == % * 5V  = Voltage
  float tempC = 5.0 * (TempValue/1023.0);
  tempC = tempC * 100 - 50;

  Serial.print("VOLTAGE =");      
  Serial.println(Voltage);
  // Cursor set for top row and Panel voltage reading 
  lcd.setCursor(0, 0);
  lcd.print("SolarPanel ");
  lcd.print(Voltage);
  lcd.print("V");
  // Cursor set for bottom row and temp reading 
  lcd.setCursor(0, 1);
  lcd.print("Temp C = ");
  lcd.print(tempC);
  lcd.print("C");
  
// Setting variable to the value obtained by the analog pin
  LightValue0 = analogRead(LightReadOut0);          
  LightValue1 = analogRead(LightReadOut1);         
  LightValue2 = analogRead(LightReadOut2);          
  LightValue3 = analogRead(LightReadOut3);   
         
//Mapping the photoresistors value for easier math and readout 
//**Comments below are when looking directly at front of Tracker**
  int TopL = map(LightValue0, 0, 1023, 0, 50);     //Top Left PhotoSensor 
  int BotL = map(LightValue1, 0, 1023, 0, 50);    //Bot Left PhotoSensor
  int TopR = map(LightValue2, 0, 1023, 0, 50);   //Top Right PhotoSensor
  int BotR = map(LightValue3, 0, 1023, 0, 50);  //Bot Right PhotoSensor

  int TopDiff = (TopR + TopL) - (BotR + BotL);  //Total averages for total top and total bot 
  int BotDiff = (BotR + BotL) - (TopR + TopL);
  int LeftDiff = (TopL + BotL) - (TopR + BotR);
  int RightDiff = (TopR + BotR) - (TopL + BotL);
  
  if (TopDiff > 3 && pVerti != 75)  // checks to see if top is bigger than bottom and that its not higher than max hieght 
  {
    pVerti -= 1;
    Verti.write(pVerti); 
  }

  if (BotDiff > 3 && pVerti != 155)  //Checks for bottom brightness and max depth 
  {
    pVerti += 1;
    Verti.write(pVerti); 
  }

  if (RightDiff > 3 && pHori != 180) //Checks right side for brightness and to see if its max west 
  {
    pHori += 1;
    Hori.write(pHori);
  }

   if (LeftDiff > 3 && pHori != 0) //Checks Left side for brightness and to see if its max East 
  {
    pHori -= 1;
    Hori.write(pHori);
  }

    if (pHori < 15 && Voltage < 0.5)   //Check if nightime and pointing west 
  {
    for(int i = 0; i < 180; i++)    // RESET for nightime once power levels drop and the unit is facing west 
    {                                 // it will reposition to the east (morning)
      pHori += 1;
      Hori.write(pHori);
      delay(50);
    }
    EEPROM.put(2, pHori);
  }

  while (Voltage < 0.5)   //SYstem will shut down if the solar panels are not getting enough juice 
  {
    VoltageValue = analogRead(VoltReadOut);  // will check for juice levels 
    VoltageValue -= 190;
    Voltage = 5.0 * (VoltageValue/1023.0);
  }

  EEPROM.put(0, pVerti);   //stores position in the EEPROM  just in case system is reset it wont fly to another position.
  EEPROM.put(2, pHori);

//  Serial.print("Horizon =");      // printing values of horizon and vertical servo's **For testing max values**
//  Serial.println(pHori);
//  Serial.print("Vertical =");      
//  Serial.println(pVerti);
//  delay(100);

//Print for light sensor value and sight value 0-50 
  Serial.print("Light sensor top left =");      
  Serial.println(TopL);
  Serial.print("Light sensor Bottom Left =");       
  Serial.println(BotL);
  Serial.print("Light sensor Top Right =");      
  Serial.println(TopR);
  Serial.print("Light sensor Bottom Right =");     
  Serial.println(BotR);
  Serial.println(" ");
  //delay(2000);
  
}
```
---------------------------------------------------------------
How To
======
* IF you followed the wiring diagram correctly and built the unit with the servo's wired in the proper orientation! (if not just switch their dtaa wires) 
* IF everything is grounded 
* IF everything is properly secured down 
* IF the world has not yet ended 
* You may now hook up the Arduino and upload the code!

* Once the code is loaded....sit back and enjoy all the solar tracking goodness! 
* Seriously it should totally work now.... 
* If not I suggest checking all the connections and greound wires 
* Also if using those fun little jumper wires i suggest checking ---each and every--- connection 

  The original code from Ingeimaks assigned values to the photoresistors top left top right and bot left and bot right.  I also did this the difference in our code is that they chose to use their complete analog input and then take an average of those values. (this works but the tracker is jumpy and constantly moves wasting power). I took their code as seen below 
```bash
 //Ingeimaks
  int avgtop = (topl + topr) ; //average of top 
  int avgbot = (botl + botr) ; //average of bottom 
  int avgleft = (topl + botl) ; //average of left 
  int avgright = (topr + botr) ; //average of right 
```
The photo resistors values were mapped from 0 to 50 and then checked for differences in their values in if statements with an error of 3. I found 3 was a very stable amount for error checking after being mapped 0-50 to keep the tracker from jumping back and forth.  (The error in the difference in photo resistor values)   
```bash
  int TopL = map(LightValue0, 0, 1023, 0, 50);     //Top Left PhotoSensor 
  int BotL = map(LightValue1, 0, 1023, 0, 50);    //Bot Left PhotoSensor
  int TopR = map(LightValue2, 0, 1023, 0, 50);   //Top Right PhotoSensor
  int BotR = map(LightValue3, 0, 1023, 0, 50);  //Bot Right PhotoSensor

  int TopDiff = (TopR + TopL) - (BotR + BotL);
  int BotDiff = (BotR + BotL) - (TopR + TopL);
  int LeftDiff = (TopL + BotL) - (TopR + BotR);
  int RightDiff = (TopR + BotR) - (TopL + BotL);
```
To check what direction the servo's both vertical and horizontal the following If statements were made 
```bash
 if (TopDiff > 3 && pVerti != 75){
    pVerti -= 1;
    Verti.write(pVerti); 
  }

  if (BotDiff > 3 && pVerti != 155){
    pVerti += 1;
    Verti.write(pVerti); 
  }

  if (RightDiff > 3 && pHori != 180){
    pHori += 1;
    Hori.write(pHori);
  }

   if (LeftDiff > 3 && pHori != 0){
    pHori -= 1;
    Hori.write(pHori);
  }
```
* You will notice in the statements there are two conditions, well the second condition was made to keep the servo's from over extending the trackers range. I wanted the tracker to be able too look straight up and all the way east to west.  These values would be different if you were to use my code for your servo's. (maybe) 

Added value to Ingeimaks Solar Tracker 
====================================
* The solar tracker will stop all its motion if it dtects the panels not producing enough voltage as seen in my code to be (voltage <0.5) The program will sit in a while loop until voltage increases
* Once night-time occurs the voltage will drop and the system will detect this and the position that it is in (west) and turn itself around to the (east) to prepare for the next days tracking activities 
* The Tracker is able to detect the voltage the panels create 
* The tracker now reads the temperature around the unit 
* The tracker now has an LCD display to relate to the user how efficient their solar panels are 

Improvements 
=============
* I would have liked to increase the size of this unit but i did not order the larger servos in time
* I Would have liekd to add a charging station and more solar panels
* This system was limited because I only had small servos so i had to shrink the unit down 
* So, for further improvements I would say increase servo size 
* Use a "reliable" 3D printer to build a better custom base 
* More Solar panels 
* Wire loom and or conduit wopuld have made the project look more pleasant
* Addidng an anemometer 
* IF anemometer was added a DMT11 moisture sensor could be added as well to create a fully functional weather station 
* Add WIFI to stream weather data to the computer or smart phone 
* creating some sort of water proof case for the electronics would be essential for a stand alone unit 

TEAM
=====
Myself - Nathan Montgomery 

Credits
=======
* Ingeimaks - https://create.arduino.cc/projecthub/Ingeimaks/diy-solar-tracker-arduino-project-ita-78ad78 - Original design Idea 

* LCD SCREEN Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld
 
 * Fritzing was used for drawing electrical diagrams - https://fritzing.org/
 
 * Dr. Trevor M. Tomesh - For being a great leader into the world of electronics 
