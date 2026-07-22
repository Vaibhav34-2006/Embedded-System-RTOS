void setup() {
  Serial.begin(9600);
  while (!Serial);
}

void loop() {
  Serial.println("Hello World");
//  Serial.println("Vaibhav Mali");
  delay(1000);
}