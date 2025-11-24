#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
void setup() {
lcd.begin();
lcd.backlight();
lcd.setCursor(3, 0);
lcd.print(“Welcome to”);
lcd.setCursor(1, 1);
lcd.print(“indomaker.com”);  
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
