#include "main_p.h"
#include "module/module.h"
#include "UnitTest.h"

Mock_Vars(5);   // must come before mocks

Mock_Value(int, mod_GetInt);
Mock_Void(mod_Init);

#define TEST_UNSET  0x42

static void setUp(void)
{
    Mock_Reset(mod_GetInt);
    Mock_Reset(mod_Init);

    Mock_Returns(mod_GetInt, TEST_UNSET);
}

static void test_Init(void)
{
    setUp();

    main_Init();

    Assert_CalledOnce(mod_Init);
    Assert_NotCalled(mod_GetInt);
}

static void test_Loop(void)
{
    setUp();

    main_Loop();

    Assert_CalledOnce(mod_GetInt);
    Assert_NotCalled(mod_Init);
}

int main(int argc, char **argv)
{
    Assert_Init();

    test_Init();
    test_Loop();

    Assert_Save();
    return 0;
}