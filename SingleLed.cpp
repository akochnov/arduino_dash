// 
// 
// 

#include "SingleLed.h"

SingleLedClass::SingleLedClass(uint8_t pin)
{
	_pin = pin;
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
	_state = false;
}


void SingleLedClass::show(KeyValueClass * data[], uint8_t size)
{
	if (size == 0) return;

	for (int i = 0; i < size / sizeof(data[0]); i++)
	{
		Keys key = data[i]->key();
		int value = data[i]->value();

		Serial.print(key);
		Serial.print(" : ");
		Serial.println(value);

		if (key == Mode) 
			if (value > 10)	_mode = value - 10;
			else _mode = value;
	}

	Serial.print("_mode is: ");
	Serial.println(_mode);
	switch (_mode)
	{
	case 0: blink(50, 2000); break;
	case 1: blink(150, 150); break;
	case 2: blink(1000, 150); break;
	}
}

void SingleLedClass::blink(int onTime, int OffTime)
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


