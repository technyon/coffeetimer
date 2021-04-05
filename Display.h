#pragma once

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Display
{
public:
    explicit Display();
    virtual ~Display() = default;

    void initialize();
    void update();

    const float duration();
    void setDuration(const float value);

private:
    float _duration = 1;

    bool _isInitialized = false;
    Adafruit_SSD1306 _ssd1306;
};
