#include "foo/foo_p.h"

// A simple function that has an external dependency to demonstrate how the
// external function is mocked by the test framework.
uint32_t foo_Doit(void)
{
    uint32_t sum;

    sum = foo_Add(FOO_FIRST_ARG0, FOO_SECOND_ARG0);

    sum += foo_Add(FOO_FIRST_ARG1, FOO_SECOND_ARG1);

    sum += foo_Add(FOO_FIRST_ARG2, FOO_SECOND_ARG2);

    return sum;
}
