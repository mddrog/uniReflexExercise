#include "LED.h"

void LED::turnOn(uint8 number, bool only){
	if(only == true){
		*OUT = ~number;
	}else{
		*OUT &= ~number;
	}
}

void LED::turnOff(uint8 number){
	*OUT |= number;
}

void LED::toggleAll(){
	*OUT = ~(*OUT);
}

void LED::turnOnColor(Color color, bool only){
	turnOn(getColorLEDBits(color), only);	
}

uint8 LED::getColorLEDBits(Color color){
	
	uint8 number = 0;
	switch(color){
		case red: 
			number = redLEDBits;
			break;
		case green:
			number = greenLEDBits;
			break;
		case blue:
			number = blueLEDBits;
			break;
	}
	return number;
}

void LED::turnOnLED(uint8 number, bool only){

	if(number > 8 || number <=0){
		return;
	}

	turnOn((1<<(number-1)), only);
}


void LED::turnOffLED(uint8 number){

	if(number > 8 || number <=0){
		return;
	}

	turnOff((1<<(number-1)));
}

void LED::displayNumber(uint8 number){
	
	if(number > 255 || number < 0){
		return;
	}
	
	turnOn(number, true);
}
	
void LED::turnOffColor(Color color){
	turnOn(getColorLEDBits(color));
}


void LED::toggleLED(uint8 number){
	toggle((1<<(number-1)));
}

void LED::toggleColor(Color color){
	uint8 colorLEDBits = getColorLEDBits(color);
	toggle(colorLEDBits);
}

void LED::toggle(uint8 number){
	*OUT = (*OUT)^number;
}

void LED::turnOffAll(){
	turnOff(0xFF);
}
void LED::turnOnAll(){
	turnOn(0xFF);
}
