#include "MotorControl.h"
#include <Arduino.h>
#include "Config.h"

MotorControl::MotorControl()
{
    pinMode(RELAIS_PIN, OUTPUT);
    digitalWrite(RELAIS_PIN, HIGH);
}

void MotorControl::start()
{
//    Serial.println("START");
    digitalWrite(RELAIS_PIN, LOW);
}

void MotorControl::stop()
{
//    Serial.println("STOP");
    digitalWrite(RELAIS_PIN, HIGH);
}

void MotorControl::setDuration(const long& value)
{
    _duration = value;
}

void MotorControl::update()
{

}
