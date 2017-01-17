#include "LedStrip.h"

//Class constructor

LedStrip::LedStrip(uint16_t n, uint8_t p) : _pixels(n, p, NEO_GRB + NEO_KHZ800)
{
	_pixels.begin();
}


//Main method to display data. Call this method in main loop() of the program

void LedStrip::show(Vector<KeyValue> * data)
{
	//Extracting the data
	for (int i = 0; i < (*data).size(); ++i)
	{
		KeyValue kv = (*data)[i];
		Keys key = kv.key();
		int value = kv.value();

		switch (key)
		{
		case Mode:
			LedStrip::setMode(value);
			break;
		case EngineSpeed:
			_rpm = value;
			break;
		}
	}

	//Serial.print("LedStrip _mode: ");
	//Serial.println(_mode);

	switch (_mode)
	{
	case 0: 
		LedStrip::piu(); 
		break;
	case 1:		//Mode linear
		if (_rpm > _switchRpm)
		{
			LedStrip::blink(50, 50, _pixels.Color(150, 150, 150));
		}
		else
		{
			LedStrip::pixels(
				LedStrip::rpmToPixelsQty(_pixels.numPixels(), _rpm, _minRpm, _maxRpm),
				_pixels.Color(0, 150, 0));
		}
		break;
	case 2:		//Mode from sides to center
		
		if (_rpm > _switchRpm)
		{
			LedStrip::blink(50, 50, _pixels.Color(150, 150, 150));
		} 
		else 
		{

			int n;
			if (_pixels.numPixels() % 2 > 0)					//in case odd qty of pixels
				n = (_pixels.numPixels() / 2) + 1;
			else
				n = _pixels.numPixels() / 2;					//case even qty of pixels

			LedStrip::pixels2(
				LedStrip::rpmToPixelsQty(n, _rpm, _midRpm, _maxRpm),
				_pixels.Color(0, 150, 0));
		}
		break;
	case 3: 
		//LedStrip::blink(50, 50, _pixels.Color(150, 150, 150));
		break;
	}
}



void LedStrip::piu()
{
	if (_isShowing == true)								//One pixel now is active
	{
		if ((millis() - _lastTime) > 10)
		{
			_pixels.clear();
			if (_activePixel == _pixels.numPixels()-1)						//Last pixel was active -> turn off
			{
				_isShowing = false;
				_pixels.show();
				_lastTime = millis();
				return;
			}
			++_activePixel;								//Activate next pixel
			_pixels.setPixelColor(_activePixel, _pixels.Color(150, 150, 150));
			_pixels.show();
			_lastTime = millis();
		}
	}
	else
	{
		if ((millis() - _lastTime) > 1000)				//Activate first pixel
		{
			_isShowing = true;
			_activePixel = 0;
			_pixels.clear();
			_pixels.setPixelColor(_activePixel, _pixels.Color(150, 150, 150));
			_pixels.show();
			_lastTime = millis();
		}
	}
}

void LedStrip::dim(bool d)
{
	if (d) _pixels.setBrightness(30);
	else _pixels.setBrightness(255);
	_pixels.show();
}

void LedStrip::init(unsigned int minRpm, unsigned int maxRpm, unsigned int midRpm, unsigned int switchRpm)
{
	_minRpm = minRpm;
	_maxRpm = maxRpm;
	_midRpm = midRpm;
	_switchRpm = switchRpm;
}

void LedStrip::setMode(uint8_t m)
{
	uint8_t newMode = 0;
	if (m >= 10)
	{
		newMode = m - 10;
		LedStrip::dim(true);
	}
	else
	{
		newMode = m;
		LedStrip::dim(false);
	}
	if (_mode != newMode)
	{
		_mode = newMode;
		_pixels.clear();
	}
}

//Methos calculates how many pixels to light based on tachometer resolution

uint16_t LedStrip::rpmToPixelsQty(uint16_t qtyPixels, unsigned int rpm, unsigned int minRpm, unsigned int maxRpm)
{
	
	Serial.print(rpm);
	Serial.print(" / ");
	Serial.print(maxRpm);
	Serial.print(" : ");

	int segment = (maxRpm - minRpm) / (qtyPixels - 1);
	
	Serial.print((int)segment);
	Serial.print(" : ");

	int count;

	if (rpm > minRpm)
	{
		if ((rpm - minRpm) < segment)
		{
			count = 1;
		}
		else
		{
			count = ((rpm - minRpm) / segment) + 1;
		}
	}
	else
		count = 0;

	Serial.print((int)count);
	Serial.print(" of ");
	Serial.println(qtyPixels);
	
	return (uint16_t) count;
	
}



void LedStrip::pixels(int n, uint32_t c)
{
  if (n > _pixels.numPixels())
  {
    n = _pixels.numPixels();
  }

  for (int i = 0; i < _pixels.numPixels(); i++)
  {
    if (i < n) 
    {
		_pixels.setPixelColor(i, c);
    }
    else
    {
		_pixels.setPixelColor(i, _pixels.Color(0, 0, 0));
    }
  }
  _pixels.show();
}

void LedStrip::pixels2(int n, uint32_t c)
{
	int q;
	if (_pixels.numPixels() % 2 > 0)
		q = (_pixels.numPixels() / 2) + 1;
	else
		q = _pixels.numPixels() / 2;

	
	for (int i = 0; i < q; i++)
	{
		if (i < n)
		{
			_pixels.setPixelColor(i, c);
			_pixels.setPixelColor(_pixels.numPixels() - 1 - i, c);
		}
		else
		{
			_pixels.setPixelColor(i, _pixels.Color(0, 0, 0));
			_pixels.setPixelColor(_pixels.numPixels() -1 - i, _pixels.Color(0, 0, 0));
		}
	}

	_pixels.show();
}

void LedStrip::blink(unsigned int onTime, unsigned int offTime, uint16_t color)
{

	if (_blinkState == true && (millis() - lastBlinkSwitchTime) > onTime)
	{
		_pixels.clear();
		_blinkState = false;
		lastBlinkSwitchTime = millis();
	}
	else if (_blinkState == false && (millis() - lastBlinkSwitchTime) > offTime)
	{
		for (int i = 0; i < _pixels.numPixels(); ++i)
		{
			_pixels.setPixelColor(i, color);
		}
		_pixels.show();

		_blinkState = true;
		lastBlinkSwitchTime = millis();
	}

}


