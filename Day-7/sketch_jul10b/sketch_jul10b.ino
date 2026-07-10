#include <Wire.h>
#include <Arduino_APDS9960.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

// Define basic color thresholds (tweak based on your testing)
struct ColorRange {
  const char* name;
  int rMin, rMax;
  int gMin, gMax;
  int bMin, bMax;
};

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor!");
    while (1);
  }

  lcd.begin(16, 2);       // 16x2 Grove RGB LCD
  lcd.setRGB(255, 255, 255);
  lcd.print("Color Sensor");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(1500);
  lcd.clear();
}

String detectColorName(int r, int g, int b) {
  // Normalize roughly and classify — adjust thresholds after testing your sensor
  if (r > g && r > b && r > 100) return "Red";
  if (g > r && g > b && g > 100) return "Green";
  if (b > r && b > g && b > 100) return "Blue";
  if (r > 150 && g > 150 && b < 100) return "Yellow";
  if (r > 150 && b > 150 && g < 100) return "Purple";
  if (r < 60 && g < 60 && b < 60) return "Black";
  if (r > 200 && g > 200 && b > 200) return "White";
  return "Unknown";
}

void loop() {
  int r, g, b, a;

  if (APDS.colorAvailable()) {
    APDS.readColor(r, g, b, a);

    String colorName = detectColorName(r, g, b);

    // Print to Serial Monitor
    Serial.print("R: "); Serial.print(r);
    Serial.print(" G: "); Serial.print(g);
    Serial.print(" B: "); Serial.print(b);
    Serial.print(" -> Color: "); Serial.println(colorName);

    // Print to LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Detected:");
    lcd.setCursor(0, 1);
    lcd.print(colorName);

    // Optional: set LCD backlight to match detected color mood
    if (colorName == "Red") lcd.setRGB(255, 0, 0);
    else if (colorName == "Green") lcd.setRGB(0, 255, 0);
    else if (colorName == "Blue") lcd.setRGB(0, 0, 255);
    else if (colorName == "Yellow") lcd.setRGB(255, 255, 0);
    else lcd.setRGB(255, 255, 255);

    delay(1000);
  }
}