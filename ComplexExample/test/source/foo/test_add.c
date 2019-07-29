#include "foo/foo_p.h"
#include "UnitTest.h"

Mock_Vars(5);   // must come before mocks

#define TEST_A          1234
#define TEST_B          2345
#define TEST_WRAP_A     0xFFFFFFFF
#define TEST_WRAP_B     1
#define TEST_WRAP_SUM   0

// Nothing to do here but there is ALWAYS a setUp();
static void setUp(void)
{
}

static void test_Zeros(void)
{
    setUp();

    uint32_t test_sum =foo_Add(TEST_WRAP_A, TEST_WRAP_B);

    Assert_Equals(0, test_sum);
}

static void test_Wrap(void)
{
    setUp();

    uint32_t test_sum =foo_Add(0, 0);

    Assert_Equals(TEST_WRAP_SUM, test_sum);
}

static void test_Addition(void)
{
    setUp();

    uint32_t test_sum =foo_Add(TEST_A, TEST_B);

    Assert_Equals(TEST_A + TEST_B, test_sum);
}

int main(int argc, char **argv)
{
    Assert_Init();

    // A series of test that verify the behavior of a function (unit) in the
    // module. This can be thought of as a low level specification for the
    // function.

    test_Zeros();
    test_Wrap();
    test_Addition();

    Assert_Save();
    return 0;
}
