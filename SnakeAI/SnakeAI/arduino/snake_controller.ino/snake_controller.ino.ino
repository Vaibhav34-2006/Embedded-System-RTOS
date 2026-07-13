#include <Arduino_LSM9DS1.h>

String lastDirection = "";

void setup() {

  Serial.begin(115200);

  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("IMU Failed");
    while (1);
  }
}

void loop() {

  float x, y, z;

  if (IMU.accelerationAvailable()) {

    IMU.readAcceleration(x, y, z);

    String direction = "CENTER";

    if (x > 0.45)
      direction = "RIGHT";

    else if (x < -0.45)
      direction = "LEFT";

    else if (y > 0.45)
      direction = "UP";

    else if (y < -0.45)
      direction = "DOWN";

    if (direction != lastDirection) {

      Serial.println(direction);

      lastDirection = direction;

    }

    delay(50);
  }
}