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
    if(_endMillis == -1)
    {
        enableRelais();
        _endMillis = millis() + 1000 * _duration;
    }
    else
    {
        _timeLeft = _endMillis >= millis() ? (_endMillis - millis()) / (float)1000 : 0;
        if(millis() >= _endMillis)
        {
            disableRelais();
        }
    }
}

void MotorControl::stop()
{
    _endMillis = -1;
    _timeLeft = -1;
    disableRelais();
}

void MotorControl::setDuration(const long& value)
{
    _duration = value;
}

void MotorControl::update()
{

}

void MotorControl::enableRelais()
{
    digitalWrite(RELAIS_PIN, LOW);
}

void MotorControl::disableRelais()
{
    digitalWrite(RELAIS_PIN, HIGH);
}

float MotorControl::timeLeft()
{
    return _timeLeft;
}