#include "Display.h"
#include <Fonts/FreeSans12pt7b.h>
#include <Arduino.h>

Display::Display()
: _ssd1306(128, 64, &Wire, -1)
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

        _ssd1306.setFont(&FreeSans12pt7b);
        _ssd1306.setTextColor(SSD1306_WHITE);

        _ssd1306.clearDisplay();

        _ssd1306.setCursor(15, 40);
        _ssd1306.print(F("Initializing"));
        _ssd1306.display();
    }
}

void Display::update()
{
}

void Display::print(long value)
{
    _ssd1306.clearDisplay();
    _ssd1306.setCursor(15, 40);
    _ssd1306.print(value);
    _ssd1306.display();
}
