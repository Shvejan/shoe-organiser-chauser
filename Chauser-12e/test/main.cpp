#include <Arduino.h>

#define ir1 1
#define ir2 2
#define ir3 3

#define lf 4
#define lb 5
#define rf 6
#define rb 7

#define trig 8
#define echo 9

#define up 10
#define down 11



void getData();
void goHome();
void goTo(int);
boolean shoes();
void lower();
void rise();
void forward();
void backword();
void right();
void left();
void stop();


void setup() {

  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  pinMode(ir3,INPUT);
  pinMode(lf,OUTPUT);
  pinMode(lb,OUTPUT);
  pinMode(rf,OUTPUT);
  pinMode(rb,OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(up,OUTPUT);
  pinMode(down,OUTPUT);

  Serial.begin(115200);
}

void loop() 
{
  Serial.println("loop");
  getData();

}


void getData()
{
  goTo(1);
}


void goHome()
{
  backword();
  delay(200);
  while(digitalRead(1) >0 && digitalRead(2)<0  && digitalRead(3)>0)
  {
    if(digitalRead(1) <0 && digitalRead(2)>0  && digitalRead(3)<0)
    {
      forward();
    }

    if(digitalRead(1) >0 && digitalRead(2)<0  && digitalRead(3)<0)
    {
      left();
    }

    if(digitalRead(1) <0 && digitalRead(2)<0  && digitalRead(3)>0)
    {
      right();
    }

    if( digitalRead(2)>0  && digitalRead(3)>0)
    {
      right();
    }

  }
  lower();
  stop();
  delay(500);

}


void goTo(int x)
{
  int c=1;
  if(shoes())
    rise();
  


  while(digitalRead(1) >0 && digitalRead(2)<0  && digitalRead(3)>0)
  {
    if(digitalRead(1) <0 && digitalRead(2)>0  && digitalRead(3)<0)
    {
      forward();
    }

    if(digitalRead(1) >0 && digitalRead(2)<0  && digitalRead(3)<0)
    {
      left();
    }

    if(digitalRead(1) <0 && digitalRead(2)<0  && digitalRead(3)>0)
    {
      right();
    }

    if(digitalRead(1) <0 && digitalRead(2)>0  && digitalRead(3)>0)
    {
      if(c==x)
      {
        right();
      }
      else
      {
        c++;
        forward();
      } 
    }
  }
  stop();
  delay(500);
  if(shoes())
    lower();
  else
    rise();

  goHome();

}

boolean shoes()
{
  digitalWrite(trig,HIGH);
  delay(100);
  digitalWrite(trig,LOW);
  delay(20);
  int t = pulseIn(echo,HIGH);
  int dist = t*0.034/2;
  Serial.println(dist);
  if(t<10)
    return true;
  else
    return false;

}





void lower()
{
  Serial.println("lower");
  digitalWrite(down,HIGH);
  delay(2000);
  digitalWrite(down,LOW);
}



void rise()
{
  Serial.println("rise");
  digitalWrite(up,HIGH);
  delay(2000);
  digitalWrite(up,LOW);
}



void forward()
{
  Serial.println("forward");
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
  digitalWrite(rf,HIGH);
  digitalWrite(lf,HIGH);
}



void backword()
{
  Serial.println("backword");
  digitalWrite(rf,LOW);
  digitalWrite(lf,LOW);
  digitalWrite(rb,HIGH);
  digitalWrite(lb,HIGH);
}


void right()
{
  Serial.println("right");
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
  digitalWrite(rf,LOW);
  digitalWrite(lf,HIGH);
}



void left()
{
  Serial.println("left");
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
  digitalWrite(rf,HIGH);
  digitalWrite(lf,LOW);
}

void stop()
{
  Serial.println("stop");
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
  digitalWrite(rf,LOW);
  digitalWrite(lf,LOW);
}