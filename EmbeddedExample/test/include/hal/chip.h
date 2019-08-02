#ifndef _CHIP_H_
#define _CHIP_H_

#include "stdint.h"

// Test mock for the actual hardware.
// When the unit tests are run this is the header that in used when the
// application includes "hal/chip.h". Note that in the test runner the include
// path for the unit test directory is specified _before_ the application
// directory. The compiler will find the header in the test path before the
// application path.  This allows to to provide this version that is used for
// testing. It is a requirement of this technique that the headers in both the
// application and test paths stay in sync in terms of the symbols they define.

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

// We make a global variable here that stands in for the hardware registers in
// actual hardware. The application can then read/write this global and the unit
// tests can setup/assert on it as well. In the example we are have a pointer
// to the "GPIO", so we need to allocate out GPIO "registers", and provide a
// symbol that the app uses to access them. It is imperative that
// app/include/hal/chip.h provide the same symbol with the same type associated
// with it.
chip_gpio_t _gpio;
#define gpio (&_gpio)

#endif
