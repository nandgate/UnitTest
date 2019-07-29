#include "foo/foo_p.h"
#include "UnitTest.h"

Mock_Vars(5);   // must come before mocks

// The unit under test has a dependency on this function, mock it...
Mock_Value2(uint32_t, foo_Add, uint32_t, uint32_t);

#define TEST_UNSET          0x42
#define TEST_VALUE_FROM_ADD 0x1234
#define TEST_NUM_CALLS      3

// A local variable used by the test. typically to track or spy on some state.
uint32_t test_sum;

// See test_CallCustomMock.
// A function to be called by the mock to implement behaviors beyond argument
// capture and simple returns. Note the arguments are still captured before
// the custom mock is called...
static uint32_t test_Add(uint32_t a, uint32_t b)
{
    test_sum = a + b;
    return TEST_VALUE_FROM_ADD;
}

static void setUp(void)
{
    // For each test case the mocks need to be reset...
    Mock_Reset(foo_Add);
}

// Various assertions on the arguments passed to mock functions.
static void test_ArgumentsToMock(void)
{
    setUp();
    // Failure to tell the test framework how to mock return values will report
    // in a compile time error.
    Mock_Returns(foo_Add, TEST_VALUE_FROM_ADD);

    foo_Doit();

    // Verify the number times the mock was called. Note that there is also
    // Assert_CalledOnce(fn), which is VERY handy.
    Assert_CallCount(TEST_NUM_CALLS, foo_Add);

    // We can assert that the first call to the mock has specific argument
    // values. Note the "2" refers to the number of arguments we are going
    // assert on.
    Assert_CalledFirst2(foo_Add, FOO_FIRST_ARG0, FOO_SECOND_ARG0);

    // We can assert the that one or more call to the mock has specific argument
    // values. Note the "2" refers to the number of arguments we are going
    // assert on. (This is assertion that is typically used for testing calls)
    Assert_Called2(foo_Add, FOO_FIRST_ARG1, FOO_SECOND_ARG1);

    // We can assert the the last call to the mock has specific argument
    // values. Note the "2" refers to the number of arguments we are going
    // assert on.
    Assert_CalledLast2(foo_Add, FOO_FIRST_ARG2, FOO_SECOND_ARG2);

    // We can assert on fewer arguments then the mock function implements...
    // This is a handy trick, sometimes you don't know or care what the actual
    // argument value is (e.g. pointers).
    Assert_Called1(foo_Add, FOO_FIRST_ARG1);

    // We can assert that the exact number of invocations to the mock with the
    // specific argument values.
    Assert_CalledN2(1, foo_Add, FOO_FIRST_ARG1, FOO_SECOND_ARG1);
}

// Example of a mock that always return the same value.
static void test_ValueFromMock(void)
{
    setUp();
    Mock_Returns(foo_Add, TEST_VALUE_FROM_ADD);

    uint32_t result  = foo_Doit();  // calls foo_Add multiple times

    Assert_CallCount(TEST_NUM_CALLS, foo_Add);
    Assert_Equals(TEST_VALUE_FROM_ADD * TEST_NUM_CALLS, result);
}

// Example of a mock that returns values from a sequence.
static void test_SequenceFromMock(void)
{
    setUp();
    uint32_t test_addSeq[3] = { 1, 2, 3};   // the values to return

    // Register the sequence with the test framework. The "3" is the length of
    // the sequence. When the number of calls to the mock exceed the sequence
    // length then the last element of the sequence is returned. So in this case
    // the values returned from foo_Add if it were called five times would be:
    // 1, 2, 3, 3, 3.
    Mock_ReturnsSequence(foo_Add, 3, test_addSeq);

    uint32_t result  = foo_Doit();  // calls foo_Add multiple times

    Assert_CallCount(TEST_NUM_CALLS, foo_Add);
    Assert_Equals(1+2+3, result);
}

// Example of a mock that implements a custom body. The arguments are captured
// by the framework and then the custom function is called.
static void test_CallCustomMock(void)
{
    setUp();
    Mock_Custom(foo_Add, test_Add);

    uint32_t result = foo_Doit();

    Assert_Equals(TEST_VALUE_FROM_ADD * TEST_NUM_CALLS, result);
    Assert_Equals(FOO_FIRST_ARG2 + FOO_SECOND_ARG2, test_sum);
}


int main(int argc, char **argv)
{
    Assert_Init();

    test_ArgumentsToMock();

    test_ValueFromMock();
    test_SequenceFromMock();
    test_CallCustomMock();

    Assert_Save();
    return 0;
}
