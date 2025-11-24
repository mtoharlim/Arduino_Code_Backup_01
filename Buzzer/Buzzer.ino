#include <Wire.h>
int Balarm = D7;   //Buzzer  alarm  connected to GPIO-14 or D5 of nodemcu
int PIRsensor = D3; //PIR sensor output connected to GPIO-5 or D1 of nodemcu
#define Serial

void setup() {

  //Serial.begin(115200);

  pinMode(PIRsensor, INPUT); // PIR sensor as input
  pinMode(Balarm, OUTPUT);   // Buzzer alaram as output
  digitalWrite (Balarm, LOW);// Initially buzzer off
}

void loop() {
  int state = digitalRead(PIRsensor); //Continuously check the state of PIR sensor
  delay(500);                         //Check state of PIR after every half second

  if (state == HIGH) {
    digitalWrite (Balarm, LOW);    //If intrusion detected ring the buzzer
    delay(500);
    //Ring buzzer for 15 seconds
    //Serial.print("Motion detected!");
  }
  else {
    digitalWrite (Balarm, LOW);     //No intrusion Buzzer off
    //Serial.print("Motion absent!");
  }
}
