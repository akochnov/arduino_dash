// KeyValue.h

#ifndef _KEYVALUE_h
#define _KEYVALUE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "IDataProvider.h"


class KeyValue
{
 public:
	 KeyValue(Keys k, int v);
	 Keys key();
	 int value();

private:
	 Keys _key;
	 int _value;
};


#endif

