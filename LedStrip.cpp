#include "LedStrip.h"

LedStrip::LedStrip(uint16_t n, uint8_t p) : pixels(n, p, NEO_GRB + NEO_KHZ800)
{
	pixels.begin();
}

void LedStrip::show(Vector<KeyValue> * data)
{
	for (int i = 0; i < (*data).size(); ++i)
	{
		KeyValue kv = (*data)[i];
		Keys key = kv.key();
		int value = kv.value();

		if (key == Mode)
			if (value >= 10)
			{
				_mode = value - 10;
				LedStrip::dim(true);
			}
			else
			{
				_mode = value;
				LedStrip::dim(false);
			}
	}

	Serial.print("LedStrip _mode: ");
	Serial.println(_mode);

	switch (_mode)
	{
	case 0: LedStrip::piu(); break;
	case 1: break;
	case 2: break;
	case 3: break;
	}
}

void LedStrip::piu()
{
	if (isShowing == true)								//One pixel now is active
	{
		if ((millis() - lastTime) > 10)
		{
			pixels.clear();
			if (activePixel == 8)						//Last pixel was active -> turn off
			{
				isShowing = false;
				pixels.show();
				lastTime = millis();
				return;
			}
			++activePixel;
			pixels.setPixelColor(activePixel, pixels.Color(150, 150, 150));
			pixels.show();
			lastTime = millis();
		}
	}
	else
	{
		if ((millis() - lastTime) > 1000)				//Activate first pixel
		{
			isShowing = true;
			activePixel = 0;
			pixels.clear();
			pixels.setPixelColor(activePixel, pixels.Color(150, 150, 150));
			pixels.show();
			lastTime = millis();
		}
	}
}

void LedStrip::dim(bool d)
{
	if (d) pixels.setBrightness(30);
	else pixels.setBrightness(255);
	pixels.show();
}


/*
void LedStrip::pixels(int n, uint32_t c)
{
  if (n > Adafruit_NeoPixel::numPixels())
  {
    n = Adafruit_NeoPixel::numPixels();
  }

  for (int i = 0; i < Adafruit_NeoPixel::numPixels(); i++)                             
  {
    if (i < n) 
    {
      Adafruit_NeoPixel::setPixelColor(i, c);
    }
    else
    {
      Adafruit_NeoPixel::setPixelColor(i, Adafruit_NeoPixel::Color(0, 0, 0));
    }
  }
  Adafruit_NeoPixel::show();
}
*/

