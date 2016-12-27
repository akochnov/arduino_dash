#include <Adafruit_NeoPixel.h>
#include "Vector.h"
#include "KeyValue.h"
#include "SingleLed.h"
#include "IDisplay.h"
#include "ModeButton.h"
#include "KeyValue.h"
#include "IDataProvider.h"
#include "LedStrip.h"


#include <Button.h>
#include <Arduino.h>

Vector<IDataProvider*>  dataProviders;

ModeButton modeButton(6);

LedStrip ledStrip(9, 9);
SingleLed display(13);


void setup() {

	Serial.begin(9600);
	Serial.println("Start");

	dataProviders.push_back(&modeButton);
}

void loop() {
	Vector<KeyValue> data;

	for (int i = 0; i < dataProviders.size(); ++i) 
	{
		Keys key = dataProviders[i]->getKey();
		uint8_t value = dataProviders[i]->getValue();
		KeyValue kv(key, value);
		//Serial.print(key);
		//Serial.print(" : ");
		//Serial.println(value);
		data.push_back(kv);
	}

	display.show(&data);
	ledStrip.show(&data);

}


