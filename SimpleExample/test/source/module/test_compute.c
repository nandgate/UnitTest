#include "module/module_p.h"
#include "UnitTest.h"

Mock_Vars(5);   // must come before mocks

// The setup function is conventially always present and called- even when it
// is empty.
static void setUp(void)
{
}

// Here are are testing the return value from the unit under test.
static void test_IntegerReturned(void)
{
    setUp();

    int result = mod_Compute();

    // Values to the test assertions are ordered: expected, actual.
    Assert_Equals(MOD_THE_INT, result);
}

int main(int argc, char **argv)
{
    Assert_Init();

    test_IntegerReturned();

    Assert_Save();
    return 0;
}
