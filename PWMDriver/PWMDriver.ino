#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwmDriver = Adafruit_PWMServoDriver(0x40);

bool started = false;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(5000);
  Serial.println("Start...");
}

void loop() {
  delay(1000);
  if (!started) {
    started = pwmDriver.begin();
    if (started) {
      Serial.println("pwm started");
    } else {
      Serial.println("pwm failed");
      return;
    }
    started = pwmDriver.reset() && pwmDriver.setPWMFreq(250);
    if (started) {
      Serial.println("pwm reset");
    } else {
      Serial.println("pwm failed");
      return;
    }
    started = pwmDriver.setPWMFreq(250);
    if (started) {
      Serial.println("pwm frequence set");
    } else {
      Serial.println("pwm failed");
      return;
    }
  }
}
