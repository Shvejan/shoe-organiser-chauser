#include <Arduino.h>

#define ir1 25
#define ir2 26
#define ir3 27

#define lf 4
#define lb 5
#define rf 6
#define rb 7

#define trig 8
#define echo 9

#define up 10
#define down 11

#include <WiFi.h>
const char WiFiPassword[] = "12345678";
const char AP_NameChar[] = "Chauser" ;
 
WiFiServer server(80);
 
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = "<!DOCTYPE html><html><head><title>home</title><script>console.log('holaa');</script></head><body><div id='main'>";
String html_2 = "<form id='1' action='one'><input class='button' type='submit' value='1' ></form><br>";
String html_3 = "<form id='2' action='two'><input class='button' type='submit' value='2' ></form><br>";
String html_4 = "<form id='3' action='three'><input class='button' type='submit' value='3></form><br>";
String html_5 = "</div></body></html>";


String html_t = "<script>console.log('hehehehhehe')</script>";
String request = "";


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
void followHome();

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
  boolean conn = WiFi.softAP(AP_NameChar, WiFiPassword);
  server.begin();
  Serial.begin(115200);

  IPAddress IP = WiFi.softAPIP();
  Serial.println(IP);
}

void loop() 
{
  Serial.println("loop");
  getData();

}


void getData()
{
  WiFiClient client=server.available();
  if(client)
  {
    String request = client.readStringUntil('\r');
    if(request.indexOf("one") != -1){
      Serial.println(1);
      goTo(1);
    }
    if(request.indexOf("two") != -1)
    {
      Serial.println(2);
      goTo(2);
    }
    if(request.indexOf("three") != -1)
    {
      Serial.println(3);
      goTo(3);
    }
    client.print(html_1);
    client.print(html_2);
    client.print(html_3);
    client.print(html_4);
    client.print(html_5);

    request="";
  }
}

void followHome()
{
  while(!(digitalRead(ir1) >0 && digitalRead(ir2)<0  && digitalRead(ir3)>0))
  {
    if(digitalRead(ir1) <0 && digitalRead(ir2)>0  && digitalRead(ir3)<0)
    {
      forward();
    }

    if(digitalRead(ir1) >0 && digitalRead(ir2)<0  && digitalRead(ir3)<0)
    {
      left();
    }

    if(digitalRead(ir1) <0 && digitalRead(ir2)<0  && digitalRead(ir3)>0)
    {
      right();
    }
    if(digitalRead(ir1) >0 && digitalRead(ir2)>0  && digitalRead(ir3)<0)
    {
      forward();
    }
  }
  lower();
  stop();
  delay(500);

}
void goHome()
{
 // backword();
  //delay(200);
  while(1)
  {
    if(digitalRead(ir1) <0 && digitalRead(ir2)>0  && digitalRead(ir3)<0)
    {
      backword();
    }

    if(digitalRead(ir1) >0 && digitalRead(ir2)<0  && digitalRead(ir3)<0)
    {
      right();
    }

    if(digitalRead(ir1) <0 && digitalRead(ir2)<0  && digitalRead(ir3)>0)
    {
      left();
    }

    if( digitalRead(ir2)>0  && digitalRead(ir3)>0)
    {
      right();
      delay(1000);
      followHome();
    }

  }
  

}


void goTo(int x)
{
  int c=1;
  if(shoes())
    rise();
  


  while(!(digitalRead(ir1) >0 && digitalRead(ir2)<0  && digitalRead(ir3)>0))
  {
    if(digitalRead(ir1) <0 && digitalRead(ir2)>0  && digitalRead(ir3)<0)
    {
      forward();
    }

    if(digitalRead(ir1) >0 && digitalRead(ir2)<0  && digitalRead(ir3)<0)
    {
      left();
    }

    if(digitalRead(ir1) <0 && digitalRead(ir2)<0  && digitalRead(ir3)>0)
    {
      right();
    }

    if(digitalRead(ir1) <0 && digitalRead(ir2)>0  && digitalRead(ir3)>0)
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