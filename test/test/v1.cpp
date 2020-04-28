#include <Arduino.h>
int t=0,d;
void setup() {
  Serial.begin(115200);
  pinMode(16,OUTPUT);
   pinMode(12,INPUT);
    pinMode(10,OUTPUT);
   
  
}

void loop() {

digitalWrite(16,HIGH);
delayMicroseconds(1000);
digitalWrite(16,LOW);
t = pulseIn(12,HIGH);
d= 330*t*0.001/2;
//Serial.println(d);

if(d<200)
{
digitalWrite(10,HIGH);
Serial.println("yes");

  
}
else
{
  digitalWrite(10,LOW);
  Serial.println("no");

}



}