#include "foo/foo_p.h"

// Simple demo function that does something that other functions can depend on.
uint32_t foo_Add(uint32_t a, uint32_t b)
{
    return a + b;
}