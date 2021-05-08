#pragma once

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "lib/EasingLibrary/SineEase.h"

#define GRINDER_X_POS 0
#define GRINDER_Y_POS -1
#define STATUS_LINE_X 32
#define STATUS_LINE_Y GRINDER_Y_POS + 62
#define STATUS_LINE_LENGTH 90
#define STATUS_LINE_EASE_TIME 500
#define DURATION_TEXT_X 40
#define DURATION_TEXT_Y 54

class Display
{
public:
    explicit Display();
    virtual ~Display() = default;

    void initialize();
    void update();

    const float duration();
    void setDuration(const float value);

    void showMessage(char* message, int duration = -1);
    void setTimeLeft(const float value);
    void setProgress(const int progress);
    void showProgressComplete();
    void grinderEnabled();
    void grinderDisabled();
    void easeStatusLine(long duration, int16_t targetLength);

private:
    void drawProgress(int value);

    float _duration = 1;

    char* _message = nullptr;
    long _clearMessageTs = -1;
    long _clearProgressTs = -1;

    float _timeLeft = 0;
    int _progress = 100;

    double _statusLineLength = 0;
    SineEase _statusLineEase;
    long _statusLineEaseStartTime;
    long _statusLineEaseEndTime;
    int16_t _currentStatusLineLength = 0;
    int16_t _statusLineEaseStartLength = 0;

    bool _grinderEnabled = false;
    uint8_t _grinderActiveAnimationIndex = 0;
    long _grindActiveAnimationTs = 0;

    bool _isInitialized = false;
    Adafruit_SSD1306 _ssd1306;

    void drawGrinderActiveAnimation();

    void drawStatusLine();
};
