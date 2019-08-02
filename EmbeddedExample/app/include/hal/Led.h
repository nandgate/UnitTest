#ifndef _LED_H_
#define _LED_H_

// Public header for the LED Hardware Abstraction Layer (HAL).
// Provides an API for interacting with the hardware without exposing any of
// the details of the hardware.

typedef enum
{
    LED_ACTIVITY,
    LED_ERROR,
    LED_BUSY,
    NUMBER_OF_LEDS
} led_t;

void led_Init(void);

void led_On(led_t led);
void led_Off(led_t led);
void led_Toggle(led_t led);

#endif
