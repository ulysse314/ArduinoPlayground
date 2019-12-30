#include <Arduino.h>
#include <MTK3339.h>

Adafruit_GPS gps(&Serial1);

void setup() {
  Serial.begin(115200);
  gps.begin(115200);
  gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
  gps.sendCommand(PGCMD_ANTENNA);
}

void loop() {
  if (Serial1.available()) {
    gps.read();
    if (gps.newNMEAreceived()) {
      const char *nmea = gps.lastNMEA();
      gps.parse(nmea);
      Serial.print(nmea);
    }
  }
}
