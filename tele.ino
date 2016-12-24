#include "KeyValue.h"
#include "SingleLed.h"
#include "IDisplay.h"
#include "ModeButton.h"
#include "KeyValue.h"
#include "IDataProvider.h"

#include <Button.h>
#include <Arduino.h>



uint8_t lastMode = 0;

IDataProvider * dataProviders[] = { 
	new ModeButtonClass(6) 
};

SingleLedClass * display = new SingleLedClass(13);;


void setup() {
	Serial.begin(9600);
	Serial.println("Start");

	//pinMode(13, OUTPUT); //debug to led 13

}

void loop() {
	/*
	for (auto dataProvider : dataProviders) {
		Keys key = dataProvider->getKey();
		uint8_t value = dataProvider->getValue();

	}
	*/

	Keys key = dataProviders[0]->getKey();
	int val = dataProviders[0]->getValue();
	Serial.print(key);
	Serial.print(" : ");
	Serial.println(val);
	
	KeyValueClass * kv = new KeyValueClass(key, val);
	key = kv->key();
	val = kv->value();
	Serial.print(key);
	Serial.print(" : ");
	Serial.println(val);

	KeyValueClass * data[] = { kv };

	display->show(data, sizeof(data));
}
