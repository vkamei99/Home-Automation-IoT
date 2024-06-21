#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C LCD(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  
  LCD.init();
  LCD.backlight();
  LCD.setCursor(0, 0);
  LCD.print("VIktor Kamei");
  LCD.setCursor(0, 1);
  LCD.print("Sist. Embarcados 1");
}

void loop() {
  delay(250);
}
