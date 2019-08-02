#ifndef _CHIP_H_
#define _CHIP_H_

// Symbols for interfacing to the actual hardware. This is the code that is used
// when you build the application target, so it needs to interface to the actual
// hardware. Sometimes you can use the headers from the manufacture as-is,
// sometimes you will need to "tweek" them, sometime they are not in a form
// adaptable to unit testing.


#include "stdint.h"

// Fictitious GPIO port for the purpose of demonstrating how hardware might be
// mocked for the purpose of testing. In most systems hardware is really just
// a bunch of volatile global variables...
typedef struct
{
    uint32_t    dir;
    uint32_t    dirSet;
    uint32_t    dirClear;
    uint32_t    out;
    uint32_t    outSet;
    uint32_t    outClear;
    uint32_t    in;
} chip_gpio_t;


// Note that for the target we are going to point to an absolute location in
// the memory map. This will not work when the tests are run on the host- writing
// to absolute address will, at best, produce seg faults. When the unit tests
// are run the same "gpio" symbol needs to be defined, but appropriate for the
// host. See test/include/hal/chip.h.
#define CHIP_GPIO_BASE  0x40001000

#define gpio    (chip_gpio_t*(CHIP_GPIO_BASE))

#endif
