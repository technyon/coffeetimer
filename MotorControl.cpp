#include "MotorControl.h"
#include <Arduino.h>
#include "Config.h"

MotorControl::MotorControl()
{
    pinMode(RELAIS_PIN, OUTPUT);
    disableRelais();
}

void MotorControl::start()
{
//    Serial.println("START");
    if(_endMillis == -1)
    {
        enableRelais();
        _endMillis = millis() + (long)((float)1000 * _duration);
    }
    else
    {
        _timeLeft = _endMillis >= millis() ? (_endMillis - millis()) / (float)1000 : 0;
//        Serial.println(_timeLeft);
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

void MotorControl::setDuration(const float& value)
{
    _duration = value;
}

void MotorControl::update()
{

}

void MotorControl::enableRelais()
{
    _isEnabled = true;
    digitalWrite(RELAIS_PIN, HIGH);
}

void MotorControl::disableRelais()
{
    digitalWrite(RELAIS_PIN, LOW);
    _isEnabled= false;
}

float MotorControl::timeLeft()
{
    return _timeLeft;
}

bool MotorControl::isRelaisEnabled()
{
    return _isEnabled;
}
