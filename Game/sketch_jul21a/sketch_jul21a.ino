#include <Arduino_LSM9DS1.h>
#include <Arduino_APDS9960.h>

float x, y, z;
int proximity;

unsigned long lastSend = 0;
const int sendInterval = 50; // 20 times/sec — smooth for gameplay

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("IMU init failed!");
    while (1);
  }

  if (!APDS.begin()) {
    Serial.println("APDS9960 init failed!");
    while (1);
  }
}

void loop() {
  if (millis() - lastSend < sendInterval) return;
  lastSend = millis();

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
  }

  if (APDS.proximityAvailable()) {
    proximity = APDS.readProximity();
  }

  // Send as CSV: x,y,z,proximity
  Serial.print(x, 3);
  Serial.print(",");
  Serial.print(y, 3);
  Serial.print(",");
  Serial.print(z, 3);
  Serial.print(",");
  Serial.println(proximity);
}
