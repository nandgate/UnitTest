
#include "hal/chip.h"
#include "hal/Led_p.h"
#include "UnitTest.h"

Mock_Vars(5);   // must come before mocks

#define TEST_UNSET          0x42
#define TEST_LED            LED_BUSY
#define TEST_LED_MASK       LED_BUSY_MASK
#define TEST_INVALID_LED    NUMBER_OF_LEDS

static void setUp(void)
{
    gpio->dirSet= TEST_UNSET;
    gpio->outClear = TEST_UNSET;
    gpio->outSet = TEST_UNSET;
}

static void test_Init_LedPinsAreOutputs(void)
{
    setUp();

    led_Init();

    Assert_Equals(LED_MASK, gpio->dirSet);
}

static void test_Init_AllLedsOff(void)
{
    setUp();

    led_Init();

    Assert_Equals(LED_MASK, gpio->outClear);
}

static void test_LedOn(void)
{
    setUp();

    led_On(TEST_LED);

    Assert_Equals(TEST_LED_MASK, gpio->outSet);
    Assert_Equals(TEST_UNSET, gpio->outClear);
}

static void test_LedOn_IvalidLed(void)
{
    setUp();

    led_On(TEST_INVALID_LED);

    Assert_Equals(TEST_UNSET, gpio->outSet);
    Assert_Equals(TEST_UNSET, gpio->outClear);
}

static void test_LedOff(void)
{
    setUp();

    led_Off(TEST_LED);

    Assert_Equals(TEST_LED_MASK, gpio->outClear);
    Assert_Equals(TEST_UNSET, gpio->outSet);
}

static void test_LedOff_IvalidLed(void)
{
    setUp();

    led_Off(TEST_INVALID_LED);

    Assert_Equals(TEST_UNSET, gpio->outSet);
    Assert_Equals(TEST_UNSET, gpio->outClear);
}

static void test_LedToggle_AlreadyOn(void)
{
    setUp();
    gpio->in |= TEST_LED_MASK;

    led_Toggle(TEST_LED);

    Assert_Equals(TEST_LED_MASK, gpio->outClear);
    Assert_Equals(TEST_UNSET, gpio->outSet);
}

static void test_LedToggle_AlreadyOff(void)
{
    setUp();
    gpio->in &= ~TEST_LED_MASK;

    led_Toggle(TEST_LED);

    Assert_Equals(TEST_LED_MASK, gpio->outSet);
    Assert_Equals(TEST_UNSET, gpio->outClear);
}

static void test_LedToggle_IvalidLed(void)
{
    setUp();

    led_Toggle(TEST_INVALID_LED);

    Assert_Equals(TEST_UNSET, gpio->outSet);
    Assert_Equals(TEST_UNSET, gpio->outClear);
}

int main(int argc, char **argv)
{
    Assert_Init();

    test_Init_LedPinsAreOutputs();
    test_Init_AllLedsOff();

    test_LedOn();
    test_LedOn_IvalidLed();

    test_LedOff();
    test_LedOff_IvalidLed();

    test_LedToggle_AlreadyOn();
    test_LedToggle_AlreadyOff();
    test_LedToggle_IvalidLed();

    Assert_Save();
    return 0;
}