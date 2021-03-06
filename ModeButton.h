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


class ModeButton : public IDataProvider, public Button
{
protected:

public:
	ModeButton(uint8_t pin);
	Keys getKey();
	uint8_t getValue();
	void nextMode();

private:
	uint8_t		mode = 0;
	bool		dim = true;
	bool		dimSwitched = false;
};


#endif

