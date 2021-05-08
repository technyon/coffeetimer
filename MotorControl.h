#pragma once

#include "Display.h"

#define INTERRUPTED_STATE_TIMEOUT 5000

enum class MotorControlState
{
    Off,
    PreOff,
    On,
    Interrupted
};

class MotorControl
{
public:
    explicit MotorControl(Display* display);
    virtual ~MotorControl() = default;

    void buttonPressed();
    void buttonReleased();
    void update();

    void setDuration(const float& value);  // milliseconds

    [[nodiscard]] float timeLeft(); // milliseconds
    [[nodiscard]] int progress();
    [[nodiscard]] MotorControlState currentState();

private:
    void enableRelais();
    void disableRelais();

    void switchState(const MotorControlState& state);

    MotorControlState _state = MotorControlState::Off;
    int _progress = 100;
    float _duration = -1;
    float _timeLeft;
    bool _isPressed = false;

    long _startMillis = -1;
    long _endMillis = -1;
    long _timeOut;
    long _millisLeftAtInterruption = -1;

    Display* _display;
};
