#include "WiFi.h"
#define ir1 25
#define ir2 26
#define ir3 27
const char* ssid = "Chauser";
const char* password = "12345678";
WiFiServer server(80);
String html_1 = "<!DOCTYPE html><html><head><title>home</title></head><body><div id='main'>";
String html_2 = "<form id='1' action='one'><input class='button' type='submit' value='1' ></form><br>";
String html_3 = "<form id='2' action='two'><input class='button' type='submit' value='2' ></form><br>";
String html_4 = "<form id='3' action='three'><input class='button' type='submit' value='3' ></form><br>";
String html_5 = "</div></body></html>";

void goHome(){
    Serial.println('goHome');
}

boolean shoes(){
    Serial.println('chk shs');

    return(true);
}
void lower(){
    Serial.println('lower');
}
void rise()
{
    Serial.println('rise');

}
void forward(){
    Serial.println('forward');

}
void backword()
{
    Serial.println('backword');

}
void right(){
    Serial.println('right');

}
void left(){
    Serial.println('left');

}
void stop(){
    Serial.println('stop');

}
void followHome(){
    Serial.println('followhome');

}

void setup()
{
Serial.begin(115200);
    pinMode(s1,INPUT);
    pinMode(s2,INPUT);
    pinMode(s3,INPUT);


WiFi.softAP(ssid, password);
IPAddress IP = WiFi.softAPIP();
Serial.println(IP);
server.begin();
}


void goTo(int x)
{
  Serial.println("gointoo");

}



void getData()
{
    WiFiClient client=server.available();
if(client)
{
String request = client.readStringUntil('\r');
if(request.indexOf("one") != -1)
{
    goTo(1);
    Serial.println(1);
}
if(request.indexOf("two") != -1)
{
    goTo(2);
    Serial.println(2);
}

if(request.indexOf("three") != -1)
{
    goTo(3);
    Serial.println(3);
}
client.print(html_1);
client.print(html_2);
client.print(html_3);
client.print(html_4);
client.print(html_5);

request="";
}
}
void loop()
{
    getData();
}

