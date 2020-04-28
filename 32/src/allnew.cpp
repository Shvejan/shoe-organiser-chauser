#include <WiFi.h>

const char* ssid = "Chauser";
const char* password = "12345678";
WiFiServer server(80);
String html_1 = "<!DOCTYPE html><html><head><title>home</title></head><body><div id='main'>";
String html_2 = "<form id='1' action='one'><input class='button' type='submit' value='1' ></form><br>";
String html_3 = "<form id='2' action='two'><input class='button' type='submit' value='2' ></form><br>";
String html_4 = "<form id='3' action='three'><input class='button' type='submit' value='3' ></form><br>";
String html_5 = "</div></body></html>";
int t=0;
#define ir1 18
#define ir2 19
#define ir3 21

#define rf 11
#define rb 11
#define lf 11
#define lb 11

#define up 21
#define lo 22

#define trig 33
#define echo 22

void forward()
{
    
    digitalWrite(rb,0);
    digitalWrite(lb,0);
    digitalWrite(rf,1);
    digitalWrite(lf,1);

    Serial.println("forward");
}
void backward()
{
    
    digitalWrite(rf,0);
    digitalWrite(lf,0);
    digitalWrite(rb,1);
    digitalWrite(lb,1);
    Serial.println("back");
}
void right()
{
    digitalWrite(rb,0);
    digitalWrite(lb,0);
    digitalWrite(rf,0);
    digitalWrite(lf,1);
    
    Serial.println("riht");
}
void left()
{
    digitalWrite(rb,0);
    digitalWrite(lb,0);
    digitalWrite(lf,0);
    digitalWrite(rf,1);
    Serial.println("left");
}
void bright()
{
    
    digitalWrite(lf,0);
    digitalWrite(rf,0);
    digitalWrite(rb,0);
    digitalWrite(lb,1);
    Serial.println("riht");
}
void bleft()
{
    digitalWrite(lf,0);
    digitalWrite(rf,0);
    digitalWrite(lb,0);
    digitalWrite(rb,1);
    Serial.println("left");
}
void stop()
{
    digitalWrite(lf,0);
    digitalWrite(rf,0);
    digitalWrite(lb,0);
    digitalWrite(rb,0);
    Serial.println("stop");
}

void lower()
{
    digitalWrite(up,0);
    digitalWrite(lo,1);

    Serial.println("lower");
    delay(2000);
}
void rise()
{
    digitalWrite(lo,0);
    digitalWrite(up,1);
    Serial.println("rise");
    delay(2000);
}
boolean shoes()
{
    return true;
}



void goHome()
{

    Serial.println("goin Home");
    backward();
    delay(100);
    int x,y,z;
    x = digitalRead(ir1);
    y = digitalRead(ir2);
    z = digitalRead(ir3);
    Serial.print(x);
    Serial.print(y);
    Serial.print(z);
    while(true)
    {
        Serial.print(x);
        Serial.print(y);
        Serial.print(z);
        if(x==1 && y==0 && z==1 )
        {
            backward();
        }

        else if(x==1 && y==1 && z==0 )
        {
            bright();
        }

        else if(x==0 && y==1 && z==1 )
        {
            bleft();
        }
        else if( y==0 && z==0 )
        {
            bright();
            delay(2000);

        }


        else if(x==0 && y==1 && z==0)
        {
            break;
        }
        else
        {
            backward();
        }
        x = digitalRead(ir1);
        y = digitalRead(ir2);
        z = digitalRead(ir3);
        

    }
    lower();
    Serial.println("reached home");
    
    


}











void goTo(int d)
{
    forward();
    delay(1000);
    int x,y,z,c=1;
    x = digitalRead(ir1);
    y = digitalRead(ir2);
    z = digitalRead(ir3);
    Serial.print(x);
    Serial.print(y);
    Serial.print(z);
    if(shoes())
    {
        rise();
    }
    

    while(true)
    {
        Serial.print(x);
        Serial.print(y);
        Serial.print(z);
        if(x==1 && y==0 && z==1 )
        {
            forward();
        }

        else if(x==1 && y==1 && z==0 )
        {
            right();
        }

        else if(x==0 && y==1 && z==1 )
        {
            left();
        }
        else if(x==1 && y==0 && z==0 )
        {
            if(c==d)
            {
                right();
                delay(500);
            }
            else
            {
                c+=1;
                forward();
                delay(1000);
            }


        }


        else if(x==0 && y==1 && z==0)
        {
            break;
        }
        else
        {
            forward();
        }
        x = digitalRead(ir1);
        y = digitalRead(ir2);
        z = digitalRead(ir3);
        

    }




    Serial.print(x);
    Serial.print(y);
    Serial.print(z);
    stop();
    if(shoes())
    {
        lower();
    }
    else 
    {
        rise();
    }

    goHome();
}






void setup()
{
    Serial.begin(115200);
    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    Serial.println(IP);
    server.begin();
    pinMode(ir1,INPUT);
    pinMode(ir2,INPUT);
    pinMode(ir3,INPUT);

}




void loop()
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








