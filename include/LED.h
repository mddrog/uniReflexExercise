#include "reflex/types.h"

#define BASEADDRESS (uint8*)0x260
#define DIR_ADDRESS (uint8*)(BASEADDRESS + 0x4)
#define OUT_ADDRESS (uint8*)(BASEADDRESS + 0x3)
#define RED_LED_BITS (0x02|0x04|0x20|0x40)
#define GREEN_LED_BITS (0x08|0x10)
#define BLUE_LED_BITS (0x01|0x80)

class LED{
	public:

	enum Color {red, green, blue};

	void turnOnLED(uint8 number, bool only = false);
	void turnOffLED(uint8 number);
	void toggleLED(uint8 number);

	void displayNumber(uint8 number);
	
	void turnOnColor(Color color, bool only = false);
	void turnOffColor(Color color);
	void toggleColor(Color color);

	void toggleAll();
	void turnOnAll();
	void turnOffAll();

	LED() : 
		DIR(DIR_ADDRESS), 
		OUT(OUT_ADDRESS),
		redLEDBits(RED_LED_BITS),
		greenLEDBits(GREEN_LED_BITS),
		blueLEDBits(BLUE_LED_BITS)
	{
		*DIR = 0xFF;
		*OUT = 0xFF;	
	}

	private:
	
	volatile uint8* const DIR;
	volatile uint8* const OUT;
	uint8 const redLEDBits;
	uint8 const greenLEDBits;
	uint8 const blueLEDBits;
	void turnOn(uint8 number, bool only = false);
	void turnOff(uint8 number);
	uint8 getColorLEDBits(Color color);
	void toggle(uint8 number);
}
;






