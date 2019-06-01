#include "reflex/types.h"

#define BASEADDRESS (uint8*)0x260
#define DIR_ADDRESS (uint8*)(BASEADDRESS + 0x4)
#define OUT_ADDRESS (uint8*)(BASEADDRESS + 0x3)

class LED{
	public:

	enum Color {red, green, blue};

	void turnOnLED(uint8 number, bool only = false);
	void turnOffLED(uint8 number);

	void displayNumber(uint8 number);
	
	void turnOnColor(Color color, bool only = false);
	void turnOffColor(Color color);

	LED() : DIR(DIR_ADDRESS), OUT(OUT_ADDRESS) {
		*DIR = 0xFF;	
	}

	private:
	
	uint8* const DIR;
	uint8* const OUT;
	void turnOn(uint8 number, bool only = false);
}
;






