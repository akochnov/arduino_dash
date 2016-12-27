// IDisplay.h

#ifndef _IDISPLAY_h
#define _IDISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "IDataProvider.h"
#include "KeyValue.h"
#include "Vector.h"

class IDisplay
{
public:
	virtual void show(Vector<KeyValue> * data) = 0;
};

#endif

