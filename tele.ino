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

//Define data source objects
Vector<IDataProvider*>  dataProviders;
ModeButton modeButton(6);

//Define display objects
LedStrip ledStrip(8, 9);
LedStrip ledStrip2(11, 10);
SingleLed statusLed(13);

//Required for engine rpm simulation
int rpm = 1000;
unsigned long lastRpmChangedMillis = 0;
int rpmIncrement = 20;

void setup() {
	//Initialize serial port
	Serial.begin(9600);
	Serial.println("Start");
	
	//Initialize ledstrips
	ledStrip.init(0, 7500, 3500, 7500);
	ledStrip2.init(0, 6000, 4500, 6500);

	//Push data providers to vector
	dataProviders.push_back(&modeButton);
}

void loop() {
	Vector<KeyValue> data;

	//Extract data from data providers
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

	//Engine simulation
	if ((millis() - lastRpmChangedMillis) > 15)
	{
		rpm = rpm + rpmIncrement;
		if (rpm > 7000 || rpm < 1000) rpmIncrement = -rpmIncrement;
		lastRpmChangedMillis = millis();
	}

	//Push simulated engine speed to data
	KeyValue eSpeed(EngineSpeed, rpm);
	//KeyValue eSpeed(EngineSpeed, 6000);
	data.push_back(eSpeed);

	//Display all information to all displays
	statusLed.show(&data);
	ledStrip.show(&data);
	ledStrip2.show(&data);
	
}


