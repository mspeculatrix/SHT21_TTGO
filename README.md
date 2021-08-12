# SHT21_TTGO

Machina Speculatrix :: https://mansfield-devine.com/speculatrix

## NOTE:
Based on the original SHT21 library by e-radionica.com.

Modified so that we can pass in a TwoWire instance, which has been created with non-standard SDA and SCL pins, on instantiation. This allows the library to work with devices, like the TTGO ESP32 boards, that have unusual I2C pin assignments.

## ORIGINAL:

### Description and details
Arduino library for interfacing [SHT21][breakout]  temperature and humidity sensor over I2C to Arduino. Simple to use, it enables reading temperature and humidity from the chip. Additionally, it uses checksum to check if data arrived from SHT21 is correctly transmitted.

### Docs
- [SHT21 breakout board by e-radionica.com] [breakout]
- [SHT21 breakout by e-r.io] [hardware]

### How to use?
Install as any Arduino library. Go to File -> Examples -> eRadionica_SHT21 -> *choose your example* and use!

## License info
This product is open-source. Yay!
For any tech questions, contact us at techsupport@e-radionica.com
If you find an Issue, please open one at GitHub. If you can improve our product, fork us.


