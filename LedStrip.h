#ifndef LedStrip_h
#define LedStrip_h

#include "IDisplay.h"
#include "Vector.h"

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


class LedStrip : public IDisplay
{
  public:
	LedStrip(uint16_t n, uint8_t p);
	void show(Vector<KeyValue> * data);
	void piu();

private:
	void dim(bool d);
	Adafruit_NeoPixel pixels;
	uint8_t _mode = 0;
	
	long lastTime = 0;
	bool isShowing = false;
	uint16_t activePixel = 0;
};

#endif

