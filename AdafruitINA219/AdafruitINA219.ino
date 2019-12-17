/**********************************************
* INA219 library example
* 10 May 2012 by johngineer
*
* 9 January 2016 Flavius Bindea: changed default values and begin()
*
* this code is public domain.
**********************************************/


#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 monitor(0x41);


void setup()
{
  Serial.begin(115200);
  monitor.begin();
  // begin calls:
  // configure() with default values RANGE_32V, GAIN_8_320MV, ADC_12BIT, ADC_12BIT, CONT_SH_BUS
  // calibrate() with default values D_SHUNT=0.1, D_V_BUS_MAX=32, D_V_SHUNT_MAX=0.2, D_I_MAX_EXPECTED=2
  // in order to work directly with ADAFruit's INA219B breakout
}

void loop()
{

  Serial.println("******************");
  
  Serial.print("raw shunt voltage: ");
  Serial.println(monitor.getShuntVoltage_raw());
  
  Serial.print("raw bus voltage:   ");
  Serial.println(monitor.getBusVoltage_raw());
  
  Serial.println("--");
  
  Serial.print("shunt voltage: ");
  Serial.print(monitor.getShuntVoltage_mV() * 1000, 4);
  Serial.println(" mV");
  
  Serial.print("shunt current: ");
  Serial.print(monitor.getCurrent_mA() * 1000, 4);
  Serial.println(" mA");
  
  Serial.print("bus voltage:   ");
  Serial.print(monitor.getBusVoltage_V(), 4);
  Serial.println(" V");
  
  Serial.print("bus power:     ");
  Serial.print(monitor.getPower_mW() * 1000, 4);
  Serial.println(" mW");
  
  Serial.println(" ");
  Serial.println(" ");
  
  delay(1000);

}

