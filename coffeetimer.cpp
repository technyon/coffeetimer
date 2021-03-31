#include "Arduino.h"
#include "Config.h"
#include "Display.h"
#include <src/AiEsp32RotaryEncoder.h>

Display* display;
AiEsp32RotaryEncoder* encoder;

void onEncoderButtonPressed()
{

}

void setup()
{
	Serial.begin(9600);
	Serial.println("START");

	display = new Display();
	display->initialize();

    encoder = new AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);
    encoder->begin();

    encoder->setup(
            [] { encoder->readEncoder_ISR(); },
            onEncoderButtonPressed);

    encoder->setBoundaries(0, 1000, true);
    encoder->setAcceleration(250);
}

void loop()
{
    //dont print anything unless value changed
    if (!encoder->encoderChanged())
    {
        return;
    }

    display->print(encoder->readEncoder());

    Serial.print("Value: ");
    Serial.println(encoder->readEncoder());
    delay(10);
}
