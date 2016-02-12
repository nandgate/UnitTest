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

#include "UnitTest.h"

Mock_Vars(5);   // must come before mocks

Mock_Value5(uint8_t, testFn, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);

bool wasFakeCalled;
uint8_t fake_testFn(uint8_t arg0, uint8_t arg1, uint8_t arg2, uint8_t arg3, uint8_t arg4) {
    Assert_Equals(1, arg0);
    Assert_Equals(2, arg1);
    Assert_Equals(3, arg2);
    Assert_Equals(4, arg3);
    Assert_Equals(4, arg4);
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

    testFn(1, 2, 3, 4, 5);
}

static void test_Returns(void) {
    setUp();
    Mock_Returns(testFn, 1);

    uint8_t result;
    result= testFn(1, 2, 3, 4, 5);    
    if(result != 1) {
        printf("**Fail: test_Returns call 1: %d\n", result);
        exit(-1);
    }

    result= testFn(1, 2, 3, 4, 5);    
    if(result != 1) {
        printf("**Fail: test_Returns call 2: %d\n", result);
        exit(-1);
    }
}

static void test_Custom(void) {
    setUp();
    Mock_Custom(testFn, fake_testFn);
    
    uint8_t result;
    result= testFn(1, 2, 3, 4, 5);    
    if(result != 42) {
        printf("**Fail: test_Custom call 1: %d\n", result);
        exit(-1);
    }

    result= testFn(1, 2, 3, 4, 5);    
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
    result= testFn(1, 2, 3, 4, 5);
    if(result != 21) {
        printf("**Fail: test_ReturnsSequence call 1: %d\n", result);
        exit(-1);
    }

    result= testFn(1, 2, 3, 4, 5);
    if(result != 32) {
        printf("**Fail: test_ReturnsSequence call 2: %d\n", result);
        exit(-1);
    }

    result= testFn(1, 2, 3, 4, 5);
    if(result != 43) {
        printf("**Fail: test_ReturnsSequence call 3: %d\n", result);
        exit(-1);
    }

    result= testFn(1, 2, 3, 4, 5);
    if(result != 43) {
        printf("**Fail: test_ReturnsSequence call 4: %d\n", result);
        exit(-1);
    }
}

static void test_Pass_AssertReturns_Arg5(void) {
    setUp();
    uint8_t seq[3]= {21, 32, 43};
    Mock_ReturnsSequence(testFn, 3, seq);
    
    testFn(1, 2, 3, 4, 5);
    testFn(1, 2, 3, 4, 5);
    testFn(1, 2, 3, 4, 5);
    testFn(1, 2, 3, 4, 5);

    Assert_Returned(testFn, 32);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertReturns_Arg5\n");
        exit(-1);
    }
}

static void test_Fail_AssertReturns_Arg5(void) {
    setUp();
    uint8_t seq[3]= {21, 32, 43};
    Mock_ReturnsSequence(testFn, 3, seq);
    
    testFn(1, 2, 3, 4, 5);
    testFn(1, 2, 3, 4, 5);
    testFn(1, 2, 3, 4, 5);
    testFn(1, 2, 3, 4, 5);

    Assert_Returned(testFn, 42);

    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertReturns_Arg5\n");
        exit(-1);
    }
}

static void test_MockDepth_Void_Arg5(void) {
    setUp();
    Mock_Returns(testFn, 1);

    for(uint32_t i= 0; i < _mockDepth+1; i++) {
        testFn(0, 1, 2, 3, 4);
    }
}

static void test_Pass_AssertCallCount_Arg5(void) {
    setUp();
    Mock_Returns(testFn, 1);

    Assert_CallCount(0, testFn);

    testFn(0, 1, 2, 3, 5);
    Assert_CallCount(1, testFn);

    testFn(1, 2, 3, 4, 5);
    Assert_CallCount(2, testFn);

    if (_assertions != 3) {
        printf("**Fail: test_Pass_AssertCallCount_Arg5\n");
        exit(-1);
    }
}

