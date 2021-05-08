#include "MotorControl.h"
#include <Arduino.h>
#include "Config.h"

MotorControl::MotorControl(Display* display)
  : _display(display)
{
    pinMode(RELAIS_PIN, OUTPUT);
    disableRelais();
}

void MotorControl::buttonPressed()
{
    _isPressed = true;
}

void MotorControl::buttonReleased()
{
    _isPressed = false;
}

void MotorControl::setDuration(const float& value)
{
    _duration = value;
}

void MotorControl::update()
{
    switch(_state)
    {
        case MotorControlState::Off:
            _progress = 100;
            _display->setProgress(_progress);
            _display->setTimeLeft(_duration);
            if(_isPressed)
            {
                switchState(MotorControlState::On);
            }
            break;
        case MotorControlState::On:
            _progress = ((float)(_endMillis - millis()) / (float)(_endMillis - _startMillis)) * (float)100;
            _display->setProgress(_progress);
            _timeLeft = _endMillis >= millis() ? (_endMillis - millis()) / (float)1000 : 0;
            _display->setTimeLeft(_timeLeft);

            if(millis() >= _endMillis)
            {
                switchState(MotorControlState::PreOff);
            }

            if(!_isPressed)
            {
                switchState(MotorControlState::Interrupted);
            }
            break;
        case MotorControlState::Interrupted:
            if(millis() >= _timeOut)
            {
                switchState(MotorControlState::Off);
            }
            if(_isPressed)
            {
                switchState(MotorControlState::On);

                // override time values from on state
                int durationMillis = _duration * (float)1000;
                _startMillis = millis() - (durationMillis - _millisLeftAtInterruption);
                _endMillis = _startMillis + durationMillis;
            }
            break;
        case MotorControlState::PreOff:
            _display->setProgress(0);
            _display->setTimeLeft(0);
            if(_timeOut == -1)
            {
                _timeOut = millis() + 1000;
            }
            if(millis() >= _timeOut && !_isPressed)
            {
                switchState(MotorControlState::Off);
            }
            break;
    }
}

void MotorControl::switchState(const MotorControlState &state)
{
    switch(state)
    {
        case MotorControlState::Off:
        {
            // do nothing
            break;
        }
        case MotorControlState::On:
        {
            _startMillis = millis();
            _endMillis = _startMillis + (long)((float)1000 * _duration);
            enableRelais();
            _display->easeStatusLine(STATUS_LINE_EASE_TIME, STATUS_LINE_LENGTH);
            break;
        }
        case MotorControlState::Interrupted:
        {
            _millisLeftAtInterruption = _endMillis - millis();
            _timeOut = millis() + INTERRUPTED_STATE_TIMEOUT;
            _startMillis = -1;
            _endMillis = -1;
            disableRelais();
            _display->easeStatusLine(INTERRUPTED_STATE_TIMEOUT, 0);
            break;
        }
        case MotorControlState::PreOff:
        {
            _startMillis = -1;
            _endMillis = -1;
            _timeOut = -1;
            disableRelais();
            _display->easeStatusLine(STATUS_LINE_EASE_TIME, 0);
            break;
        }
        default:
        {
            Serial.print("MotorControl switchState(): Unhandled State ");
            Serial.println((int)state);
        }
    }

    _state = state;
}

void MotorControl::enableRelais()
{
    digitalWrite(RELAIS_PIN, HIGH);
    _display->grinderEnabled();
}

void MotorControl::disableRelais()
{
    digitalWrite(RELAIS_PIN, LOW);
    _display->grinderDisabled();
}

float MotorControl::timeLeft()
{
    return _timeLeft;
}

int MotorControl::progress()
{
    return _progress;
}

MotorControlState MotorControl::currentState()
{
    return _state;
}