#include <dummy.h>

#include <dummy.h>

#include <ArduinoWiFiServer.h>
#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiGratuitous.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>

#include <ArduinoWiFiServer.h>
#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiGratuitous.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>

void Line_Notify(String message) ; 
#include <ESP8266WiFi.h>
//#include <WiFiClientSecureAxTLS.h> // กรณีขึ้น Error ให้เอาบรรทัดนี้ออก
  // Config connect WiFi
#define WIFI_SSID "MIN"
#define WIFI_PASSWORD "123456789"
  
//#define WIFI_SSID "F7 TG Device"
//#define WIFI_PASSWORD "F07#APDEVICE@"
  // Line config
//#define LINE_TOKEN "KP1xxVPRjC2zkfBruEXNaskHYLQbaBH4qL2gnVFr4US" //khalang
#define LINE_TOKEN "kGHtMJ85e3l3PCzs2jbvfiPhnWknDlqpoV2T4sOlm7M"  //Token for Boiler C6


#define high_temp1 D4
#define low_temp1 D2
#define run_mode D7

String tempHIGH1 = "260";
String tempHIGH2 = "255";
String tempHIGH3 = "250";
String tempLOW1  = "248";
String tempLOW2  = "245";
String tempLOW3  = "240";
String message = "";
String message_tempHIGH = " Supply Temp HIGH [More than 260 C]"; 
String message_tempLOW = " Supply Temp LOW [Less than 230 C]";
String message_tempINSPEC = " Supply Temp Normal. ";
String message_furnaceOver = " furnace Negative pressure OVER standard ";
String message_furnaceLower = " furnace Negative pressure LOWER standard ";
String message_pressureINSPEC = " furnace Negative pressur IN SPEC ";
String message_statusBoiler_On = " Status Boiler [On] ";
String message_statusBoiler_Off = " Status Boiler [off] ";
String message_hello = "starting system";
int cout = 0;
int cout_temp = 1;
int check=1;
int Boiler_off =0 , Boiler_on =0;

void setup() {
  pinMode(high_temp1, INPUT_PULLUP);
  pinMode(low_temp1, INPUT_PULLUP);
  pinMode(run_mode, INPUT_PULLUP);
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  // connect to wifi.

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);  
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Line_Notify(message_hello);
}

void loop()
{
  Serial.print("parametor : ");
  Serial.print(digitalRead(high_temp1));
  Serial.println(digitalRead(low_temp1));   
  
  if(digitalRead(run_mode) == LOW)
  {
    if(digitalRead(run_mode) == LOW && Boiler_on == 0)
    {
      Serial.println("Status Boiler: On");
      Line_Notify(message_statusBoiler_On);
      cout_temp=0;
      check=1;
      cout=1;
      Boiler_off =0;
      Boiler_on =1;
    } 

    
  // Normal Function//  
    if (digitalRead(high_temp1) == HIGH && digitalRead(low_temp1) == HIGH)
    { 
          Serial.println(check);
          if(cout_temp==1)
          {
             Line_Notify(message_tempINSPEC);
             cout_temp=1;
          }

//-->3600= Alarm to Time 1h
          else if (check>10)  
          {
             Serial.println("  Supply Temp Normal.");
             Line_Notify(message_tempINSPEC);
             check=1;
           }
           delay(1000);
           check+=1;
           cout_temp+=1;
    }


    else if (digitalRead(high_temp1) == LOW)
    {
          Serial.println(check);
           if(cout_temp!=0)
          {
             Serial.println("Supply Temp HIGH [More than 260 C]");
             Line_Notify(message_tempHIGH);
             cout_temp=0;
             check=1;
          }
//-->180= Alarm Temp HIGH to Time 3min    
      if(check>10 && cout_temp==0){
        Serial.println("Supply Temp HIGH [More than 260 C]");
        Line_Notify(message_tempHIGH);
        check=1;
      }
      check+=1;
      delay(1000);
    }

    
    else if (digitalRead(low_temp1) == LOW)
    {
      Serial.println(check);
      if(cout_temp!=0){
        Serial.println("Supply Temp LOW [Less than 230 C]");
        Line_Notify(message_tempLOW);
        check=1;
      }
      cout_temp=0;
//-->180= Alarm Temp LOW to Time 3min 
      if(check>10 && cout_temp==0 ){
        Serial.println("Supply Temp LOW [Less than 230 C]");
        Line_Notify(message_tempLOW);
        check=0;
      }
      check+=1;
      delay(1000);
    } 
  }     

  else if(digitalRead(run_mode) == HIGH && Boiler_off==0)
    {
      Serial.println("Status Boiler: off");
      Line_Notify(message_statusBoiler_Off);
      Boiler_off =1;
      Boiler_on =0;
    }

  else if(digitalRead(run_mode) == HIGH)
    {
      Serial.println("Status Boiler: off");
      delay(1000);
    }
   
}

void Line_Notify(String message) {
  WiFiClientSecure client; // กรณีขึ้น Error ให้ลบ axTLS:: ข้างหน้าทิ้ง

  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
    return;   
  }

  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP8266\r\n";
  req += "Connection: close\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + message;

  client.print(req);
    
  delay(20);


  while(client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }
}
