#include "OneWire.h"

#define ONE_WIRE_PIN          12
// DS18S20 Temperature chip i/o
OneWire ds(ONE_WIRE_PIN);  // on pin 12

void printData(byte *data, int size, const char *separator) {
  for(int i = 0; i < size; i++) {
    if (i > 0) {
      Serial.print(separator);
    }
    if (data[i] < 0x10) {
      Serial.print("0");
    }
    Serial.print(data[i], HEX);
  }
}

size_t counter = 0;

void setup(void) {
  // initialize inputs/outputs
  // start serial port
  Serial.begin(115200);
}

void loop(void) {
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      Serial.print("Found: ");
      Serial.println(counter);
      Serial.println(" ");
      ds.reset_search();
      counter = 0;
      return;
  }

  ++counter;
  Serial.print("Address: ");
  printData(addr, 8, ":");

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.print(", CRC is not valid!\r\n");
      return;
  }

  if ( addr[0] == 0x10) {
      Serial.print(", DS18S20");
  }
  else if ( addr[0] == 0x28) {
      Serial.print(", DS18B20");
  }
  else {
      Serial.print("Device family is not recognized: 0x");
      Serial.println(addr[0],HEX);
      return;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);         // start conversion, with parasite power on at the end

  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.

  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  Serial.print(", P=");
  Serial.print(present,HEX);
  Serial.print(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  }
  printData(data, 9, ", ");
  Serial.print(", ");
  unsigned int raw = (data[1] << 8) | data[0];
  if (addr[0] == 0x10) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // count remain gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw << 3;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw << 2; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw << 1; // 11 bit res, 375 ms
    // default is 12 bit resolution, 750 ms conversion time
  }
  float celsius = (float)raw / 16.0;
  Serial.println(celsius);
}

