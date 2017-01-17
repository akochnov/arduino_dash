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
	void show(Vector<KeyValue> * data);	//Method recieves data to display

	void init(unsigned int minRpm, unsigned int maxRpm, unsigned int midRpm, unsigned int switchRpm);	

private:
	void piu();											//Method to dispalay engine off status
	void setMode(uint8_t m);							//Method to set current mode of the display
	
	
	uint16_t rpmToPixelsQty(uint16_t qtyPixels,			//Method to calculate number of pixels vs current rpm
							unsigned int rpm, 
							unsigned int minRpm, 
							unsigned int maxRpm);	

	void pixels(int n, uint32_t c);						//Method to light v1 tachometer
	void pixels2(int n, uint32_t c);					//Method to light v2 tachometer

	void blink(unsigned int onTime,						//Blink all pixels
				unsigned int offTime, 
				uint16_t color);		

	void dim(bool d);									//Method to switch dimmer

	Adafruit_NeoPixel _pixels;							//Stores LedStrip object
	uint8_t _mode = 0;									//Stores current ledstrip mode
	
	
	//Store current engine speed and tachometer resolution
	unsigned int _rpm = 0;
	unsigned int _minRpm = 1000;
	unsigned int _midRpm = 3500;
	unsigned int _maxRpm = 8000;
	unsigned int _switchRpm = 7500;

	//Properties used by piu()
	unsigned long _lastTime = 0;
	bool _isShowing = false;
	uint16_t _activePixel = 0;

	bool _blinkState = false;
	unsigned int lastBlinkSwitchTime = 0;
};

#endif

