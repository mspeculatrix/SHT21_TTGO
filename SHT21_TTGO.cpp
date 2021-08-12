#include <Arduino.h>
#include <SHT21_TTGO.h>

/*  In this file, the changes from the e-radionica.com original version are:
	- addition of a constructor
	- all instances of 'Wire.' have been replaced with 'wire->'
*/

//==============================================================================
// PUBLIC
//==============================================================================

// ** Added a constructor
SHT21_TTGO::SHT21_TTGO(TwoWire *twi): wire(twi ? twi : &Wire) {}

float SHT21_TTGO::getHumidity(void) {
	uint16_t result; 	// return variable
	
	result = readSensor_hm(TRIGGER_RH_MEASUREMENT_NHM);

	return CalcRH(result);
}

float SHT21_TTGO::getTemperature(void) {
	uint16_t result; 	// return variable
	
	result = readSensor_hm(TRIGGER_T_MEASUREMENT_NHM);

	return CalcT(result);
}

void SHT21_TTGO::reset() {
	wire->write(SOFT_RESET);
	wire->beginTransmission(I2C_ADD);
	wire->endTransmission();

	delay(15);	// wait for SHT to reset
}

uint8_t SHT21_TTGO::getSerialNumber(uint8_t return_sn) {

	uint8_t serialNumber[8];

	// read memory location 1
	wire->beginTransmission(I2C_ADD);
	wire->write(0xFA);
	wire->write(0x0F);
	wire->endTransmission();

	wire->requestFrom(I2C_ADD,8);
	while(wire->available() < 8) {}

	serialNumber[5] = wire->read();	// read SNB_3
	wire->read();					// CRC SNB_3 not used
	serialNumber[4] = wire->read();  // read SNB_2
	wire->read();					// CRC SNB_2 not used
	serialNumber[3] = wire->read();	// read SNB_1
	wire->read();					// CRC SNB_1 not used
	serialNumber[2] = wire->read();	// read SNB_0
	wire->read();					// CRC SNB_0 not used

	// read memory location 2
	wire->beginTransmission(I2C_ADD);
	wire->write(0xFC);
	wire->write(0xC9);
	wire->endTransmission();

	wire->requestFrom(I2C_ADD,6);
	while(wire->available() < 6) {}

	serialNumber[1] = wire->read();	// read SNC_1
	serialNumber[0] = wire->read();  // read SNC_0
	wire->read();					// CRC SNC_1/SNC_0 not used
	serialNumber[7] = wire->read();	// read SNA_1			
	serialNumber[6] = wire->read();	// read SNA_0
	wire->read();					// CRC SNA_1/SNA_0 not used

	return serialNumber[return_sn];
}

//==============================================================================
// PRIVATE
//==============================================================================

uint16_t SHT21_TTGO::readSensor_hm(uint8_t command) {
	uint8_t checksum;
	uint8_t data[2];
	uint16_t result;
	uint8_t n = 0;
	uint8_t d;
	
	if(command == TRIGGER_RH_MEASUREMENT_HM || command == TRIGGER_RH_MEASUREMENT_NHM) d = 30;
	if(command == TRIGGER_T_MEASUREMENT_HM || command == TRIGGER_T_MEASUREMENT_NHM) d = 85;
	
	wire->beginTransmission(I2C_ADD);
	wire->write(command);
	wire->endTransmission();
	delay(d);
	wire->requestFrom(I2C_ADD,3);
	
	while(wire->available() < 3) {
		delay(10);
		n++;
		if(n>10) return 0;
	}

	data[0] = wire->read(); 	// read data (MSB)
	data[1] = wire->read(); 	// read data (LSB)
	checksum = wire->read();	// read checksum

	result = (data[0] << 8);
	result += data[1];

	if(CRC_Checksum (data,2,checksum)) {
		reset();
		return 1;
	}

	else return result;
}

float SHT21_TTGO::CalcRH(uint16_t rh) {

	rh &= ~0x0003;	// clean last two bits

  	return (-6.0 + 125.0/65536 * (float)rh); // return relative humidity
}

float SHT21_TTGO::CalcT(uint16_t t) {

	t &= ~0x0003;	// clean last two bits
 	
	return (-46.85 + 175.72/65536 * (float)t);
}

uint8_t SHT21_TTGO::CRC_Checksum(uint8_t data[], uint8_t no_of_bytes, uint8_t checksum) {
	uint8_t crc = 0;	
  	uint8_t byteCtr;

 	 //calculates 8-Bit checksum with given polynomial
  	for (byteCtr = 0; byteCtr < no_of_bytes; ++byteCtr)
 	 { crc ^= (data[byteCtr]);
 	   for (uint8_t bit = 8; bit > 0; --bit)
 	   { if (crc & 0x80) crc = (crc << 1) ^ POLYNOMIAL;
 	     else crc = (crc << 1);
 	   }
 	 }
 	 if (crc != checksum) return 1;
 	 else return 0;
}
