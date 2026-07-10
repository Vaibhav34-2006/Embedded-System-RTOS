/*
  APDS-9960 - Gesture Sensor with Grove RGB LCD output

  Reads gesture data from the on-board APDS-9960 sensor of the
  Nano 33 BLE Sense and displays detected gestures on a Grove RGB LCD (I2C).
*/

#include <Arduino_APDS9960.h>
#include <Wire.h>
#include <rgb_lcd.h>

rgb_lcd lcd;

// Grove RGB LCD backlight color (feel free to change)
const int colorR = 0;
const int colorG = 128;
const int colorB = 255;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  lcd.print("Gesture Sensor");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");

  // Initialize gesture sensor
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("APDS-9960 Error!");
    while (1); // halt, since sensor isn't working
  }

  // for setGestureSensitivity(..) a value between 1 and 100 is required.
  // Higher values make the gesture recognition more sensitive but less accurate.
  // Lower values make it more accurate but less sensitive. Default is 80
  //APDS.setGestureSensitivity(80);

  Serial.println("Detecting gestures ...");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Detecting");
  lcd.setCursor(0, 1);
  lcd.print("gestures...");
}

void loop() {
  if (APDS.gestureAvailable()) {
    int gesture = APDS.readGesture();
    String gestureText = "";

    switch (gesture) {
      case GESTURE_UP:
        gestureText = "UP";
        break;

      case GESTURE_DOWN:
        gestureText = "DOWN";
        break;

      case GESTURE_LEFT:
        gestureText = "LEFT";
        break;

      case GESTURE_RIGHT:
        gestureText = "RIGHT";
        break;

      default:
        // ignore unknown gestures
        return;
    }

    Serial.println("Detected " + gestureText + " gesture");

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Gesture:");
    lcd.setCursor(0, 1);
    lcd.print(gestureText);
  }
}
which one is this onevoid setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
