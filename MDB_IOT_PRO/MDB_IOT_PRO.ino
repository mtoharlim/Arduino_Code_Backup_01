
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPL3EEHnObQ"
#define BLYNK_DEVICE_NAME "000"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG
#define POTENTIOMETER_PIN A0

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI
#include "BlynkEdgent.h"



int LED1 = 2; // Assign LED1 to pin GPIO2
int LED2 = 16; // Assign LED2 to pin GPIO16
int percentage;


BlynkTimer timer;
float A2D = 0; // add



void sendSensor()
{
  int data = analogRead(POTENTIOMETER_PIN);
  int percentage = map(data, 0, 1023, 0, 100);
  
  Serial.print("Potentiometer : ");
  Serial.print(data);
  Serial.print("Percentage : ");
  Serial.print(percentage);

  
  
  //volt = (value/1023.0)*3.3;
   
}

BLYNK_WRITE(V1) // Executes when the value of virtual pin 0 changes
{
  Blynk.virtualWrite(V1,percentage);

}


// On LED1 on Nodemcu
BLYNK_WRITE(V2) // Executes when the value of virtual pin 0 changes
{
  if(param.asInt() == 0)
   {
    // execute this code if the switch widget is now ON
    digitalWrite(LED1,HIGH);  // Set digital pin 2 HIGH
   }
  else
    {
    // execute this code if the switch widget is now OFF
    digitalWrite(LED1,LOW);  // Set digital pin 2 LOW    
    }
}

// On LED2 on Nodemcu
BLYNK_WRITE(V3) // Executes when the value of virtual pin 0 changes
{
  if(param.asInt() == 0)
   {
    // execute this code if the switch widget is now ON
    digitalWrite(LED2,HIGH);  // Set digital pin 2 HIGH
   }
  else
    {
    // execute this code if the switch widget is now OFF
    digitalWrite(LED2,LOW);  // Set digital pin 2 LOW    
    }
}


void setup()
{

  // initialize GPIO2 and GPIO16 as an output
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  //pinMode(2, OUTPUT); // Initialise digital pin 2 as an output pin

 
  
  Serial.begin(115200);
  timer.setInterval(100L,sendSensor);

  BlynkEdgent.begin();
}

void loop() 
{
  
  BlynkEdgent.run();
  timer.run();
}
