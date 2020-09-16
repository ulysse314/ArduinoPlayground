#include <Wire.h>
#include <BNO055.h>

BNO055 bno055;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  while(true) {
    if (bno055.begin()) {
      break;
    }
    Serial.println("BNO055 not found");
    delay(5000);
  }
}

void printVector(imu::Vector<3> vector) {
  Serial.print("x: ");
  Serial.println(vector.x());
  Serial.print("y: ");
  Serial.println(vector.y());
  Serial.print("z: ");
  Serial.println(vector.z());
}

void loop() {
  unsigned long long start = micros();
  unsigned long long diff = micros() - start;
  Serial.println((long int)diff);
  imu::Vector<3> euler;
  if (!bno055.getVector(BNO055::VECTOR_EULER, &euler)) {
    Serial.println("Euler not available");
  } else {
    printVector(euler);
  }
  imu::Vector<3> mag;
  if (!bno055.getVector(BNO055::VECTOR_MAGNETOMETER, &mag)) {
    Serial.println("Mag not available");
  } else {
    printVector(mag);
  }
  Serial.println(" ");
  delay(500);
}
