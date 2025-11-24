#include <ESP8266WiFi.h>
#include <TridentTD_LineNotify.h>
#define SSID        "F7 TG Device"
#define PASSWORD    "F07#APDEVICE@"
//#define SSID        "MIN"
//#define PASSWORD    "123456789"
#define LINE_TOKEN  "X9i4GdCSZkbZgd4YseLdxAqSChWYmOSo63j92JKwDuE"

#define D1 5
#define D2 4

int status_D1 = 1;
int status_D2 = 1;

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
  LINE.notify("MDB Room Block C");

  pinMode(D1,INPUT_PULLUP);
  pinMode(D2,INPUT_PULLUP);
}

void loop() {
  status_D1 = digitalRead(D1);
  status_D2 = digitalRead(D2);

  Serial.print("Status of Relay");
  Serial.print("  D1: ");
  Serial.print(status_D1);
  Serial.print("  D2: ");
  Serial.println(status_D2);
      
  if (status_D2 == 0){
    //t = 40;
    String LineText;
    String string2 = "Block C over temperature !!! ";
    //String string3 = " °C";
    LineText = string2;
    Serial.print("Line ");
    Serial.println(LineText);
    LINE.notify(LineText);

    //if (status_D2 == 0){
      //String string4 = "อุณหภูมิกลับมาเป็นปกติ ";
      //Serial.print("Line ");
      //Serial.println(string4);
      //LINE.notify(string4);
    //}
  }
  if (status_D2 == 1) {
    String string5 = "อุณหภูมิปกติ ";
    Serial.print("Line ");
    Serial.println(string5);
    //LINE.notify(string5);
  }
  delay (1000);
}
