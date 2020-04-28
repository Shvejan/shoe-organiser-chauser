#include "WiFi.h"

const char* ssid = "ESP32-Soft-accessPoint";
const char* password = "microcontrollerslab";
WiFiServer server(80);
String html_1 = "<!DOCTYPE html><html><head><title>home</title></head><body><div id='main'>";
String html_2 = "<form id='1' action='one'><input class='button' type='submit' value='1' ></form><br>";
String html_3 = "<form id='2' action='two'><input class='button' type='submit' value='2' ></form><br>";
String html_4 = "<form id='3' action='three'><input class='button' type='submit' value='3' ></form><br>";
String html_5 = "</div></body></html>";

void setup()
{
Serial.begin(115200);


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
if(request.indexOf("one") != -1)Serial.println(1);
if(request.indexOf("two") != -1)Serial.println(2);
if(request.indexOf("three") != -1)Serial.println(3);
client.print(html_1);
client.print(html_2);
client.print(html_3);
client.print(html_4);
client.print(html_5);

request="";
}
}