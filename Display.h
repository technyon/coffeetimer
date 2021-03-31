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

    void print(long i);

private:

    bool _isInitialized = false;
    Adafruit_SSD1306 _ssd1306;
};
