/*
 * Easing Functions: Copyright (c) 2010 Andy Brown
 * http://www.andybrown.me.uk
 *
 * This work is licensed under a Creative Commons
 * Attribution_ShareAlike 3.0 Unported License.
 * http://creativecommons.org/licenses/by_sa/3.0/
 */

#include "EasingBase.h"


/*
 * Default constructor
 */

EasingBase::EasingBase()
{
	_change=0;
}

#include <Arduino.h>

/*
 * Set the duration
 */

void EasingBase::setDuration(NUMBER duration_)
{
	_duration=duration_;
	Serial.print("DURATION: ");
	Serial.println(_duration);
}


/*
 * Set the total change in position
 */

void EasingBase::setTotalChangeInPosition(NUMBER totalChangeInPosition_)
{
	_change=totalChangeInPosition_;
    Serial.print("CHANGE: ");
    Serial.println(_change);
}
