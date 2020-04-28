#include<Arduino.h>
int x=1,y=1,z=1,a=1,b=1;
int s1=5,s2=16,s3=14,s4=10,s5=19;




void setup()
{
    Serial.begin(115200);
    pinMode(s1,INPUT);
    pinMode(s2,INPUT);
    pinMode(s3,INPUT);
    pinMode(s4,INPUT);
    pinMode(s5,INPUT);

    

}
void loop()
{
    x = digitalRead(s1);
    y = digitalRead(s2);
    z = digitalRead(s3);
    a = digitalRead(s4);
    b = digitalRead(s5);

    Serial.println(x);
    
}
 