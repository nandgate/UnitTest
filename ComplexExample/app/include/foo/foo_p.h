#ifndef __FOO_P_H__
#define __FOO_P_H__

#include "foo/foo.h"
#include <stdint.h>

// Private header for the foo modules

#define FOO_FIRST_ARG0   12
#define FOO_SECOND_ARG0  23

#define FOO_FIRST_ARG1   12
#define FOO_SECOND_ARG1  23

#define FOO_FIRST_ARG2   12
#define FOO_SECOND_ARG2  23

// A function that is private to the module (this is what gets mocked)
uint32_t foo_Add(uint32_t a, uint32_t b);

#endif
