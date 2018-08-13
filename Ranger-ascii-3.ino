#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"
#include <Wire.h>
#include "Adafruit_VL53L0X.h"
#include <SPI.h>

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN -1

SSD1306AsciiAvrI2c oled;

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(9600);

  #if RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
  #else // RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  #endif // RST_PIN >= 0
  Wire.begin();

  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, true); // pass in 'true' to get debug data printout!

  oled.setFont(Adafruit5x7); //without font no text is printed

  oled.clear();
  oled.println("---------------------");
  oled.println("--laser-rangefinder--");
  oled.set2X();
  oled.print("mm : ");
  oled.println(measure.RangeMilliMeter);
  oled.set1X();

  delay(250);
}
