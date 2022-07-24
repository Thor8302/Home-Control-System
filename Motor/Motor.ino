#define echoPin 5 // attach pin D2 Arduino to pin Echo of JSN-SR04T
#define trigPin 6 //attach pin D3 Arduino to pin Trig of JSN-SR04T
#define start1  9
#define start2  8              ///       c h e c k    o n c e
#define stop  7

#include <SoftwareSerial.h>

#define rxPin 11
#define txPin 12

// Set up a new SoftwareSerial object
SoftwareSerial Sentinal =  SoftwareSerial(rxPin, txPin);



// defines variables
long duration; // variable for the duration of sound wave travel
int distance[10],i=0,echocheck=3,bar=10,fdistance; // variable for the distance measurement
// bat variable
float battemp=0,battery=0,batcount=0,batcent,batmax=13;
bool batlock;
// tank variable
int depth=200;
bool tanklock=0;
bool correctness;
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(start1,OUTPUT);
  pinMode(start2,OUTPUT);
  pinMode(stop,OUTPUT);
  pinMode(A0,INPUT);
  Sentinal.begin(9600); 
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baud rate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}
void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);  //
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance[i] = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  i+=1;
  if(i>=echocheck)
  i=0;
  for(int a=1;a<echocheck;a++)
  {
    correctness=1;
    if((distance[a]-distance[0]>bar)||(distance[a]-distance[0]>bar))
    correctness=0;
  }
  if(correctness)
  {
    fdistance=0;
   for(int a=0;a<echocheck;a++)
   {
     fdistance=fdistance+distance[a];
   }
  }
  
  


if(batlock)
{
  batcent=percentage(battery,batmax);
  Sentinal.write("bat=");
  Sentinal.write(batcent);
}
if(tanklock)
{
  tankcent=percentage(fdistance,depth);
  tankcent=100-tankcent;
  Sentinal.write("tank=");
  Sentinal.write(tankcent);
  if(tankcent<30)
  {
    if(relaylock)
    {
      if(lightcount>=lightmotorlimit)
      relay(1);
    }
  }
}
  delay(10);
}






int variableread(string var)
{
  if(var=="battery")
  return battery;
  else if(var=="battemp")
  return battemp;
  else if(var=="battemp")          /////                  p e n d i n g
  return battemp;
  else if(var=="battemp")
  return battemp;
  else if(var=="battemp")
  return battemp;
  else if(var=="battemp")
  return battemp;
  else if(var=="battemp")
  return battemp;
}




int variablechange(float value)
{
  if(change=="battery")
  battery=value;
  else if(change=="battemp")
  battemp=value;
}




int percentage(float value,float max)
{
  return((value*100)/max);
}




int relay(int mode=0)
{
  int done=0;
  if(mode==1)
  {
    digitalWrite(start1,0);
    digitalWrite(start2,0);
    digitalWrite(stop,1);
    delay(300);
    digitalWrite(start1,1);
    digitalWrite(start2,1);
    done=1;
  }
  else if(mode==0)
  {
    digitalWrite(stop,0);
    delay(300);
    digitalWrite(stop,1);
    done=1;
  }
  return done;
}




int batterystudy()
{
    float a=analogRead(A0);  
  a=a*14.35;
  a=a/1028;
  battemp[i]=a;
  batcount=batcount+1;
  if(batcount>=10)
  {
    a=0;
    for(int i=0;i<10;i++)
    a=a+battemp[i];
    battery=a/10;
    batcount=0;
    if(Serial.available())
    {
      Serial.print("battery : ");
      Serial.println(battery);
    }
  if((battery>=10.5)&&(battery<=14))
  return 1;
  else 
  return 0;
  }
}