static void test_Fail_AssertCallCount_Arg5(void) {
    setUp();
    Mock_Returns(testFn, 1);

    Assert_CallCount(0, testFn);

    testFn(0, 1, 2, 3, 4);
    testFn(1, 2, 3, 4, 5);
    Assert_CallCount(1, testFn);

    if (_assertions != 1) {
        printf("**Fail: test_Fail_AssertCallCount_Arg5\n");
        exit(-1);
    }
}

static void test_Pass_AssertCalledOnce_Arg5(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(0, 1, 2, 3, 4);
    Assert_CalledOnce(testFn);

    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalledOnce_Arg5\n");
        exit(-1);
    }
}

static void test_Fail_AssertCalledOnce_Arg5(void) {
    setUp();
    Mock_Returns(testFn, 1);

    Assert_CalledOnce(testFn);
    testFn(0, 1, 2, 3, 4);
    testFn(1, 2, 3, 4, 5);
    Assert_CalledOnce(testFn);

    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalledOnce_Arg5\n");
        exit(-1);
    }
}

static void test_Pass_AssertNotCalled_Arg5(void) {
    setUp();
    Mock_Returns(testFn, 1);

    Assert_NotCalled(testFn);

    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertNotCalled_Arg5\n");
        exit(-1);
    }
}

static void test_Fail_AssertNotCalled_Arg5(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(0, 1, 2, 3, 4);
    Assert_NotCalled(testFn);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertNotCalled_Arg5\n");
        exit(-1);
    }
}

static void test_Pass_AssertCalled5_Arg5(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(0, 1, 2, 3, 4);
    testFn(1, 2, 3, 4, 5);
    testFn(2, 3, 4, 5, 6);
    testFn(3, 4, 5, 6, 7);

    Assert_Called5(testFn, 2, 3, 4, 5, 6);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalled5_Arg5\n");
        exit(-1);
    }
}

static void test_Fail_AssertCalled5_Arg5(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(0, 1, 2, 3, 4);
    testFn(1, 2, 3, 4, 5);
    testFn(2, 3, 4, 5, 6);
    testFn(3, 4, 5, 6, 7);

    Assert_Called5(testFn, 0, 1, 2, 3, 5);
    Assert_Called5(testFn, 0, 1, 2, 5, 5);
    Assert_Called5(testFn, 0, 1, 5, 3, 4);
    Assert_Called5(testFn, 0, 5, 2, 3, 4);
    Assert_Called5(testFn, 5, 1, 2, 3, 4);
    Assert_Called5(testFn, 5, 5, 5, 5, 5);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalled5_Arg5\n");
        exit(-1);
    }
}

static void test_Pass_AssertCalledFirst_Arg5(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(0, 1, 2, 3, 4);
    testFn(1, 2, 3, 4, 5);

    Assert_CalledFirst5(testFn, 0, 1, 2, 3, 4);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalledFirst_Arg5\n");
        exit(-1);
    }
}

static void test_Fail_AssertCalledFirst_Arg5(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(1, 2, 3, 4, 5);
    testFn(0, 1, 2, 3, 4);

    Assert_CalledFirst5(testFn, 0, 1, 2, 3, 4);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalledFirst_Arg5\n");
        exit(-1);
    }    
}

static void test_FailNoCalles_AssertCalledFirst_Arg5() {
    setUp();
    Mock_Returns(testFn, 1);

    Assert_CalledFirst5(testFn, 0, 1, 2, 3, 4);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalledFirst_Arg5\n");
        exit(-1);
    }    
}

static void test_Pass_AssertCalledLast_Arg5(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(0, 1, 2, 3, 4);
    testFn(1, 2, 3, 4, 5);

    Assert_CalledLast5(testFn, 1, 2, 3, 4, 5);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalledLast_Arg5\n");
        exit(-1);
    }
}

static void test_Fail_AssertCalledLast_Arg5(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(1, 2, 3, 4, 5);
    testFn(0, 2, 3, 4, 5);

    Assert_CalledLast5(testFn, 1, 2, 3, 4, 5);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalledLast_Arg5\n");
        exit(-1);
    }    
}

