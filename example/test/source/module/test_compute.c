#include "module/module_p.h"
#include "UnitTest.h"

Mock_Vars(5);   // must come before mocks

static void setUp(void)
{
}

static void test_IntegerReturned(void)
{
    setUp();

    int result = mod_Compute();

    Assert_Equals(MOD_THE_INT, result);
}

int main(int argc, char **argv)
{
    Assert_Init();

    test_IntegerReturned();

    Assert_Save();
    return 0;
}
