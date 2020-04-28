#include<Arduino.h>
int x=1,y=1,z=1;
int s1=25,s2=26,s3=27;


int rf = 0,rb =2,lf=5,lb=4; 




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
     digitalWrite(lf,0);
     digitalWrite(lb,1);

}
void right()
{
    digitalWrite(rf,1);
     digitalWrite(rb,0);
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
    x = digitalRead(s1);
    y = digitalRead(s2);
    z = digitalRead(s3);
    //Serial.print(x);
    //Serial.print(y);
    //Serial.println(z);
    if (x==1 && y==0 && z==1)
    {
        Serial.println("straight");
        straight();
    }
    else if (x==0 && y==0 && z==1){
        Serial.println("left'");
        left();
    }
    else if(x==1 && y==0 && z==0){
    Serial.println("right");
    right();
    }
    else if(x==1 && y==1 && z==0){
    Serial.println("right");
    right();
    }
    else if(x==0 && y==1 && z==1){
        Serial.println("left'");
        left();
    }
    else if(x==0 && y==1 && z==0){
        Serial.println("stop");
        stop();
    }
}
 