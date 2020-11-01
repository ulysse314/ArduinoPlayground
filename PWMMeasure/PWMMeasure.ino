#define VALUES 20
#define START_VALUE HIGH

const byte interruptPin = 2;
volatile int counter = 0;
volatile unsigned long long timerValues[VALUES];

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), interrupt, CHANGE);
  Serial.println("start");
}

void loop() {
  if (counter >= VALUES) {
    digitalWrite(LED_BUILTIN, LOW);
    for (int ii = 0; ii < VALUES - 2; ii += 2) {
      int phase1 = timerValues[ii + 1] - timerValues[ii];
      int phase2 = timerValues[ii + 2] - timerValues[ii + 1];
      Serial.print("Phase 1: ");
      Serial.print(phase1);
      Serial.print(", phase 2: ");
      Serial.print(phase2);
      Serial.print(", total: ");
      Serial.print(phase1 + phase2);
      Serial.print(" (");
      Serial.print((double)phase1 * 100. / (phase1 + phase2));
      Serial.print("%, ");
      Serial.print((double)phase2 * 100. / (phase1 + phase2));
      Serial.print("%), frequence: ");
      Serial.print(1000000. / (phase1 + phase2));
      Serial.println("Hz");
    }
    Serial.println("--");
    Serial.println("");
    delay(5000);
    digitalWrite(LED_BUILTIN, HIGH);
    counter = 0;
  }
}

void interrupt() {
  unsigned long long time = micros();
  if (counter < VALUES) {
    if (counter == 0 && digitalRead(interruptPin) != START_VALUE) {
      return;
    }
    timerValues[counter++] = time;
  }
}
