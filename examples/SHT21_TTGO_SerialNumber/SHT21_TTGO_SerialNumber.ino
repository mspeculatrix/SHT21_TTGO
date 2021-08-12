// Modified version of original by:
//==============================================================================
//    E - R A D I O N I C A . C O M,  H.Kolomana 6/A, Djakovo 31400, Croatia
//==============================================================================
// Project   :  SHT21 Arduino Library
// File      :  SHT21 Serial Number Example
// Author    :  e-radionica.com 2017
// Licence   :  Open-source ! 
//==============================================================================
//==============================================================================
// Use with any SHT21 breakout. Check ours: 
// https://e-radionica.com/en/sht21-humidity-and-temperature-sensor.html
// Prints hardcored SHT21 Serial Number to Serial monitor.
// If any questions, 
// just contact techsupport@e-radionica.com
//==============================================================================

#define SDA 4       // Pin for I2C SDA
#define SCL 15      // Pin for I2C SCL          

#include <SHT21_TTGO.h>

TwoWire twi = TwoWire(1);
SHT21_TTGO sht = SHT21_TTGO(&twi);

void setup() {
  twi.begin(SDA,SCL);    // begin I2C
  Serial.begin(9600);    // begin Serial

  // call following as argument in getSerialNumber function to print SN
  //		0 - for SNC_0
  //		1 - for SNC_1
  //		2 - for SNB_0
  //		3 - for SNB_1
  //		4 - for SNB_2
  //		5 - for SNB_3
  //		6 - for SNA_0
  //		7 - for SNA_1

  // printing all serial numbers to Serial monitor
  for(int i= 0; i < 8; i++)
  {
    Serial.print(sht.getSerialNumber(0),BIN);
  }
}

void loop() {
}
