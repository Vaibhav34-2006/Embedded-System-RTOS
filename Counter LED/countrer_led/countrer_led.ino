#include <Arduino_APDS9960.h>

void setup() {
  Serial.begin(9600);

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  // Turn OFF all LEDs
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);

  if (!APDS.begin()) {
    Serial.println("Failed to initialize APDS9960!");
    while (1);
  }

  Serial.println("=== Proximity Sensor Started ===");
}

void loop() {

  if (APDS.proximityAvailable()) {

    int proximity = APDS.readProximity();

    Serial.print("Proximity: ");
    Serial.println(proximity);

    // Turn OFF all LEDs
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, HIGH);

    if (proximity <= 80) {
      // RED
      digitalWrite(LEDR, LOW);
      Serial.println("RED LED ON");
    }
    else if (proximity <= 170) {
      // BLUE
      digitalWrite(LEDB, LOW);
      Serial.println("BLUE LED ON");
    }
    else {
      // GREEN
      digitalWrite(LEDG, LOW);
      Serial.println("GREEN LED ON");
    }

    delay(100);
  }
}