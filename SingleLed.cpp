// 
// 
// 

#include "SingleLed.h"

SingleLed::SingleLed(uint8_t pin)
{
	_pin = pin;
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
	_state = false;
}


void SingleLed::show(Vector<KeyValue> * data)
{
	for (int i = 0; i < (*data).size(); ++i)
	{
		KeyValue kv = (*data)[i];
		Keys key = kv.key();
		int value = kv.value();

		if (key == Mode) 
			if (value >= 10)	_mode = value - 10;
			else _mode = value;
	}

	switch (_mode)
	{
	case 0: blink(50, 2000); break;
	case 1: blink(150, 150); break;
	case 2: blink(1000, 150); break;
	case 3: blink(30, 30); break;
	}
}

void SingleLed::blink(int onTime, int OffTime)
{
	if (_state == true && (millis() - lastSwitchTime) > onTime)
	{
		digitalWrite(_pin, LOW);
		_state = false;
		lastSwitchTime = millis();
	}
	else if (_state == false && (millis() - lastSwitchTime) > OffTime)
	{
		digitalWrite(_pin, HIGH);
		_state = true;
		lastSwitchTime = millis();
	}
}