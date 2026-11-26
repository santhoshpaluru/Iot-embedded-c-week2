#include <Wire.h>

const byte SLAVE_ADDR = 8;
bool ledOn = false;

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(ledOn ? 1 : 0);
  Wire.endTransmission();
  ledOn = !ledOn;

  Wire.requestFrom(SLAVE_ADDR, (byte)2);
  if (Wire.available() >= 2) {
    int value = Wire.read() << 8;
    value |= Wire.read();
    Serial.print("Slave ADC value: ");
    Serial.println(value);
  } else {
    Serial.println("No response from slave");
  }

  delay(1000);
}
