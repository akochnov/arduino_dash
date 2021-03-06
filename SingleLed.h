// SingleLed.h

#ifndef _SINGLELED_h
#define _SINGLELED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "IDisplay.h"
#include "IDataProvider.h"
#include "Vector.h"

class SingleLed : public IDisplay
{

public:
	SingleLed(uint8_t pin);
	void show(Vector<KeyValue> * data);

private:
	void blink(int onTime, int OffTime);

	bool _state;
	uint8_t _pin;
	unsigned long lastSwitchTime = 0;
	uint8_t _mode = 0;
};




#endif

