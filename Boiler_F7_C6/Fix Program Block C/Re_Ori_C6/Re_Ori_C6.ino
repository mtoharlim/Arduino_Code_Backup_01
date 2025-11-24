#include <ESP8266WiFi.h>
#include <TridentTD_LineNotify.h>

//void Line_Notify(String message) ; 

//#include <WiFiClientSecureAxTLS.h> // กรณีขึ้น Error ให้เอาบรรทัดนี้ออก
  // Config connect WiFi
//#define SSID "MIN"
//#define PASSWORD "123456789"
  
#define SSID "F7 TG Device"
#define PASSWORD "F07#APDEVICE@"
 
  // Line config
//#define LINE_TOKEN "qwyx8nQeJEPpEmO9dqldcoIHEK5x5SkhWGk4lLUVsbo" //Min
#define LINE_TOKEN "xZpMAzHNWMkFqAHCNPVkor9wPmXlAMD4joD9B3sPNYq"  //Token for Boiler C6


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
String message_tempHIGH = " Boiler C6: Supply Temp HIGH [ More than 260 C ] ⚠ "; 
String message_tempLOW = " Boiler C6: Supply Temp LOW [ Less than 245 C ] ⚠ ";
String message_tempINSPEC = " Boiler C6: Supply Temp [ Normal ]  ";
String message_furnaceOver = " furnace Negative pressure OVER standard ";
String message_furnaceLower = " furnace Negative pressure LOWER standard ";
String message_pressureINSPEC = " furnace Negative pressur IN SPEC ";
String message_statusBoiler_On = " Boiler C6: Status Boiler [ On ] ";
String message_statusBoiler_Off = " Boiler C6: Status Boiler [ off ] ";
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
  Serial.println();
  Serial.println(LINE.getVersion());
 
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());\

  // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);
  LINE.notify(" Notify Boiler Block C ");

}

void loop() {
  Serial.print("parametor : ");
  Serial.print(digitalRead(high_temp1));
  Serial.println(digitalRead(low_temp1));   
  
  if(digitalRead(run_mode) == LOW)
  {
    if(digitalRead(run_mode) == LOW && Boiler_on == 0)
    {
      Serial.println("Status Boiler: On");
      LINE.notify(message_statusBoiler_On);
      cout_temp=0;
      check=1;
      cout=1;
      Boiler_off =0;
      Boiler_on =1;
    } 

    
// Normal Function -----------------------------------------------------------------  
    if (digitalRead(high_temp1) == HIGH && digitalRead(low_temp1) == HIGH)
    { 
          Serial.println(check);
          if(cout_temp==1)
          {
             LINE.notify(message_tempINSPEC);
             cout_temp=1;
          }

//-->3600= Alarm to Time 1h ------------------------------------------------------
          else if (check>3600)  
          {
             Serial.println("  Supply Temp Normal. ");
             LINE.notify(message_tempINSPEC);
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
             LINE.notify(message_tempHIGH);
             cout_temp=0;
             check=1;
          }

//-->180= Alarm Temp HIGH to Time 3min ---------------------------------------------    
      if(check>180 && cout_temp==180){
        Serial.println("Supply Temp HIGH [More than 260 C]");
        LINE.notify(message_tempHIGH);
        check=1;
      }
      check+=1;
      delay(1000);
    }

    
    else if (digitalRead(low_temp1) == LOW)
    {
      Serial.println(check);
      if(cout_temp!=0){
        Serial.println("Supply Temp LOW [Less than 245 C]");
        LINE.notify(message_tempLOW);
        check=1;
      }
      cout_temp=0;
      
//-->180= Alarm Temp LOW to Time 3min ----------------------------------------------
      if(check>180 && cout_temp==0 ){
        Serial.println("Supply Temp LOW [Less than 245 C]");
        LINE.notify(message_tempLOW);
        check=0;
      }
      check+=1;
      delay(1000);
    } 
  }     

  else if(digitalRead(run_mode) == HIGH && Boiler_off==0)
    {
      Serial.println("Status Boiler: off");
      LINE.notify(message_statusBoiler_Off);
      Boiler_off =1;
      Boiler_on =0;
    }

  else if(digitalRead(run_mode) == HIGH)
    {
      Serial.println("Status Boiler: off");
      delay(1000);
    }

  delay(100);
 }
 
  

  
