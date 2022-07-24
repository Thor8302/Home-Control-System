 /*
  This is for my  C O N T R O L L E R
*/
#include<Servo.h>
#include<SoftwareSerial.h>
#include <Wire.h>
#include "RTClib.h"
#include <OneWire.h>
#include <DallasTemperature.h>


RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


#define RX          10
#define TX          12
#define Light1       9
#define Light2      10
#define Fan         10
#define Main        10
#define Extramain
#define cyphercam   A7
#define staticcam   A3
#define tempwire    A0
#define ldr         A6


OneWire oneWire(tempwire);
DallasTemperature sensors(&oneWire);


int;
float temperature;
bool;
char;
string;

void setup() {
  SoftwareSerial Sentinal = SoftwareSerial(RX, TX);
  sensors.begin();
  Servo Cypher;
  Cypher.attach(11);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(A3, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  digitalWrite(2, 1);
  digitalWrite(3, 1);
  digitalWrite(4, 1);
  digitalWrite(5, 1);
  digitalWrite(6, 1);
  digitalWrite(7, 1);
  digitalWrite(8, 1);
  digitalWrite(9, 0);


  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  //  else
  //  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");

    // Comment out below lines once you set the date & time.
    // Following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

    // Following line sets the RTC with an explicit date & time
    // for example to set January 27 2017 at 12:56 you would call:
    //rtc.adjust(DateTime(2022, 1, 14, 4, 36, 25));1

  }
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

}

void loop()
{
 
 //   Reading variables !!!
 { 
   DateTime now = rtc.now();
   sensors.requestTemperatures();
   temperature = sensors.getTempCByIndex(0);
 }
 
 //    motion sensing and time setting section
{
if (presence)         ////                      from here presence section begins
{
  check_motion(cypheron);
  DateTime light1oninerval( now + TimeSpan(0,0,0,15));         ///      light1 interval reset         
  DateTime light2oninerval( now + TimeSpan(0,0,0,15));         ///      light2 interval reset
  DateTime fanoninerval( now + TimeSpan(0,0,0,15));            ///      fan interval reset
  
  if(motion==0)                                   ///  if motion stopped 
  {
    if(presenceonce)
    {
      DateTime presenceduration(now + TimeSpan(0,0,0,5));             //    creating buffer for presence for once while motion stopped
      presenceonce=0;
    }
    
  }
  else
  {
    presenceonce=1;
  }
}                                         ///                 presence section ends here   


else if(presence!)                                  //               from here   non presence section begins
{
  
  if(motion!=0)
  {
    check_motion(cypheron);                                    //as found motion so cypher now on
    DateTime light2oninterval (now + TimeSpan(0,0,1,0));       //switching on light 1 for passage
    trigger(2);
    if(motiononce)
    {
      DateTime presencedelayinterval ( now + TimeSpan(0,0,0,3));     // delaying presence for the passer by
      motiononce=0;
    }
    if(checktime(presencedelaytime)==1)
    {   
      presence=1;                                                     //   declaring presence after 3 seconds of continous motion
    }
  }
  else 
  {
    motiononce=1;
    check_motion(cypheroff);                                       //// checking for motion in ideal state
  }
}                                                    ///                non presence section ends here

}

///    trigger section here
{                                  //                             from here
if(checktime(light1ontime)==1)        //   for light 1   
{
  trigger(1);
}
else if(checktime(light2ontime)==1)         //     for light 2
{
  trigger(2);
}
else if(checktime(fanontime)==1)        //     for fan
{
  trigger(3); 
}                                                                 ///      trigger section
else if(checktime(mainontime)==1)          //      for main
{
  trigger(4);
}
else if (checktime(presencedurationtime))             //     for presence hold
{
  presence=0;
}                                                  ////                    to here
}


int check_motion (bool cypherstatus)
{

  cypherpos(cypherstatus);

  if ((analogRead(A3) >= static_barrier) && (anlogRead(A7) < dynamic_barrier))
  {
    motion = 1;                                                                               // it means that static cam identifies motion
  }
  else if ((analogRead(A3) < static_barrier)) && (analogRead(A7) >= dynamic_barrier))
  {
    motion = 2;                                                                               // it means that dynamic cam identifies motion
  }
  else if ((analogRead(A3) >= static_barrier) && (analogRead(A7) >= dynamic_barrier))
  {
    motion = 3;                                                                              // it means that both of them identifies motion
  }
  else if ((analogRead(A3) < static_barrier) && (analogRead(A7) < dynamic_barrier))
  {
    motion = 0;                                                                              // it means that no motion is identified.
  }
  return 8;
}

int trigger(int response)
{
  if (response == 0)
  {
    digitalWrite(Light1, 0);
    digitalWrite(Light2, 1);
    digitalWrite(Fan, 1);
    digitalWrite(Main, 1);

  }
  else if (response == 1)
  {
    digitalWrite(Light1, 1);

  }
  else if (response == 2)
  {
    digitalWrite(Light2, 0);

  }
  else if (response == 3)
  {
    digitalWrite(Fan, 0);

  }
  else if (response == 4)
  {
    digitalWrite(Main,0);
  }
  else if (response == -1)
  {
    digitalWrite(Light1, 0);

  }
  else if (response == -2)
  {
    digitalWrite(Light2, 1);

  }
  else if (response == -3)
  {
    digitalWrite(Fan, 1);

  }
  else if ( response ==-4)
  {
    digitalWrite(Main,1);
  }
  return 8;
}

