const int LM35_PIN = A0;
const int LDR_PIN = A1;
const int TRIG = 9;
const int ECHO = 10;
const int BUZZER = 8;

const float TEMP_LIMIT = 35.0;
const float DIST_LIMIT = 15.0;
const int LIGHT_LIMIT = 200;

const unsigned long INTERVAL = 1000;
unsigned long lastLog = 0;

float readTemperature() {
  int raw = analogRead(LM35_PIN);
  return raw * 5.0 / 1023.0 * 100.0;
}

float readDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  unsigned long duration = pulseIn(ECHO, HIGH, 30000);
  if (duration == 0) return -1;
  return duration * 0.0343 / 2.0;
}

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
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
  Serial.println("timestamp,temp_c,distance_cm,light,alert");
}

void loop() {
  unsigned long now = millis();
  if (now - lastLog < INTERVAL) return;
  lastLog = now;

  float tempC = readTemperature();
  float distance = readDistance();
  int light = analogRead(LDR_PIN);

  bool hot = tempC > TEMP_LIMIT;
  bool close = distance > 0 && distance < DIST_LIMIT;
  bool dark = light < LIGHT_LIMIT;
  bool alert = hot || close || dark;

  printTimestamp(now);
  Serial.print(",");
  Serial.print(tempC, 1);
  Serial.print(",");
  Serial.print(distance, 1);
  Serial.print(",");
  Serial.print(light);
  Serial.print(",");
  if (hot) Serial.print("HOT ");
  if (close) Serial.print("CLOSE ");
  if (dark) Serial.print("DARK");
  if (!alert) Serial.print("OK");
  Serial.println();

  if (alert) {
    tone(BUZZER, 1500, 300);
  }
}
