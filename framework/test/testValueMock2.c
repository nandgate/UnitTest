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

Mock_Vars(5);   // must come before mocks

Mock_Value2(uint8_t, testFn, uint8_t, uint8_t);

bool wasFakeCalled;
uint8_t fake_testFn(uint8_t arg0, uint8_t arg1) {
    Assert_Equals(1, arg0);
    Assert_Equals(2, arg1);
    wasFakeCalled= true;
    return 42;
}

static void setUp(void) {
    _assertions= 0;
    _mockExit= false;
    wasFakeCalled= false;
    
    Mock_Reset(testFn);
}

static void test_ReturnNotSet(void) {
    setUp();

    testFn(1, 2);
}

static void test_Returns(void) {
    setUp();
    Mock_Returns(testFn, 1);

    uint8_t result;
    result= testFn(1, 2);    
    if(result != 1) {
        printf("**Fail: test_Returns call 1: %d\n", result);
        exit(-1);
    }

    result= testFn(1, 2);    
    if(result != 1) {
        printf("**Fail: test_Returns call 2: %d\n", result);
        exit(-1);
    }
}

static void test_Custom(void) {
    setUp();
    Mock_Custom(testFn, fake_testFn);
    
    uint8_t result;
    result= testFn(1, 2);    
    if(result != 42) {
        printf("**Fail: test_Custom call 1: %d\n", result);
        exit(-1);
    }

    result= testFn(1, 2);    
    if(result != 42) {
        printf("**Fail: test_Custom call 2: %d\n", result);
        exit(-1);
    }
}

static void test_ReturnsSequence(void) {
    setUp();
    uint8_t seq[3]= {21, 32, 43};
    Mock_ReturnsSequence(testFn, 3, seq);
    
    uint8_t result;
    result= testFn(1, 2);
    if(result != 21) {
        printf("**Fail: test_ReturnsSequence call 1: %d\n", result);
        exit(-1);
    }

    result= testFn(1, 2);
    if(result != 32) {
        printf("**Fail: test_ReturnsSequence call 2: %d\n", result);
        exit(-1);
    }

    result= testFn(1, 2);
    if(result != 43) {
        printf("**Fail: test_ReturnsSequence call 3: %d\n", result);
        exit(-1);
    }

    result= testFn(1, 2);
    if(result != 43) {
        printf("**Fail: test_ReturnsSequence call 4: %d\n", result);
        exit(-1);
    }
}

static void test_Pass_AssertReturns_Arg2(void) {
    setUp();
    uint8_t seq[3]= {21, 32, 43};
    Mock_ReturnsSequence(testFn, 3, seq);
    
    testFn(1, 2);
    testFn(1, 2);
    testFn(1, 2);
    testFn(1, 2);

    Assert_Returned(testFn, 32);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertReturns_Arg2\n");
        exit(-1);
    }
}

static void test_Fail_AssertReturns_Arg2(void) {
    setUp();
    uint8_t seq[3]= {21, 32, 43};
    Mock_ReturnsSequence(testFn, 3, seq);
    
    testFn(1, 2);
    testFn(1, 2);
    testFn(1, 2);
    testFn(1, 2);

    Assert_Returned(testFn, 42);

    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertReturns_Arg2\n");
        exit(-1);
    }
}

static void test_MockDepth_Void_Arg2(void) {
    setUp();
    Mock_Returns(testFn, 1);

    for(uint32_t i= 0; i < _mockDepth+1; i++) {
        testFn(0, 1);
    }
}

static void test_Pass_AssertCallCount_Arg2(void) {
    setUp();
    Mock_Returns(testFn, 1);

    Assert_CallCount(0, testFn);

    testFn(0, 1);
    Assert_CallCount(1, testFn);

    testFn(1, 2);
    Assert_CallCount(2, testFn);

    if (_assertions != 3) {
        printf("**Fail: test_Pass_AssertCallCount_Arg2\n");
        exit(-1);
    }
}

static void test_Fail_AssertCallCount_Arg2(void) {
    setUp();
    Mock_Returns(testFn, 1);

    Assert_CallCount(0, testFn);

    testFn(0, 1);
    testFn(1, 2);
    Assert_CallCount(1, testFn);

    if (_assertions != 1) {
        printf("**Fail: test_Fail_AssertCallCount_Arg2\n");
        exit(-1);
    }
}

static void test_Pass_AssertCalledOnce_Arg2(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(0, 1);
    Assert_CalledOnce(testFn);

    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalledOnce_Arg2\n");
        exit(-1);
    }
}

static void test_Fail_AssertCalledOnce_Arg2(void) {
    setUp();
    Mock_Returns(testFn, 1);

    Assert_CalledOnce(testFn);
    testFn(0, 1);
    testFn(1, 2);
    Assert_CalledOnce(testFn);

    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalledOnce_Arg2\n");
        exit(-1);
    }
}

static void test_Pass_AssertNotCalled_Arg2(void) {
    setUp();
    Mock_Returns(testFn, 1);

    Assert_NotCalled(testFn);

    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertNotCalled_Arg2\n");
        exit(-1);
    }
}

static void test_Fail_AssertNotCalled_Arg2(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(0, 1);
    Assert_NotCalled(testFn);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertNotCalled_Arg2\n");
        exit(-1);
    }
}

