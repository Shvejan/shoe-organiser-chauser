#include "WiFi.h"

const char* ssid = "Chauser";
const char* password = "12345678";
WiFiServer server(80);
String html_1 = "<!DOCTYPE html><html><head><title>home</title></head><body><div id='main'>";
String html_2 = "<form id='1' action='one'><input class='button' type='submit' value='1' ></form><br>";
String html_3 = "<form id='2' action='two'><input class='button' type='submit' value='2' ></form><br>";
String html_4 = "<form id='3' action='three'><input class='button' type='submit' value='3' ></form><br>";
String html_5 = "</div></body></html>";
int a,b,c;
#define ir1 25
#define ir2 26
#define ir3 27



void forward()
{
    Serial.println("forward");
}
void backward()
{
    Serial.println("back");
}
void right()
{
    Serial.println("riht");
}
void left()
{
    Serial.println("left");
}
void stop()
{
    Serial.println("stop");
}

void lower()
{
    Serial.println("lower");
    delay(2000);
}


void goTo(int d)
{
    Serial.println("goin 22");
    int c=1;
    forward();
    delay(300);
    a = digitalRead(ir1);
    b = digitalRead(ir2);
    c = digitalRead(ir3);
    Serial.print(a);
    Serial.print(b);
    Serial.println(c);

    while(true)
    {
        Serial.println("while looppp");
        a = digitalRead(ir1);
        c = digitalRead(ir2);
        b = digitalRead(ir3);



        if(a!=1 && b!=0 && c!=1)
        {
            forward();
        }
        if(a!=0 && b!=1 && c!=1)
        {
            left();
        }
        if(a!=1 && b!=1 && c!=0)
        {
            right();
        }
        if(a!=1 && b!=0 && c!=0)
        {
            Serial.println("junction");

            if(d==c)
            {
                right();
                delay(400);
                c+=1;
                Serial.println("turning right");

            }
            else
            {
                c+=1;
            }
            
        }

    }
    stop();
    delay(1000);
    lower();
    


}








void setup()
{
Serial.begin(115200);


WiFi.softAP(ssid, password);
IPAddress IP = WiFi.softAPIP();
Serial.println(IP);
server.begin();
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
if(request.indexOf("two") != -1){
    goTo(2);
    Serial.println(2);
    
}
if(request.indexOf("three") != -1){
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