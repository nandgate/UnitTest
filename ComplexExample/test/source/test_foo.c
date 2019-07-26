#include "main_p.h"
#include "module/module.h"
#include "UnitTest.h"

Mock_Vars(5);   // must come before mocks

#define TEST_UNSET  0x42

static void setUp(void)
{
}

int main(int argc, char **argv)
{
    Assert_Init();

    // TODO

    Assert_Save();
    return 0;
}