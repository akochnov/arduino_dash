#include "LedStrip.h"

LedStrip::LedStrip(uint16_t n, uint8_t p) : _pixels(n, p, NEO_GRB + NEO_KHZ800)
{
	_pixels.begin();
}

void LedStrip::show(Vector<KeyValue> * data)
{
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
		case MaxEngineSpeed:
			_maxRpm = value;
			break;
		case MinEngineSpeed:
			_minRpm = value;
			break;
		}
	}

	//Serial.print("LedStrip _mode: ");
	//Serial.println(_mode);

	switch (_mode)
	{
	case 0: LedStrip::piu(); break;
	case 1: LedStrip::pixels(LedStrip::rpmToPixelsQty(_pixels.numPixels()), _pixels.Color(0, 150, 0)); break;
	case 2: break;
	case 3: break;
	}
}



void LedStrip::piu()
{
	if (_isShowing == true)								//One pixel now is active
	{
		if ((millis() - _lastTime) > 10)
		{
			_pixels.clear();
			if (_activePixel == 8)						//Last pixel was active -> turn off
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

void LedStrip::setMode(uint8_t m)
{
	if (m >= 10)
	{
		_mode = m - 10;
		LedStrip::dim(true);
	}
	else
	{
		_mode = m;
		LedStrip::dim(false);
	}
}

uint16_t LedStrip::rpmToPixelsQty(uint16_t qtyPixels = 0)
{
	if (qtyPixels == 0) qtyPixels = _pixels.numPixels();
	
	Serial.print(_rpm);
	Serial.print(" : ");

	double segment = (_maxRpm - _minRpm) / (qtyPixels - 1);
	
	Serial.print((int)segment);
	Serial.print(" : ");

	double count;

	if (_rpm > _minRpm)
	{
		if ((_rpm - _minRpm) < segment)
		{
			count = 1;
		}
		else
		{
			count = ((_rpm - _minRpm) / segment) + 1;
		}
	}
	else
		count = 0;

	Serial.println((int)count);
	
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


