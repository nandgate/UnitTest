#include "module/module_p.h"
#include "UnitTest.h"

Mock_Vars(5);   // must come before mocks

extern int mod_localState;

static void setUp(void)
{
}

static void test_Init(void)
{
    setUp();

    mod_Init();

    Assert_Equals(MOD_DEFAULT_STATE, mod_localState);
}

int main(int argc, char **argv)
{
    Assert_Init();

    test_Init();

    Assert_Save();
    return 0;
}
