/**********************************************
* INA219 library example
* 10 May 2012 by johngineer
*
* 9 January 2016 Flavius Bindea: changed default values and begin()
*
* this code is public domain.
**********************************************/


#include <Wire.h>
#include <INA219.h>

INA219 monitor(INA219::I2C_ADDR_41);


#define SHUNT_MAX_V 0.04  /* Rated max for our shunt is 75mv for 50 A current:
                             we will mesure only up to 20A so max is about 75mV*20/50 lets put some more*/
#define BUS_MAX_V   16.0  /* with 12v lead acid battery this should be enough*/
#define MAX_CURRENT 20    /* In our case this is enaugh even shunt is capable to 50 A*/
#define SHUNT_R   0.0015   /* Shunt resistor in ohm */
			     

void setup()
{
  Serial.begin(115200);
  monitor.begin();
  // begin calls:
  // configure() with default values RANGE_32V, GAIN_8_320MV, ADC_12BIT, ADC_12BIT, CONT_SH_BUS
  // calibrate() with default values D_SHUNT=0.1, D_V_BUS_MAX=32, D_V_SHUNT_MAX=0.2, D_I_MAX_EXPECTED=2
  // in order to work directly with ADAFruit's INA219B breakout
  monitor.calibrate(SHUNT_R, SHUNT_MAX_V, BUS_MAX_V, MAX_CURRENT);
 }

void loop()
{

  Serial.println("******************");
  
  Serial.print("raw shunt voltage: ");
  Serial.println(monitor.shuntVoltageRaw());
  
  Serial.print("raw bus voltage:   ");
  Serial.println(monitor.busVoltageRaw());
  
  Serial.println("--");
  
  Serial.print("shunt voltage: ");
  Serial.print(monitor.shuntVoltage() * 1000, 4);
  Serial.println(" mV");
  
  Serial.print("shunt current: ");
  Serial.print(monitor.shuntCurrent() * 1000, 4);
  Serial.println(" mA");
  
  Serial.print("bus voltage:   ");
  Serial.print(monitor.busVoltage(), 4);
  Serial.println(" V");
  
  Serial.print("bus power:     ");
  Serial.print(monitor.busPower() * 1000, 4);
  Serial.println(" mW");
  
  Serial.println(" ");
  Serial.println(" ");
  
  delay(1000);

}


