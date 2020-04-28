#include<Arduino.h>
int x=1,y=1,z=1;

void setup()
{
    Serial.begin(115200);
    pinMode(0,INPUT);
    pinMode(5,INPUT);
    pinMode(6,INPUT);

}
void loop()
{
    x = digitalRead(5);
    y = digitalRead(10);
    z = digitalRead(4);
    Serial.print(x);
    if (x==0 && y==1 && z==0)
    {

       void straight();
        Serial.println("straight");
    }

    else if (x==1 && y==1 && z==0)
    {
       void left();
        Serial.println("left'");
    }
    
   
    else if(x==0 && y==1 && z==1)
    {
        void right();
        Serial.println("right");
    }
    
   
    else if(x==1 && y==1 && z==1)
    {   void stop();
       
        Serial.println("stop");
    }
}
 void straight()
 {
     digitalWrite(,HIGH);
     
     digitalWrite(,HIGH);
     delay(10000);
 }
  void left()       
 {
digitalWrite(,HIGH);

digitalWrite(,LOW);
delay(10000);

}
void right()
{
digitalWrite(,HIGH);
digitalWrite(,LOW);
delay(10000);
}
void stop()
{
digitalWrite(,LOW);
digitalWrite(,LOW);
delay(10000);
}
