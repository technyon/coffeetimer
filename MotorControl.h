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

private:
    float _duration = -1;
};
