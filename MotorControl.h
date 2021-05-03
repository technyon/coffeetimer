#pragma once

class MotorControl
{
public:
    explicit MotorControl();
    virtual ~MotorControl() = default;

    void start();
    void stop();
    void update();

    void setDuration(const long& value);  // milliseconds

    float timeLeft(); // milliseconds
    bool isRelaisEnabled();

private:
    void enableRelais();
    void disableRelais();

    float _duration = -1;
    float _timeLeft;
    bool _isEnabled = false;

    long _endMillis = -1;
};
