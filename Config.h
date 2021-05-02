#pragma once

// Minimum and maximum duration in seconds
#define MINIMUM_DURATION 0.5
#define MAXIMUM_DURATION 9

#define START_BUTTON_PIN 32
#define RELAIS_PIN 25

#define ROTARY_ENCODER_A_PIN 26
#define ROTARY_ENCODER_B_PIN 27
#define ROTARY_ENCODER_BUTTON_PIN 33
#define ROTARY_ENCODER_VCC_PIN -1

#define ROTARY_ENCODER_ACCELERATION 20

//depending on your encoder - try 1,2 or 4 to get expected behaviour
#define ROTARY_ENCODER_STEPS 4