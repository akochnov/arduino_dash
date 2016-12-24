// ModeButton.h

#ifndef _MODEBUTTON_h
#define _MODEBUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "IDataProvider.h"
#include <Button.h>


class ModeButtonClass : public IDataProvider, public Button
{
protected:

public:
	ModeButtonClass(uint8_t pin);
	Keys getKey();
	uint8_t getValue();
	void nextMode();

private:
	uint8_t		mode = 0;
	bool		dim = false;
	bool		dimSwitched = false;
};


#endif

