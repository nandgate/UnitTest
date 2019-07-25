#include "module/module_p.h"
#include "UnitTest.h"

Mock_Vars(5);   // must come before mocks

Mock_Value(int, mod_Compute);

#define TEST_INT_VALUE  0X42

static void setUp(void)
{
    Mock_Reset(mod_Compute);

    Mock_Returns(mod_Compute, TEST_INT_VALUE);
}

static void test_CallsCompute(void)
{
    setUp();

    mod_GetInt();

    Assert_CalledOnce(mod_Compute);
}

static void test_IntegerReturned(void)
{
    setUp();

    int result = mod_GetInt();

    Assert_Equals(TEST_INT_VALUE + MOD_THE_INT, result);
}

int main(int argc, char **argv)
{
    Assert_Init();

    test_CallsCompute();
    test_IntegerReturned();

    Assert_Save();
    return 0;
}
