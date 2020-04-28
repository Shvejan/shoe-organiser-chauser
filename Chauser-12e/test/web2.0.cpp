//192.168.4.1

#include<Arduino.h> 
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


String request = "";
 
void setup() 
{
    Serial.begin(115200);
    boolean conn = WiFi.softAP(AP_NameChar, WiFiPassword);
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
        Serial.println("1"); 
        digitalWrite(13,HIGH);
        delay(2000);
        digitalWrite(13,LOW);
    }
    else if(request.indexOf("two") > 0) 
    {  
        Serial.println("2"); 
        digitalWrite(14,HIGH);
        delay(2000);
        digitalWrite(14,LOW);
    }
    else if(request.indexOf("three")>0)
    { 
        Serial.println("3");  
        digitalWrite(9,HIGH);
        delay(2000);
        digitalWrite(9,LOW);
    }
 
    client.flush();
 
    client.print( header );
    client.print( html_1 );
    client.print( html_2 );
    client.print( html_3 );
    client.print( html_4 );
 
    delay(5000);
 
} 