const int SENSOR = A0;
const unsigned long INTERVAL = 1000;
unsigned long lastLog = 0;

void printTimestamp(unsigned long ms) {
  unsigned long totalSec = ms / 1000;
  unsigned long h = totalSec / 3600;
  unsigned long m = (totalSec % 3600) / 60;
  unsigned long s = totalSec % 60;
  unsigned long msPart = ms % 1000;
  char buf[16];
  snprintf(buf, sizeof(buf), "%02lu:%02lu:%02lu.%03lu", h, m, s, msPart);
  Serial.print(buf);
}

void setup() {
  Serial.begin(9600);
  Serial.println("timestamp,adc,temp_c");
}

void loop() {
  unsigned long now = millis();
  if (now - lastLog >= INTERVAL) {
    lastLog = now;

    int raw = analogRead(SENSOR);
    float tempC = raw * 5.0 / 1023.0 * 100.0;

    printTimestamp(now);
    Serial.print(",");
    Serial.print(raw);
    Serial.print(",");
    Serial.println(tempC, 1);
  }
}
