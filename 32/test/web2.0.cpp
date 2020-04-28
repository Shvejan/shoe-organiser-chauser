#include "WiFi.h"
#define LED0 23
#define LED1 22
const char* ssid = "ESP32-Soft-accessPoint";
const char* password = "microcontrollerslab";
WiFiServer server(80);
String html ="<!DOCTYPE html> \
<html> \
<body> \
<center><h1>ESP32 Soft access point</h1></center> \
<center><h2>Web Server</h2></center> \
<form> \
<button name=\"LED0\" button style=\"color:green\" value=\"ON\" type=\"submit\">LED0 ON</button> \
<button name=\"LED0\" button style=\"color=red\" value=\"OFF\" type=\"submit\">LED0 OFF</button><br><br> \
<button name=\"LED1\" button style=\"color:green\" value=\"ON\" type=\"submit\">LED1 ON</button> \
<button name=\"LED1\" button style=\"color:red\" value=\"OFF\" type=\"submit\">LED1 OFF</button> \
</form> \
</body> \
</html>";



void setup()
{
Serial.begin(115200);
pinMode(LED0, OUTPUT);
pinMode(LED1, OUTPUT);

WiFi.softAP(ssid, password);
IPAddress IP = WiFi.softAPIP();
Serial.println(IP);
server.begin();
}


void loop()
{
WiFiClient client=server.available();
if(client)
{
String request = client.readStringUntil('\r');
if(request.indexOf("LED0=ON") != -1)digitalWrite(LED0, HIGH);
if(request.indexOf("LED0=OFF") != -1)digitalWrite(LED0, LOW);
if(request.indexOf("LED1=ON") != -1)digitalWrite(LED1, HIGH);
if(request.indexOf("LED1=OFF") != -1)digitalWrite(LED1, LOW);
client.print(html);
request="";
}
}