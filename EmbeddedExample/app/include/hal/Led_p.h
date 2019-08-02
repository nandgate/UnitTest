#ifndef _LEDS_P_H_
#define _LEDS_P_H_

// Private header fo the LED HAL.

#include "hal/Led.h"

// Actual hardware specific symbols:
#define LED_ACTIVITY_MASK   (1<<12)
#define LED_ERROR_MASK      (1<<7)
#define LED_BUSY_MASK       (1<<28)

#define LED_MASK (LED_ACTIVITY_MASK | LED_ERROR_MASK | LED_BUSY_MASK)

#endif
