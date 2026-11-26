#include <Wire.h>

const byte SLAVE_ADDR = 8;
volatile int sensorValue = 0;

void receiveEvent(int count) {
  while (Wire.available()) {
    byte cmd = Wire.read();
    digitalWrite(LED_BUILTIN, cmd);
  }
}

void requestEvent() {
  Wire.write(highByte(sensorValue));
  Wire.write(lowByte(sensorValue));
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.begin(SLAVE_ADDR);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() {
  sensorValue = analogRead(A0);
  delay(50);
}
