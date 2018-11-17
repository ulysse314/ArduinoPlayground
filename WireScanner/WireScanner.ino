#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("I2C Scanner");
}

void loop() {
  int devicesFound = 0;
  Serial.println("Scanning...");
  for(byte address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      devicesFound++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
    } else {
      continue;
    }
    if (address < 16) {
      Serial.print("0");
    }
    Serial.println(address,HEX);
  }
  if (devicesFound == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("done\n");
  }
  delay(5000);
}
