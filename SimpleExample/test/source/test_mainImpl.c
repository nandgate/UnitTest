
// This is unit test for the main helper function. The unit tests typically
// include the same files as the application file, with the addition of the
// "UnitTest.h". I keep the headers in alphabetical order (if the order of the
// headers matters you shoud fix that...).

#include "main_p.h"
#include "module/module.h"
#include "UnitTest.h"

// The unit test frame work tracks the invocation of the mock functions. It
// needs to be told how the maximum number of invocations to track in the
// history buffer. Typically this number is pretty small, but there are cases
// where a deeper history buffer is required. The '5' being passed into
// 'Mock_Vars' is this depth. This must come before the declaration of mocks.
// The 'Mock_Vars' also declared variables private to the UnitTest framework
// and is not optional.

Mock_Vars(5);   // must come before mocks

// The application source has two external dependencies, the two functions:
// "mod_GetInt" and "mod_Init".  The framework can provide mock (stub)
// implementations of these functions that the application code can call. In
// the unit test we can fake return values and inspect the parameters the
// application passed to the mocks. If needed you can supply the behavior for
// the mock function.
//
// I declare the mocks in  alphabetical order to make managing them easier.

// This creates the mock function for "mod_GetInt". We need to tell the
// framework the name of the function we want it to mock, and in this case the
// type that the function returns. The order of the arguments to the Mock_xxx
// macros always match the C syntax, so Mock_Value(type, name).
Mock_Value(int, mod_GetInt);

// This creates the mock function for "mod_Init". We need to tell the framework
// the name of the function. This is a "void" function, so jus the name is
// needed.
Mock_Void(mod_Init);

// It is very common to have a assortment of constants that are used in testing
// I prefix all names that are specific to testing with the "TEST_" or "test_"
// prefix.
#define TEST_UNSET  0x42

// By convention all tests have a setUp function. The frame work does not
// require or even know about the setUp funtion- you will be calling it manually
// in you tests. By convention there is always a setUp function (even if it is
// empty). The setUp function perform the initialization of state for the test.
// Some times more than one setup function is created to setup for different
// scenarios. In these case I typically chain the setUp functions:
// setUp_foo() -> setup().
static void setUp(void)
{
    // The mock functions need to be reset for each test case. Failure to do so
    // will result is erroneous call counts returned by the framework. Forgetting
    // to reset the mock is a common mistake when getting started with the
    // framework.  Again the oder here is alphabetical, making it easy to scan
    // the mock declarations and the reset calls to verify all the mocks are
    // reset.
    Mock_Reset(mod_GetInt);
    Mock_Reset(mod_Init);

    // When the application calls the "mod_GetInt" function it must return a
    // value. We need to tell the framework what value to return. There are a
    // couple of options here:
    // 1. We can tell the framework to always return a constant value.
    // 2. We can give the framework a sequence of values to return on each call.
    // 3. We can provide a custom body for the function that will return
    // whatever value we compute.
    // For this eample we are going to keep things simple and use option #1 and
    // always return a constant value.
    //
    // One other thing to note here: We don'e need to do this in the setUp
    // function. Often the return value is specific to a test and the return
    // value is set in the unit test function.
    Mock_Returns(mod_GetInt, TEST_UNSET);
}

// This is a unit test function. They are "static" because when we forget to
// call the function in the test main (and you will forget) the compiler will
// warn about an unused local function. By convention the functions are always
// prefixed with "test_" because they are test specific (they are the tests!).
static void test_Init(void)
{
    // First we need to setup for the test. We always call setUp for this...
    setUp();
    // Sometimes there is setup that is required just for this test. This goes
    // after the call to setUp.

    // Now we call the unit user test...
    main_Init();

    // Now we make assertions about what the unit should have/have not of done.
    // In this case we verify that the unit called "mod_Init" once and
    // "mod_GetInt" was never called. If these function has parameters we could
    // verify the values passed to them are the expected values.
    Assert_CalledOnce(mod_Init);
    Assert_NotCalled(mod_GetInt);
}

// Another test function. These are also organized in alphabetical order to they
// are easy to find in the file.
static void test_Loop(void)
{
    setUp();

    main_Loop();

    Assert_CalledOnce(mod_GetInt);
    Assert_NotCalled(mod_Init);
}

// This is the main function for the test suit. This is the main that is used
// the the framework compiles and runs the tests for the suit.
int main(int argc, char **argv)
{
    // This initializes the test framework. Call this function first before any
    // test functions.
    Assert_Init();

    // Now call the test function. Note the order here matches the oder the
    // functions are declared in the file.
    test_Init();
    test_Loop();

    // The performs post processing the testing. Call this function after all
    // of the test functions.
    Assert_Save();

    // We return zero here to indicate everything went OK. Not not return any
    // value other than zero.
    return 0;
}