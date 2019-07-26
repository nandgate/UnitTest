#include "module/module_p.h"
#include "UnitTest.h"

Mock_Vars(5);   // must come before mocks

// Many times is it important to verify that a value has/has not been written
// to. To do this we typically set the value in the setUp function to some
// initial value, then assert that the value has changed as a result of calling
// the unit under test. Conventionally the initial value is "TEST_UNSET". It is
// best if this value is unique enough that its obvious that the value under
// test has/has not been set. Bas choices here are 0, -1, or any value in the
// test domain of the variable.
#define TEST_UNSET  0x42

// Here we need to pull in the state used buy the unit under test so we can
// initialize and monitor it.
extern int mod_localState;

static void setUp(void)
{
    // It is important to set the state variable to their "unset" state so you
    // can validate that they are/are not set by the unit. It is very common to
    // to forget to do this- and the test is not logically correct without this.
    mod_localState = TEST_UNSET;
}

static void test_Init(void)
{
    setUp();

    mod_Init();

    // Not we can assert that the state was changed by the unit under test.
    Assert_Equals(MOD_DEFAULT_STATE, mod_localState);
}

int main(int argc, char **argv)
{
    Assert_Init();

    test_Init();

    Assert_Save();
    return 0;
}
