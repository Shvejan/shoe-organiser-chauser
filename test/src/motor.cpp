//192.168.4.1

#include"Arduino.h" 
#include <ESP8266WiFi.h>
const char WiFiPassword[] = "12345678";
const char AP_NameChar[] = "Chauser" ;
 
WiFiServer server(80);
 
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = "<!DOCTYPE html><html><head><title>home</title></head><body><div id='main'>";
String html_2 = "<form id='1' action='one'><input class='button' type='submit' value='1' ></form><br>";
String html_3 = "<form id='2' action='two'><input class='button' type='submit' value='2' ></form><br>";
String html_4 = "<form id='3' action='three'><input class='button' type='submit' value='3' ></form><br>";
String html_5 = "</div></body></html>";

int rf = 26,rb = 27,lf = 12,lb=13;
int l =32,u=33;
String request = "";
 void upper()
{
  digitalWrite(l,0);
  digitalWrite(u,1);
}
void lower()
{
  digitalWrite(u,0);
  digitalWrite(l,1);
}
void straight()
{
  digitalWrite(rf,1);
  digitalWrite(lf,1);
  
  digitalWrite(rb,0);
  digitalWrite(lb,0);
}
void wait()
{
  
  digitalWrite(rf,0);
  digitalWrite(lf,0);
  
  digitalWrite(rf,0);
  digitalWrite(lf,0);
}
void setup() 
{
    Serial.begin(115200);
    //boolean conn = WiFi.softAP(AP_NameChar, WiFiPassword);
    pinMode(13,OUTPUT);
    pinMode(14,OUTPUT);

    server.begin();
 
}
 
 
void loop() 
{
    WiFiClient client = server.available();
    if (!client)  
      return;  
 
    request = client.readStringUntil('\r');

    if(request.indexOf("one") > 0)  
    {  
        Serial.println(1);
        upper();
        delay(600);
        straight();
        delay(5000);
        wait();
        delay(3000);
        lower();
        delay(3000);
        upper();
    }
    else if(request.indexOf("two") > 0) 
    {  
            lower();
            delay(600);
            straight();
            delay(5000);
            wait();
            delay(3000);
            upper();
            delay(600);
    }
    else if(request.indexOf("three")>0)
    { 
        Serial.println("3");
    }
 
    client.flush();
 
    client.print( header );
    client.print( html_1 );
    client.print( html_2 );
    client.print( html_3 );
    client.print( html_4 );
 
    delay(5000);
 
} 