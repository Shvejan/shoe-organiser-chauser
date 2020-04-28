#include<Arduino.h>
int x=1,y=1,z=1;
int s1=18,s2=19,s3=21;


int rf = 26,rb =27,lf=12,lb=13; 




void straight()
 {
     digitalWrite(rf,HIGH);
     digitalWrite(rb,LOW);
     digitalWrite(lf,HIGH);
     digitalWrite(lb,LOW);
 }
  void left()       
 {
   digitalWrite(rf,0);
     digitalWrite(rb,1);
     //digitalWrite(lf,0);
     //digitalWrite(lb,1);

}
void right()
{
    //digitalWrite(rf,1);
     //digitalWrite(rb,0);
     digitalWrite(lf,1);
     digitalWrite(lb,0);
}
void stop()
{
    digitalWrite(rf,0);
     digitalWrite(rb,0);
     digitalWrite(lf,0);
     digitalWrite(lb,0);
}
 void back()
 {
     digitalWrite(rf,0);
     digitalWrite(rb,1);
     digitalWrite(lf,0);
     digitalWrite(lb,1);
 }


void setup()
{
    Serial.begin(115200);
    pinMode(s1,INPUT);
    pinMode(s2,INPUT);
    pinMode(s3,INPUT);
    pinMode(rf,OUTPUT);
    pinMode(rb,OUTPUT);
    pinMode(lf,OUTPUT);
    pinMode(lb,OUTPUT);

}
void loop()
{
   stop();
   delay(3000);
   straight();
   delay(5000);

}
 