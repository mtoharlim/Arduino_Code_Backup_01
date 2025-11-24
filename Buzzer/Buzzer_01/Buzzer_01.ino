//int Buzzer = 7; //for Arduino Microcontroller
int Buzzer = D7; //for ESP8266 Microcontroller
//int Buzzer = 4; //for ESP32 Microcontroller

void setup()
{
 
}

void loop()
{
    tone(14, 494, 500);
    delay(1000);
}
