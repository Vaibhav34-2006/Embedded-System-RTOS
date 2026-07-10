/*
  APDS-9960 - Proximity Sensor controlling Grove RGB LCD Brightness

  Reads proximity data from the on-board APDS-9960 sensor of the
  Nano 33 BLE Sense. As distance increases, LCD backlight brightness increases.
  As distance decreases (object gets closer), brightness decreases.

  Proximity value reference:
  - 0   => close
  - 255 => far
  - -1  => error
*/

#include <Arduino_APDS9960.h>
#include <Wire.h>
#include <rgb_lcd.h>

rgb_lcd lcd;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  lcd.begin(16, 2);
  lcd.setRGB(0, 0, 0);
  lcd.setCursor(0, 0);
  lcd.print("Proximity Test");

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("APDS-9960 Error!");
    while (1);
  }
}

void loop() {
  // check if a proximity reading is available
  if (APDS.proximityAvailable()) {
    // read the proximity
    int proximity = APDS.readProximity();

    if (proximity >= 0) {
      // proximity is already 0 (close) to 255 (far)
      // use it directly as brightness: far = bright, close = dim
      int brightness = proximity;

      // set backlight brightness (white light, scaled)
      lcd.setRGB(brightness, brightness, brightness);

      // print value to the Serial Monitor
      Serial.print("Proximity: ");
      Serial.print(proximity);
      Serial.print("  Brightness: ");
      Serial.println(brightness);

      // update LCD text
      lcd.setCursor(0, 0);
      lcd.print("Proximity: ");
      lcd.print(proximity);
      lcd.print("   "); // clear leftover digits

      lcd.setCursor(0, 1);
      lcd.print("Bright: ");
      lcd.print(brightness);
      lcd.print("   ");
    } else {
      Serial.println("Proximity read error");
    }
  }

  // wait a bit before reading again
  delay(100);
}