const int SENSOR = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(SENSOR);
  float volts = raw * 5.0 / 1023.0;
  float tempC = volts * 100.0;

  Serial.print("ADC: ");
  Serial.print(raw);
  Serial.print("  Voltage: ");
  Serial.print(volts, 2);
  Serial.print(" V  Temperature: ");
  Serial.print(tempC, 1);
  Serial.println(" C");

  delay(1000);
}
