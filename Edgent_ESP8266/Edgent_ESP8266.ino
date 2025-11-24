
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID           "TMPL3qRy1sXT"
#define BLYNK_DEVICE_NAME           "IOT flow direction"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"
BLYNK_WRITE(V0)
{
  int val = param.asInt();

  digitalWrite(D4, !val);
}
void setup()
{
  pinMode(D4, OUTPUT);
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
}
