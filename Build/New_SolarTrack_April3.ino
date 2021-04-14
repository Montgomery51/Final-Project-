/*
   CS 207 Final Project
   Project Name: Solar tracker weather station  
   
   Description:   
 
   Setup:  materials : 4 x 10KΩ resistors 
                       4 x Photo resistors
                       Jumper wires 
                       Arduino UNO Board 

  
    Name: Nathan Montgomery
    SID: 200354470
    Due Date: April 14th, 2021   
*/

#include <Servo.h> // Servo library 

Servo Hori;  //Horizontal and Vertical Servos for tracking 
Servo Verti;

const int LightReadOut0= A0;
const int LightReadOut1= A1;
const int LightReadOut2= A2;
const int LightReadOut3= A3;

int LightValue0 = 0;
int LightValue1 = 0;
int LightValue2 = 0;
int LightValue3 = 0;

 int TopDiff = 0;
 int BotDiff = 0;
 int LeftDiff = 0;
 int RightDiff = 0;
 int pHori = 180;
 int pVerti = 180;

void setup() {

  Hori.attach(9);
  Hori.write (pHori);
  Verti.attach(10);
  Verti.write(pVerti);
  Serial.begin(9600);
  

}

void loop() {
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

  int TopDiff = (TopR + TopL) - (BotR + BotL);
  int BotDiff = (BotR + BotL) - (TopR + TopL);
  int LeftDiff = (TopL + BotL) - (TopR + BotR);
  int RightDiff = (TopR + BotR) - (TopL + BotL);

// TopDiff = abs(TopDiff);
// BotDiff = abs(BotDiff);
// LeftDiff = abs(LeftDiff);
// RightDiff = abs(RightDiff);

//  int TopTwo = ((TopL + TopR) / 2);
//  int BotTwo = ((BotL + BotL) / 2);
//  int LeftTwo = ((TopL + BotL) / 2);
//  int RightTwo = ((TopR + BotR) /2);

  if (TopDiff > 3 && pVerti != 0)
  {
    pVerti -= 1;
    Verti.write(pVerti); 
  }

  if (BotDiff > 3 && pVerti != 180)
  {
    pVerti += 1;
    Verti.write(pVerti); 
  }

  if (RightDiff > 3 && pHori != 180)
  {
    pHori += 1;
    Hori.write(pHori);
  }

   if (LeftDiff > 3 && pHori != 0)
  {
    pHori -= 1;
    Hori.write(pHori);
  }


  

//Print for light sensor value and sight value 0-50 
  Serial.print("Light sensor top left =");      
  Serial.println(pVerti);
  Serial.print("Light sensor Bottom Left =");       
  Serial.println(BotL);
  Serial.print("Light sensor Top Right =");      
  Serial.println(TopR);
  Serial.print("Light sensor Bottom Right =");     
  Serial.println(BotR);
  Serial.println(" ");
  //delay(2000);
  
}
