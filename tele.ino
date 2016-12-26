#include "Vector.h"
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

int counter = 0;

void setup() {
	Serial.begin(9600);
	Serial.println("Start");

	//pinMode(13, OUTPUT); //debug to led 13

}

void loop() {
	/*
	int countProviders = sizeof(dataProviders) / sizeof(dataProviders[0]);
	KeyValueClass data[countProviders];

	for (int i = 0; i < countProviders; ++i) {
		Keys key = dataProviders[i]->getKey();
		uint8_t value = dataProviders[i]->getValue();
		KeyValueClass kv(key, value);
		data[i] =  &kv;
	}

	int arr[15];

	*/

	KeyValueClass kv(dataProviders[0]->getKey(), dataProviders[0]->getValue());

	KeyValueClass * data[] = { &kv };

	display->show(data, sizeof(data));



	
	Vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(3);

	for (int i = 0; i < v.size(); ++i)
	{
		Serial.println(v[i]);
	}
	
}
