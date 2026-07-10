
// UART demo on Arduino Nano 33 BLE
// Connect TX (D1) to RX (D0) for loopback
void setup() {
  // Start USB serial for debugging
  Serial.begin(9600);
  while (!Serial); // Wait for Serial monitor
  // Start hardware UART (Serial1)
  Serial1.begin(9600);
  Serial.println("UART Loopback Demo Started");
}
void loop() {
  // Send a message over UART
  Serial1.println("Hello via UART!");
  // Check if data is received back
  if (Serial1.available()) {
    String incoming = Serial1.readStringUntil('\n');
    Serial.print("Received: ");
    Serial.println(incoming);
  }
  delay(1000); // Wait 1 second
}