int cypherpos(bool position)
{
  if(postion)
  {
    if(angle>94)
    {
      adder=-1;
    }
    else if(angle<86)
    {
      adder=1;
    }
    angle+=adder;
  }
  else if(position!)
  {
    if(angle >90)
    {
      angle-=1;
    }
    else if(angle<90)
    {
      angle+=1;
    }
    else{}
  }
}

int checktime(int mode)
{
  if (mode==cyphertime)
  {
    if((now.second(),DEC)%2==0)
    return 1;
    else
    return 0;
  }
  else if(mode==light1ontime)
  {
    if((light1oninterval.hour(),DEC)-(now.hour(),DEC)>0)
    return 1;
    else if((light1oninterval.minute(),DEC)-(now.minute(),DEC)>0)
    return 1;
    else if((light1oninterval.second(),DEC)-(now.second(),DEC)>0)
    return 1;
    else 
    return 0;
    
  }
  else if(mode==light2ontime)
  {
    
    if((light2oninterval.hour(),DEC)-(now.hour(),DEC)>0)
    return 1;
    else if((light2oninterval.minute(),DEC)-(now.minute(),DEC)>0)
    return 1;
    else if((light2oninterval.second(),DEC)-(now.second(),DEC)>0)
    return 1;
    else 
    return 0;
    
  }
  else if(mode==fanontime)
  {
   
    if((fanoninterval.hour(),DEC)-(now.hour(),DEC)>0)
    return 1;
    else if((fanoninterval.minute(),DEC)-(now.minute(),DEC)>0)
    return 1;
    else if((fanoninterval.second(),DEC)-(now.second(),DEC)>0)
    return 1;
    else 
    return 0;
     
  }
  else if(mode==mainontime)
  {
    
    if((mainoninterval.hour(),DEC)-(now.hour(),DEC)>0)
    return 1;
    else if((mainoninterval.minute(),DEC)-(now.minute(),DEC)>0)
    return 1;
    else if((mainoninterval.second(),DEC)-(now.second(),DEC)>0)
    return 1;
    else 
    return 0;
    
  }
  else if(mode==presencedelaytime)
  {
    
    if((presencedelayinterval.hour(),DEC)-(now.hour(),DEC)<0)
    return 1;
    else if((presencedelayinterval.minute(),DEC)-(now.minute(),DEC)<0)        //        in no presence if motion caught delay to declare as presence
    return 1;
    else if((presencedelayinterval.second(),DEC)-(now.second(),DEC)<0)
    return 1;
    if((presencedelayinterval.hour(),DEC)-(now.hour(),DEC)<0)
    return 1;
    else if((presencedelayinterval.minute(),DEC)-(now.minute(),DEC)<0)        //        in no presence if motion caught delay to declare as presence
    return 1;
    else if((presencedelayinterval.second(),DEC)-(now.second(),DEC)<0)
    return 1;
    else 
    return 0;
    
  }
   else if(mode==light1offtime)
  {
    if((light1offinterval.hour(),DEC)-(now.hour(),DEC)<0)
    return 1;
    else if((light1offinterval.minute(),DEC)-(now.minute(),DEC)<0)
    return 1;
    else if((light1offinterval.second(),DEC)-(now.second(),DEC)<0)
    return 1;
    else 
    return 0;
    
  }
  else if(mode==light2offtime)
  {
    
    if((light2offinterval.hour(),DEC)-(now.hour(),DEC)<0)
    return 1;
    else if((light2offinterval.minute(),DEC)-(now.minute(),DEC)<0)
    return 1;
    else if((light2offinterval.second(),DEC)-(now.second(),DEC)<0)
    return 1;
    else 
    return 0;
    
  }
  else if(mode==fanofftime)
  {
   
    if((fanoffinterval.hour(),DEC)-(now.hour(),DEC)<0)
    return 1;
    else if((fanoffinterval.minute(),DEC)-(now.minute(),DEC)<0)
    return 1;
    else if((fanoffinterval.second(),DEC)-(now.second(),DEC)<0)
    return 1;
    else 
    return 0;
     
  }
  else if(mode==mainoff)
  {
    
    if((mainoffinterval.hour(),DEC)-(now.hour(),DEC<)0)
    return 1;
    else if((mainoffinterval.minute(),DEC)-(now.minute(),DEC)<0)
    return 1;
    else if((mainoffinterval.second(),DEC)-(now.second(),DEC)<0)
    return 1;
    else 
    return 0;
    
  }
  else if(mode==4)
  {
    
    if((light1interval.hour(),DEC)-(now.hour(),DEC)<0)
    return 1;
    else if((light1interval.minute(),DEC)-(now.minute(),DEC)<0)    ///           if u wannna put more time put it here
    return 1;
    else if((light1interval.second(),DEC)-(now.second(),DEC)<0)
    return 1;
    else 
    return 0;
    
  }
}

