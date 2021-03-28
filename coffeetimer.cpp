#include "Arduino.h"

#define  LED_PIN 2

void setup()
{
	Serial.begin(9600);
	Serial.println("START");
	pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
    Serial.println("LOOP");
}
