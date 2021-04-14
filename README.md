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

[pic1]: https://github.com/Montgomery51/Final-Project-/blob/main/img/Final%20Build.jpg  "Final Build"
![alt text][pic1]













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

