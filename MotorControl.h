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

private:
    void enableRelais();
    void disableRelais();

    float _duration = -1;
    float _timeLeft;

    long _endMillis = -1;
};
