#pragma once

#include "Display.h"
// #include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans24pt7b.h>
#include <Arduino.h>
#include "resources/bitmaps_grinder.h"

Display::Display()
: _statusLineEase(ease_mode::EASE_OUT_QUAD, 500),
  _ssd1306(128, 64, &Wire, -1)
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

//        _ssd1306.setCursor(15, 40);
//        _ssd1306.print(F("Initializing"));
//        _ssd1306.display();
    }
}

void Display::update()
{
    float value = _timeLeft == -1 ? _duration : _timeLeft;

    _ssd1306.clearDisplay();

    if(_clearProgressTs > 0)
    {
        if(millis() > _clearProgressTs)
        {
            _clearProgressTs = -1;
        }
        drawProgress(0);
    }
    else
    {
        drawProgress(_progress);
    }

    if(_grinderEnabled)
    {
        drawGrinderActiveAnimation();
    }

    drawStatusLine();

    _ssd1306.setCursor(value < 10 ? DURATION_TEXT_X + 10 : DURATION_TEXT_X, DURATION_TEXT_Y);
    _ssd1306.print(value, 1);

    _ssd1306.display();
}

void Display::drawProgress(int value)
{
    int fillHeight = 18 - (float)18 * ((float)value / (float)100);

    _ssd1306.drawBitmap(GRINDER_X_POS, GRINDER_Y_POS, resource::bitmap::grinder, 32, 64, SSD1306_WHITE);
    _ssd1306.drawBitmap(GRINDER_X_POS + 6, GRINDER_Y_POS + 7, resource::bitmap::grinder_coffee, 20, fillHeight, SSD1306_BLACK);
}

void Display::showMessage(char *message, int duration)
{
    _message = message;
    if(duration > 0)
    {
        _clearMessageTs = millis() + duration;
    }
}

const float Display::duration()
{
    return _duration;
}

void Display::setDuration(const float value)
{
    _duration = value;
}

void Display::setTimeLeft(const float value)
{
    _timeLeft = value;
}

void Display::setProgress(const int progress)
{
    _progress = progress;
}

void Display::showProgressComplete()
{
    _clearProgressTs = millis() + 500;
}

void Display::grinderEnabled()
{
    _grinderEnabled = true;
}

void Display::grinderDisabled()
{
    _grinderEnabled = false;
}

void Display::drawGrinderActiveAnimation()
{
    long ts = millis();
    if(ts > _grindActiveAnimationTs)
    {
        _grinderActiveAnimationIndex = _grinderActiveAnimationIndex + 1;
        if(_grinderActiveAnimationIndex > 3)
        {
            _grinderActiveAnimationIndex = 0;
        }
        _grindActiveAnimationTs = ts + 150;
    }

    switch(_grinderActiveAnimationIndex)
    {
        case 0:
            _ssd1306.drawBitmap(GRINDER_X_POS + 9, GRINDER_Y_POS + 47, resource::bitmap::grinder_active_anim_1, 14, 5, SSD1306_WHITE);
            break;
        case 1:
            _ssd1306.drawBitmap(GRINDER_X_POS + 9, GRINDER_Y_POS + 47, resource::bitmap::grinder_active_anim_2, 14, 5, SSD1306_WHITE);
            break;
        case 2:
            _ssd1306.drawBitmap(GRINDER_X_POS + 9, GRINDER_Y_POS + 47, resource::bitmap::grinder_active_anim_3, 14, 5, SSD1306_WHITE);
            break;
        case 3:
            _ssd1306.drawBitmap(GRINDER_X_POS + 9, GRINDER_Y_POS + 47, resource::bitmap::grinder_active_anim_4, 14, 5, SSD1306_WHITE);
            break;
    }
}

void Display::drawStatusLine()
{
    int16_t statusLinelength;

    statusLinelength = _statusLineEase.GetValue();

    _ssd1306.drawFastHLine(STATUS_LINE_X, STATUS_LINE_Y, statusLinelength, SSD1306_WHITE);
    _ssd1306.drawFastHLine(STATUS_LINE_X, STATUS_LINE_Y+1, statusLinelength, SSD1306_WHITE);

    _currentStatusLineLength = statusLinelength;
}

void Display::easeStatusLine(long duration, int16_t targetLength)
{
    _statusLineEase.Init(_currentStatusLineLength);
    _statusLineEase.SetMillisInterval(duration);
    _statusLineEase.SetSetpoint(targetLength);
    //    _statusLineEase.setDuration((double)(_statusLineEaseEndTime - _statusLineEaseStartTime) / (double)1000);
//    _statusLineEase.setTotalChangeInPosition(_statusLineEaseEndTime - _statusLineEaseStartTime - _currentStatusLineLength);
}
