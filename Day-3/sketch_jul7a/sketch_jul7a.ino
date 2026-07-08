#include <Arduino_LSM9DS1.h>

void setup() {
  Serial.begin(9600);

  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  // Turn all LEDs OFF (RGB LEDs are active LOW)
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
}

void loop() {

  float x, y, z;

  if (IMU.accelerationAvailable()) {

    IMU.readAcceleration(x, y, z);

    // Turn OFF all LEDs first
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, HIGH);

    if (x > 0.5) {
      // RIGHT → Red
      digitalWrite(LEDR, LOW);
      Serial.println("RIGHT");
    }
    else if (x < -0.5) {
      // LEFT → Blue
      digitalWrite(LEDB, LOW);
      Serial.println("LEFT");
    }
    else if (y > 0.5) {
      // FRONT → Green
      digitalWrite(LEDG, LOW);
      Serial.println("FRONT");
    }
    else if (y < -0.5) {
      // BACK → Yellow (Red + Green)
      digitalWrite(LEDR, LOW);
      digitalWrite(LEDG, LOW);
      Serial.println("BACK");
    }
    else {
      Serial.println("CENTER");
    }

    delay(200);
  }
}