static void test_FailNoCalles_AssertCalledLast_Arg5() {
    setUp();
    Mock_Returns(testFn, 1);

    Assert_CalledLast5(testFn, 0, 1, 2, 3, 4);
    
    if (_assertions != 0) {
        printf("**Fail: test_FailNoCalles_AssertCalledLast_Arg5\n");
        exit(-1);
    }    
}

static void test_Pass_AssertCalledN_Arg5(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(0, 1, 2, 3, 4);
    testFn(1, 2, 3, 4, 5);

    Assert_CalledN5(2, testFn, 1, 2, 3, 4, 5);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalledLast_Arg5\n");
        exit(-1);
    }
}

static void test_Fail_AssertCalledN_Arg5(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(1, 2, 3, 4, 5);
    testFn(0, 1, 2, 3, 4);

    Assert_CalledN5(2, testFn, 1, 2, 3, 4, 5);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalledLast_Arg5\n");
        exit(-1);
    }    
}

static void test_FailNoCalles_AssertCalledN_Arg5(void) {
    setUp();
    Mock_Returns(testFn, 1);
    
    Assert_CalledN5(2, testFn, 0, 1, 2, 3, 4);
    
    if (_assertions != 0) {
        printf("**Fail: test_FailNoCalles_AssertCalledLast_Arg5\n");
        exit(-1);
    }    
}

static void test_Pass_AssertAllCalls_Arg5(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(0, 1, 2, 3, 4);
    testFn(0, 1, 2, 3, 4);
    testFn(0, 1, 2, 3, 4);

    Assert_AllCalls5(testFn, 4);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertAllCalls_Arg5\n");
        exit(-1);
    }
}

static void test_Fail_AssertAllCalls_Arg5(void) {
    setUp();
    Mock_Returns(testFn, 1);

    testFn(0, 1, 2, 3, 4);
    testFn(0, 1, 2, 3, 0);
    testFn(0, 2, 3, 4, 4);

    Assert_AllCalls5(testFn, 4);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertAllCalls_Arg5\n");
        exit(-1);
    }    
}

static void test_CustomMock_Arg5(void) {
    setUp();
    Mock_Custom(testFn, fake_testFn);
    
    testFn(1, 2, 3, 4, 5);
    
    if (wasFakeCalled == false) {
        printf("**Fail: test_CustomMock_Arg5\n");
        exit(-1);
    }        
}

int main(int argc, char **argv) {
    test_ReturnNotSet();
    test_Custom();
    test_Returns();
    test_ReturnsSequence();

    test_Pass_AssertReturns_Arg5();
    test_Fail_AssertReturns_Arg5();

    test_MockDepth_Void_Arg5();
    
    test_Pass_AssertCallCount_Arg5();
    test_Fail_AssertCallCount_Arg5();

    test_Pass_AssertCalledOnce_Arg5();
    test_Fail_AssertCalledOnce_Arg5();

    test_Pass_AssertNotCalled_Arg5();
    test_Fail_AssertNotCalled_Arg5();

    test_Pass_AssertCalled5_Arg5();
    test_Fail_AssertCalled5_Arg5();
    
    test_Pass_AssertCalledFirst_Arg5();
    test_Fail_AssertCalledFirst_Arg5();
    test_FailNoCalles_AssertCalledFirst_Arg5();

    test_Pass_AssertCalledLast_Arg5();
    test_Fail_AssertCalledLast_Arg5();
    test_FailNoCalles_AssertCalledLast_Arg5();

    test_Pass_AssertCalledN_Arg5();
    test_Fail_AssertCalledN_Arg5();
    test_FailNoCalles_AssertCalledN_Arg5();

    test_Pass_AssertAllCalls_Arg5();
    test_Fail_AssertAllCalls_Arg5();
    
    test_CustomMock_Arg5();
    
    printf("**Tests complete\n");
    return 0;
}
