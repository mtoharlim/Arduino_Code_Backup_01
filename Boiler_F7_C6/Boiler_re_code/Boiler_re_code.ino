
#include <ESP8266WiFi.h>
#include <TridentTD_LineNotify.h>
//#define SSID        "F7 TG Device"
//#define PASSWORD    "F07#APDEVICE@"
#define SSID        "MIN"
#define PASSWORD    "123456789"
#define LINE_TOKEN  "qwyx8nQeJEPpEmO9dqldcoIHEK5x5SkhWGk4lLUVsbo"

#define D3 0
#define D1 5
#define D2 4


int status_D3 = 1;
int status_D1 = 1;
int status_D2 = 1;

int cout = 0;
int cout_temp = 1;
int check = 1;


float t = 0;
void setup() {
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
  LINE.notify("Boiler Block C");

  pinMode(D3,INPUT_PULLUP);
  pinMode(D1,INPUT_PULLUP);
  pinMode(D2,INPUT_PULLUP);
}

void loop() {
  status_D3 = digitalRead(D3); // Run Mode
  status_D1 = digitalRead(D1); // High temp
  status_D2 = digitalRead(D2); // Low temp
  
  Serial.println("Status of Relay");
  Serial.print("  D3: ");
  Serial.print(status_D3);
  Serial.print("  D1: ");
  Serial.print(status_D1);
  Serial.print("  D2: ");
  Serial.println(status_D2);

// Run mode status -------------------------------------------------------
 if (status_D3 == 0){
    if(cout == 0){
      String LineText;
      String StatusBoiler = "Status Boiler: On  ";
      Serial.print("Status Boiler: On ");
      LINE.notify(StatusBoiler);
      cout = 1;  
    }  
    while(digitalRead(status_D1) == 1 && digitalRead(status_D2) == 1 ){ 
      check = 1;
      Serial.println(check);
      if(check == 1){
        String LineText;
        String SupplyNormal = " Supply Temp Normal. ";
        LINE.notify(SupplyNormal);
      }
      if (check > 10)  //-->900= Alarm to Time 15min
      {
        Serial.println("  Supply Temp Normal.");
        String SupplyNormal = " Supply Temp Normal. ";
        LINE.notify(SupplyNormal);
        check = 1;
      }
      delay(1000);
      check += 1;
      cout_temp = 0;
    } 
 }

// Hight temp status -------------------------------------------------------

  if (digitalRead(status_D1) == 0 ){
      Serial.println(check);
            if (check == 1){
              Serial.println("Supply Temp HIGH [More than 260 C]");
              String SupplyHIGH = " Supply Temp HIGH [More than 260 C] ";
              LINE.notify(SupplyHIGH);
              check += 1;
            }
            if(check>60){
              Serial.println("Supply Temp High [More than 260 C]!!!!");
              String SupplyHIGH1 = " Supply Temp High [More than 260 C]!!!! ";
              LINE.notify(SupplyHIGH1);
              check=1;
            }
            check+=1;
            delay(1000);
          }

// Low temp status -------------------------------------------------------   
    else if (digitalRead(status_D2) == 0 ){
      Serial.println(check);
          if(check == 1){
            Serial.println("Supply Temp LOW [Less than 248 C]");
            String SupplyLOW = " Supply Temp LOW [Less than 248 C]";
            LINE.notify(SupplyLOW);
            check+=1;
          }
          if(check > 60){
            Serial.println("Supply Temp Low [Less than 248 C]!!!!");
            String SupplyLOW1 = " Supply Temp LOW [Less than 248 C]!!!!";
            LINE.notify(SupplyLOW1);
            check = 1;
          }
          check += 1;
          delay(1000);
        } 
    // cout_temp!=0;
      

  else{
    if(cout <=1){
      Serial.println("Status Boiler: off");
      String BoilerOFF = " Status Boiler: off";
      LINE.notify(BoilerOFF);
      cout += 2;
      check = 0;
    }
  }
 delay (1000); 
}
    
 /**if (status_D1 == 0){
    //t = 40;
    String LineText;
    String string2 = "Temp High";
    //String string3 = " °C";
    LineText = string2;
    Serial.print("Line ");
    Serial.println(LineText);
    LINE.notify(LineText);

  }
  if (status_D2 == 0) {
    String string5 = " Temp Low ";
    Serial.print("Line ");
    Serial.println(string5);
    LINE.notify(string5);
  }**/

  
