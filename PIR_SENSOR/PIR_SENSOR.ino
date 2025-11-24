//PIR motion detecting system

#define BLYNK_PRINT Serial
#define TRIGGERPIN D5
#define ECHOPIN    D6
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <HCSR04.h>

BlynkTimer timer;
char auth[] = "_Ev1pnlEofK02iKQD_0gmWJIcnRCbgsY";
char ssid[] = "MIN";
char pass[] = "123456789";
int flag=0;
WidgetLCD lcd(V6);

void notifyOnThings()
{
  int isButtonPressed = digitalRead(D3);
  if (isButtonPressed==1 && flag==0) {
    Serial.println("Alert : Alat Anda Telah Mendeteksi Pergerakkan ");//you can change this message
    Blynk.notify("Alert : Alat Anda Telah Mendeteksi Pergerakkan ");//you can change this message
    flag=1;
  }
  else if (isButtonPressed==0)
  { 
    flag=0;
  }
}
void setup()
{
  

Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
pinMode(TRIGGERPIN, OUTPUT);
pinMode(ECHOPIN, INPUT);
 lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(0, 0, "Distance in cm"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  // Please use timed events when LCD printintg in void loop to avoid sending too many commands
  // It will cause a FLOOD Error, and connection will be dropped 

pinMode(D3,INPUT_PULLUP);
timer.setInterval(50L,notifyOnThings); 
}
void loop()
{
  lcd.clear();
  lcd.print(0, 0, "Distance in cm"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  long duration, distance;
  digitalWrite(TRIGGERPIN, LOW);  
  delayMicroseconds(3); 
  
  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(12); 
  
  digitalWrite(TRIGGERPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println("Cm");
  lcd.print(7, 1, distance);


  delay(1000);
  Blynk.run();
  timer.run();
}
