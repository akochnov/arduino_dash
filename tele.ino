#include "Vector.h"
#include "KeyValue.h"
#include "SingleLed.h"
#include "IDisplay.h"
#include "ModeButton.h"
#include "KeyValue.h"
#include "IDataProvider.h"


#include <Button.h>
#include <Arduino.h>

Vector<IDataProvider*>  dataProviders;

ModeButton modeButton(6);

//TODO
//LedStrip ledStrip();
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
		data.push_back(kv);
	}

	display.show(&data);
}


