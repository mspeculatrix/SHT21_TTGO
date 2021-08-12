// Modified version of original by:
//==============================================================================
//    E - R A D I O N I C A . C O M,  H.Kolomana 6/A, Djakovo 31400, Croatia
//==============================================================================
// Project   :  SHT21 Arduino Library
// File      :  SHT21 Demo Arduino Example
// Author    :  e-radionica.com 2017
// Licence   :  Open-source ! 
//==============================================================================
//==============================================================================
// Use with any SHT21 breakout. Check ours: 
// https://e-radionica.com/en/sht21-humidity-and-temperature-sensor.html
// Shows temperature and humidity from SHT21 sensor in Serial monitor.
// If any questions, 
// just contact techsupport@e-radionica.com
//==============================================================================

#define SDA 4       // Pin for I2C SDA
#define SCL 15      // Pin for I2C SCL          

#include <SHT21_TTGO.h>  // include SHT21 library

TwoWire twi = TwoWire(1);
SHT21_TTGO sht = SHT21_TTGO(&twi);

float temp; 	// variable to store temperature
float humidity; // variable to store hemidity

void setup() {
  twi.begin(SDA,SCL);	// begin I2C
  Serial.begin(9600);   // begin Serial
}

void loop() {

  temp = sht.getTemperature();  // get temp from SHT 
  humidity = sht.getHumidity(); // get temp from SHT

  Serial.print("Temp: ");			// print readings
  Serial.print(temp);
  Serial.print("\t Humidity: ");
  Serial.println(humidity);

  delay(85);	// min delay for 14bit temp reading is 85ms
}
