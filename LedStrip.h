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
	void setMode(uint8_t m);
	uint16_t rpmToPixelsQty(uint16_t qtyPixels);

	void pixels(int n, uint32_t c);

	Adafruit_NeoPixel _pixels;
	uint8_t _mode = 0;
	
	//Store current engine speed and tachometer resolution
	unsigned int _rpm = 0;
	unsigned int _minRpm = 1000;
	unsigned int _maxRpm = 8000;

	//Properties used by piu()
	unsigned long _lastTime = 0;
	bool _isShowing = false;
	uint16_t _activePixel = 0;
};

#endif

