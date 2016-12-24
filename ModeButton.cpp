// Mode Button Class
// Switching between modes by clicking the button
// Longpress to set dimmer

#include "ModeButton.h"

#define HOLD_TIME_TRESHHOLD		1500


ModeButtonClass::ModeButtonClass(uint8_t pin) : Button(pin, BUTTON_PULLUP_INTERNAL, true, 70)
{

}

Keys ModeButtonClass::getKey() 
{ 
	return Mode; 
}

uint8_t ModeButtonClass::getValue()
{ 
	Button::process();
	
	//Hanlde long press
	if (Button::held(HOLD_TIME_TRESHHOLD, false))
	{
		dim = !dim;
		dimSwitched = true;			//avoid onpress event when hold event just triggered
	}
	
	//Hanlde press event when button switches off
	if (Button::stateChanged(false) && !Button::isPressed(false))
	{
		if (dimSwitched)
		{
			dimSwitched = false;
		}
		else
		{
			this->nextMode();
		}
	}
	
	//Calculating current state of the switch
	uint8_t state = mode;
	if (dim) state += 10;

	return state; 
}

void ModeButtonClass::nextMode()
{
	mode++;
	if (mode > 3) mode = 0;
}




