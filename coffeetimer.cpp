#include "Arduino.h"
#include "Config.h"
#include "Display.h"
#include <src/AiEsp32RotaryEncoder.h>
#include "Storage.h"
#include "MotorControl.h"


Display* display;
AiEsp32RotaryEncoder* encoder;
Storage* storage;
MotorControl* motorControl;

uint16_t duration = 1; // milliseconds

void onEncoderButtonPressed()
{
    if(motorControl->currentState() != MotorControlState::Off)
    {
        return;
    }
    Serial.println("PRESS");
}

void setup()
{
    pinMode(START_BUTTON_PIN, INPUT_PULLUP);

    display = new Display();
    display->initialize();

    motorControl = new MotorControl(display);

    Serial.begin(9600);
	Serial.println("START");

    storage = new Storage();

    Serial.println(storage->duration());


    encoder = new AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);
    encoder->begin();

    encoder->setup(
            [] { encoder->readEncoder_ISR(); },
            onEncoderButtonPressed);

    encoder->setBoundaries(MINIMUM_DURATION * 10, MAXIMUM_DURATION * 10, false);
    encoder->setAcceleration(ROTARY_ENCODER_ACCELERATION);

    encoder->setEncoderValue(storage->duration() * 10);
    motorControl->setDuration(storage->duration());
}

void queryEncoder()
{
    //dont print anything unless value changed
    if (!encoder->encoderChanged())
    {
        return;
    }

    float duration = (float)encoder->readEncoder() / (float)10;
    display->setDuration(duration);
    motorControl->setDuration(duration);
    storage->setDuration(duration);
}

long lastDisplayUpdate = 0;

void loop()
{
    queryEncoder();

    long ts = millis();

    if(ts - lastDisplayUpdate > 50)
    {
        display->update();
        lastDisplayUpdate = ts;
    }

    if(digitalRead(START_BUTTON_PIN) == LOW)
    {
        motorControl->buttonPressed();
        storage->save();
    }
    else
    {
        motorControl->buttonReleased();
    }

    if(motorControl->currentState() == MotorControlState::Off)
    {
        encoder->enable();
    }
    else
    {
        encoder->disable();
    }

    motorControl->update();
}
