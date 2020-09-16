
#define DELAY 500

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  delay(DELAY);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  delay(DELAY);
  Serial.println("Cycle");
}