static void test_Pass_AssertCalled2_Arg2(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(0, 1);
    testFn(1, 2);
    testFn(2, 3);
    testFn(3, 4);

    Assert_Called2(testFn, 2, 3);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalled2_Arg2\n");
        exit(-1);
    }
}

static void test_Fail_AssertCalled2_Arg2(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(0, 1);
    testFn(1, 2);
    testFn(2, 3);
    testFn(3, 4);

    Assert_Called2(testFn, 1, 4);
    Assert_Called2(testFn, 4, 1);
    Assert_Called2(testFn, 4, 4);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalled2_Arg2\n");
        exit(-1);
    }
}

static void test_Pass_AssertCalledFirst_Arg2(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(0, 1);
    testFn(1, 2);

    Assert_CalledFirst2(testFn, 0, 1);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalledFirst_Arg2\n");
        exit(-1);
    }
}

static void test_Fail_AssertCalledFirst_Arg2(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(1, 2);
    testFn(0, 1);

    Assert_CalledFirst2(testFn, 0, 1);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalledFirst_Arg2\n");
        exit(-1);
    }    
}

static void test_FailNoCalles_AssertCalledFirst_Arg2() {
    setUp();
    Mock_Returns(testFn, 1);

    Assert_CalledFirst2(testFn, 0, 1);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalledFirst_Arg2\n");
        exit(-1);
    }    
}

static void test_Pass_AssertCalledLast_Arg2(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(0, 1);
    testFn(1, 2);

    Assert_CalledLast2(testFn, 1, 2);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalledLast_Arg2\n");
        exit(-1);
    }
}

static void test_Fail_AssertCalledLast_Arg2(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(1, 2);
    testFn(0, 2);

    Assert_CalledLast2(testFn, 1, 2);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalledLast_Arg2\n");
        exit(-1);
    }    
}

static void test_FailNoCalles_AssertCalledLast_Arg2() {
    setUp();
    Mock_Returns(testFn, 1);

    Assert_CalledLast2(testFn, 0, 1);
    
    if (_assertions != 0) {
        printf("**Fail: test_FailNoCalles_AssertCalledLast_Arg2\n");
        exit(-1);
    }    
}

static void test_Pass_AssertCalledN_Arg2(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(0, 1);
    testFn(1, 2);

    Assert_CalledN2(2, testFn, 1, 2);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalledLast_Arg2\n");
        exit(-1);
    }
}

static void test_Fail_AssertCalledN_Arg2(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(1, 2);
    testFn(0, 1);

    Assert_CalledN2(2, testFn, 1, 2);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalledLast_Arg2\n");
        exit(-1);
    }    
}

static void test_FailNoCalles_AssertCalledN_Arg2(void) {
    setUp();
    Mock_Returns(testFn, 1);
    
    Assert_CalledN2(2, testFn, 0, 1);
    
    if (_assertions != 0) {
        printf("**Fail: test_FailNoCalles_AssertCalledLast_Arg2\n");
        exit(-1);
    }    
}

static void test_Pass_AssertAllCalls_Arg2(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(0, 1);
    testFn(0, 1);
    testFn(0, 1);

    Assert_AllCalls2(testFn, 1);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertAllCalls_Arg2\n");
        exit(-1);
    }
}

static void test_Fail_AssertAllCalls_Arg2(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(0, 1);
    testFn(0, 1);
    testFn(1, 2);

    Assert_AllCalls2(testFn, 1);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertAllCalls_Arg2\n");
        exit(-1);
    }    
}

static void test_CustomMock_Arg2(void) {
    setUp();
    Mock_Custom(testFn, fake_testFn);
    
    testFn(1, 2);
    
    if (wasFakeCalled == false) {
        printf("**Fail: test_CustomMock_Arg2\n");
        exit(-1);
    }        
}

int main(int argc, char **argv) {
    test_ReturnNotSet();
    test_Custom();
    test_Returns();
    test_ReturnsSequence();
    
    test_Pass_AssertReturns_Arg2();
    test_Fail_AssertReturns_Arg2();
    
    test_MockDepth_Void_Arg2();
    
    test_Pass_AssertCallCount_Arg2();
    test_Fail_AssertCallCount_Arg2();

    test_Pass_AssertCalledOnce_Arg2();
    test_Fail_AssertCalledOnce_Arg2();

    test_Pass_AssertNotCalled_Arg2();
    test_Fail_AssertNotCalled_Arg2();

    test_Pass_AssertCalled2_Arg2();
    test_Fail_AssertCalled2_Arg2();

    test_Pass_AssertCalledFirst_Arg2();
    test_Fail_AssertCalledFirst_Arg2();
    test_FailNoCalles_AssertCalledFirst_Arg2();

    test_Pass_AssertCalledLast_Arg2();
    test_Fail_AssertCalledLast_Arg2();
    test_FailNoCalles_AssertCalledLast_Arg2();

    test_Pass_AssertCalledN_Arg2();
    test_Fail_AssertCalledN_Arg2();
    test_FailNoCalles_AssertCalledN_Arg2();

    test_Pass_AssertAllCalls_Arg2();
    test_Fail_AssertAllCalls_Arg2();
    
    test_CustomMock_Arg2();
    
    printf("**Tests complete\n");
    return 0;
}
