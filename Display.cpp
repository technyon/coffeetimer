#include "Display.h"
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans24pt7b.h>
#include <Arduino.h>

Display::Display(MotorControl* motorControl)
: _ssd1306(128, 64, &Wire, -1),
  _motorControl(motorControl)
{

}

void Display::initialize()
{
#define SCREEN_ADDRESS 0x3C

    _isInitialized = _ssd1306.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    if(!_isInitialized)
    {
        Serial.println(F("SSD1306 allocation failed"));
    }
    else
    {
        _ssd1306.dim(false);

        _ssd1306.setFont(&FreeSans24pt7b);
        _ssd1306.setTextColor(SSD1306_WHITE);

        _ssd1306.clearDisplay();

        _ssd1306.setCursor(15, 40);
        _ssd1306.print(F("Initializing"));
        _ssd1306.display();
    }
}

void Display::update()
{
    float value = _motorControl->timeLeft() == -1 ? _duration : _motorControl->timeLeft();

    _ssd1306.clearDisplay();
    _ssd1306.setCursor(value < 10 ? 30 : 20, 55);
    _ssd1306.print(value, 1);
    _ssd1306.display();
}

const float Display::duration()
{
    return _duration;
}

void Display::setDuration(const float value)
{
    _duration = value;
}
