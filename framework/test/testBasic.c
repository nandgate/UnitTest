/******************************************************************************
* Copyright (C) <2016> NAND Gate Technologies LLC
* Permission is hereby granted, free of charge, to any person obtaining a copy 
* of this software and associated documentation files (the "Software"), to 
* deal in the Software without restriction, including without limitation the 
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
* sell copies of the Software, and to permit persons to whom the Software is 
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
* NAND GATE TECHNOLOGIES LLC BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
* THE SOFTWARE.
* 
* Except as contained in this notice, the name of NAND Gate Technolgies LLC 
* shall not be used in advertising or otherwise to promote the sale, use or 
* other dealings in this Software without prior written authorization from 
* NAND Gate Technolgies.
******************************************************************************/

#include "../UnitTest.h"

Mock_Vars(0);

static void setUp(void) {
    _assertions= 0;
    _mockExit= false;    
}

static void test_Pass_AssertArrayEquals(void) {
    setUp();
    uint8_t expected[] = {1, 2, 3};
    uint8_t actaul[] = {1, 2, 3};
    
    Assert_ArrayEquals(3, expected, actaul);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertArrayEquals\n");
        exit(-1);
    }
}

static void test_Fail_AssertArrayEquals(void) {
    setUp();
    uint8_t expected[] = {1, 2, 3};
    uint8_t actaul[] = {1, 2, 0};
        
    Assert_ArrayEquals(3, expected, actaul);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertArrayEquals\n");
        exit(-1);
    }
}
    
static void test_Pass_AssertEquals(void) {
    setUp();
    
    Assert_Equals(42, 42);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertEquals\n");
        exit(-1);
    }
}

static void test_Fail_AssertEquals(void) {
    setUp();
    
    Assert_Equals(42, 24);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertEquals\n");
        exit(-1);
    }
}

static void test_Pass_AssertEqualsLong(void) {
    setUp();
    
    Assert_EqualsLong(0x1122334455667788, 0x1122334455667788);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertEqualsLong\n");
        exit(-1);
    }
}

static void test_Fail_AssertEqualsLong(void) {
    setUp();
    
    Assert_EqualsLong(0x1122334455667788, 0x2233445566778899);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertEqualsLong\n");
        exit(-1);
    }
}

static void test_Pass_AssertEqualsFloat(void) {
    setUp();
    
    Assert_EqualsFloat(0.123, 0.1234, 0.1);
    Assert_EqualsFloat(0.123, 0.1234, 0.01);
    Assert_EqualsFloat(0.123, 0.1234, 0.001);

    Assert_EqualsFloat(0.1234, 0.123, 0.1);
    Assert_EqualsFloat(0.1234, 0.123, 0.01);
    Assert_EqualsFloat(0.1234, 0.123, 0.001);
    
    if (_assertions != 6) {
        printf("**Fail: test_Pass_AssertEqualsFloat\n");
        exit(-1);
    }
}

static void test_Fail_AssertEqualsFloat(void) {
    setUp();
    
    Assert_EqualsFloat(0.123, 0.1234, 0.0001);
    Assert_EqualsFloat(0.1234, 0.123, 0.0001);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertEqualsFloat\n");
        exit(-1);
    }
}

static void test_Fail_AssertFail(void) {
    setUp();
    
    Assert_Fail("failure message");
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertFail\n");
        exit(-1);
    }
}

static void test_Pass_AssertFalse(void) {
    setUp();
    
    Assert_False(0);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertFalse\n");
        exit(-1);
    }
}

static void test_Fail_AssertFalse(void) {
    setUp();
    
    Assert_False(42);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertFalse\n");
        exit(-1);
    }
}

static void test_Pass_AssertNotEquals(void) {
    setUp();
    
    Assert_NotEquals(42, 24);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertNotEquals\n");
        exit(-1);
    }
}

static void test_Fail_AssertNotEquals(void) {
    setUp();
    
    Assert_NotEquals(42, 42);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertNotEquals\n");
        exit(-1);
    }
}

static void test_Pass_AssertIsNotNull(void) {
    setUp();
    char *ptr= "ABC";
    
    Assert_IsNotNull(&ptr);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertIsNotNull\n");
        exit(-1);
    }
}

static void test_Fail_AssertIsNotNull(void) {
    setUp();
    
    Assert_IsNotNull(NULL);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertIsNotNull\n");
        exit(-1);
    }
}

static void test_Pass_AssertIsNull(void) {
    setUp();
    
    Assert_IsNull(NULL);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertIsNull\n");
        exit(-1);
    }
}

static void test_Fail_AssertIsNull(void) {
    setUp();
    char *ptr= "ABC";
    
    Assert_IsNull(ptr);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertIsNull\n");
        exit(-1);
    }
}

static void test_Pass_AssertStrEquals(void) {
    setUp();
    char *expected= "ABC";
    char *actual= "ABC";
    
    Assert_StrEquals(expected, actual);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertStrEquals\n");
        exit(-1);
    }
}

static void test_FailLen_AssertStrEquals(void) {
    setUp();
    char *expected= "ABC";
    char *actual= "ABCD";
    
    Assert_StrEquals(expected, actual);
    
    if (_assertions != 0) {
        printf("**Fail: test_FailLen_AssertStrEquals\n");
        exit(-1);
    }
}

static void test_FailValue_AssertStrEquals(void) {
    setUp();
    char *expected= "ABC";
    char *actual= "ABZ";
    
    Assert_StrEquals(expected, actual);
    
    if (_assertions != 0) {
        printf("**Fail: test_FailValue_AssertStrEquals\n");
        exit(-1);
    }
}

static void test_Pass_AssertTrue(void) {
    setUp();
    
    Assert_True(42);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertTrue\n");
        exit(-1);
    }
}

static void test_Fail_AssertTrue(void) {
    setUp();
    
    Assert_True(0);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertTrue\n");
        exit(-1);
    }
}

static void test_InitSave(void) {
    setUp();
    
    _assertions = 5;
    Assert_Save();

    _assertions = 0;
    Assert_Init();

    if (_assertions != 5) {
        printf("**Fail: test_InitSave: %d\n", _assertions);
        exit(-1);
    }

}

int main(int argc, char **argv) {
    test_Pass_AssertArrayEquals();
    test_Fail_AssertArrayEquals();

    test_Pass_AssertEquals();
    test_Fail_AssertEquals();

    test_Pass_AssertEqualsLong();
    test_Fail_AssertEqualsLong();

    test_Pass_AssertEqualsFloat();
    test_Fail_AssertEqualsFloat();

    test_Fail_AssertFail();

    test_Pass_AssertFalse();
    test_Fail_AssertFalse();

    test_Pass_AssertNotEquals();
    test_Fail_AssertNotEquals();

    test_Pass_AssertIsNotNull();
    test_Fail_AssertIsNotNull();

    test_Pass_AssertIsNull();
    test_Fail_AssertIsNull();

    test_Pass_AssertStrEquals();
    test_FailLen_AssertStrEquals();
    test_FailValue_AssertStrEquals();

    test_Pass_AssertTrue();
    test_Fail_AssertTrue();
    
    test_InitSave();
    
    printf("**Tests complete\n");
    return 0;
}
