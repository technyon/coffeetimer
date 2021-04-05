#include "Arduino.h"
#include "Config.h"
#include "Display.h"
#include <src/AiEsp32RotaryEncoder.h>
#include "Storage.h"


Display* display;
AiEsp32RotaryEncoder* encoder;
Storage* storage;

uint16_t duration = 1; // milliseconds

void onEncoderButtonPressed()
{
    Serial.println("PRESS");
}

void setup()
{
    Serial.begin(9600);
	Serial.println("START");

    storage = new Storage();

    Serial.println(storage->duration());

//    storage->setDuration(6.78);
//    storage->save();

	display = new Display();
	display->initialize();

    encoder = new AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);
    encoder->begin();

    encoder->setup(
            [] { encoder->readEncoder_ISR(); },
            onEncoderButtonPressed);

    encoder->setBoundaries(10, 150, false);
    encoder->setAcceleration(ROTARY_ENCODER_ACCELERATION);
}

void queryEncoder()
{
    //dont print anything unless value changed
    if (!encoder->encoderChanged())
    {
        return;
    }

    display->setDuration((float)encoder->readEncoder() / 10);
}

long lastDisplayUpdate = 0;

void loop()
{
    queryEncoder();

    long ts = millis();

    if(ts - lastDisplayUpdate > 100)
    {
        display->update();
        lastDisplayUpdate = ts;
    }
}
