#include "Arduino.h"
#include "Display.h"

Display* display;

void setup()
{
	Serial.begin(9600);
	Serial.println("START");

	display = new Display();
	display->initialize();
}

void loop()
{
    delay(10);
//    display->update();
}
