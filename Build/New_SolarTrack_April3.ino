/*
   CS 207 Final Project
   Project Name: Solar tracker weather station  
   
   Description:   
 
   Setup:  materials :  1 x Arduino UNO
                        1 x Breadboard (or prototype boards and solder - Used in this project)
                        4 x PhotoResistors 
                        4 x 10k ohm Resistors 
                        1 x 220 ohm Resistor
                        1 x TMP36 Temperature Sensor 
                        2 x Servo motor (Bigger is Better! But not needed)
                        1 x 16 PIN LCD Screen 
                        1 x 10k ohm Potentiometer 
                        Solar Panel (Salvaged or new)
                        Wire for connections 
                        External power supply 

------------------------------------------------------------------------------
 LiquidCrystal Library  
 This example code is in the public domain.
 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

-----------------------------------------------------------------------------
*******
Code based off a project by Ingeimaks at https://create.arduino.cc/projecthub/Ingeimaks/diy-solar-tracker-arduino-project-ita-78ad78

-----------------------------------------------------------------------------

  
    Name: Nathan Montgomery
    SID: 200354470
    Due Date: April 14th, 2021   
*/

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
