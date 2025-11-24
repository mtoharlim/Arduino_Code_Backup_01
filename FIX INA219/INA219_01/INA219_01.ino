#define BLYNK_PRINT Serial
#define BLYNK_MAX_READBYTES 512
#define TRIGGERPIN D5
#define ECHOPIN    D6
/****************************************************************************/

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <HCSR04.h>
#include <SimpleTimer.h>
#include "pitches.h"



BlynkTimer timer;
char auth[] = "lXYC0MzKY67gCxgzyN818l3D22KOxmRB";
char ssid[] = "iPhone";
char pass[] = "123456789";
char readyForDHTUpdate;
Adafruit_INA219 ina219;
float shuntvoltage = 0.00;
float busvoltage = 0.00;
float current_mA = 0.00; 
float loadvoltage = 0.00; 
float power = 0.00;
float energy = 0.00;
int flag = 0;
int buzzer = D7 ; //buzzer

// PIR-sensor
void notifyOnThings()
{
  int isButtonPressed = digitalRead(D3);
  if (isButtonPressed == 1 && flag == 0) {

    Blynk.notify("Alert : Alat Anda Telah Mendeteksi Pergerakkan ");//you can change this message
    flag = 1;

  }
  else if (isButtonPressed == 0)
  {
    flag = 0;
  }

}

// Buzzer
void beep(int note, int duration){
  tone(buzzer, note, duration);
  delay(duration);
}
// GRAFE-Blynk
void myTimerEvent()
{

  Blynk.virtualWrite(V4, loadvoltage);
  Blynk.virtualWrite(V5, current_mA);
  Blynk.virtualWrite(V6, power);

}
  
  BLYNK_CONNECTED()
 {
  Blynk.syncVirtual(V7) ;
 } 

//Bunyi Buzzer
  BLYNK_WRITE(V7)
  {
  int buttonState = param.asInt(); 
  if (buttonState == 1){ 
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(1000);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(1000);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(1000);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(1000);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(1000);
    digitalWrite(buzzer, HIGH);
    delay(500);}
  else {
    digitalWrite (buzzer, HIGH); }   
  }

  
void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  Serial.println("\n Starting");

  void setReadyForDHTUpdate(); {
    Serial.println("Setting readyForDHTUpdate to true");
    readyForDHTUpdate = true;
    Blynk.virtualWrite(V0, WiFi.RSSI());

  }

  //Ultrasonic sensor
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);

  //PIR-SENSOR
  pinMode(D3, INPUT_PULLUP);
  timer.setInterval(50L, notifyOnThings);

  //Buzzer
  pinMode (buzzer, OUTPUT) ;
  digitalWrite (buzzer, LOW);
  ina219.begin();
}

void loop(void) {
  // Fomular code
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  loadvoltage = busvoltage + (shuntvoltage / 1000); // V
  power = (current_mA / 1000) * loadvoltage * 1000; // mW
  energy = energy + (power / 1000 / 1000);

  BLYNK_READ(V1);//LOAD VOLTAGE
  {
    Blynk.virtualWrite(V1, String(loadvoltage, 4) + String(" V"));
  }

  BLYNK_READ(V2);//LOAD CURRENT
  {
    if (current_mA > 1000) {
      Blynk.virtualWrite(V2, String((current_mA / 1000), 3) + String(" A") );
    } else {
      Blynk.virtualWrite(V2, String(current_mA, 3) + String(" mA"));
    }
  }

  BLYNK_READ(V3);//LOAD POWER
  {
    if (power > 1000 ) {
      Blynk.virtualWrite(V3, String((power / 1000), 3) + String(" W") );
    } else {
      Blynk.virtualWrite(V3, String(power, 3) + String(" mW") );
    }
  }

  timer.setInterval(1000L, myTimerEvent);

  //Ultrasonic sensor
  long duration, distance;
  digitalWrite(TRIGGERPIN, LOW);
  delayMicroseconds(3);

  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(12);

  digitalWrite(TRIGGERPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration / 2) / 29.1;

  BLYNK_READ(V8);
  {
    Blynk.virtualWrite(V8, distance); //sending to Blynk
  }

 
  Blynk.run();
  timer.run();
}
