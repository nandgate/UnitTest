#include "hal/chip.h"
#include "hal/Led_p.h"

// Sometimes you can put all of the functions for a module in one file- many
// times you can't. Its would be OK (in some way desirable) to split this up
// so each function is in its own file.

uint32_t led_map[NUMBER_OF_LEDS] =
{
    [LED_ACTIVITY] = LED_ACTIVITY_MASK,
    [LED_ERROR] = LED_ERROR_MASK,
    [LED_BUSY] = LED_BUSY_MASK
};

void led_Init(void)
{
    gpio->outClear= LED_MASK;
    gpio->dirSet= LED_MASK;
}

void led_On(led_t led)
{
    if(led < NUMBER_OF_LEDS) {
        gpio->outSet = led_map[led];
    }
}

void led_Off(led_t led)
{
    if(led < NUMBER_OF_LEDS) {
        gpio->outClear = led_map[led];
    }
}

void led_Toggle(led_t led)
{
    if(led < NUMBER_OF_LEDS) {
        uint32_t mask = led_map[led];
        if (gpio->in & mask) {
            gpio->outClear = mask;
        } else {
            gpio->outSet = mask;
        }
    }
}