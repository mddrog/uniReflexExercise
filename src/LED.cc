#include "LED.h"

void LED::turnOn(uint8 number, bool only){
	if(only == true){
		*OUT = number;
	}else{
		*OUT |= number;
	}
}

void LED::turnOnColor(Color color, bool only){

	uint8 number = 0;
	switch(color){
		case red: 
			number = ~(0x02|0x04|0x20|0x40);
		case green:
			number = ~(0x08|0x10);
		case blue:
			number = ~(0x01|0x80);
	}
	
	turnOn(number, only);	
}

void LED::turnOnNumber(uint8 number, bool only){

	if(number > 8 || number <=0){
		return;
	}

	turnOn(~(1<<(number-1)), only);
}


void LED::turnOffNumber(uint8 number){}

void LED::displayNumber(uint8 number){
	
	if(number > 255 || number < 0){
		return;
	}
	
	turnOn(~number, true);
}
	
void LED::turnOffColor(Color color){}

