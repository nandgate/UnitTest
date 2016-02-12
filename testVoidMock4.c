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

Mock_Void4(testFn, uint8_t, uint8_t, uint8_t, uint8_t);

bool wasFakeCalled;
void fake_testFn(uint8_t arg0, uint8_t arg1, uint8_t arg2, uint8_t arg3) {
    Assert_Equals(1, arg0);
    Assert_Equals(2, arg1);
    Assert_Equals(3, arg2);
    Assert_Equals(4, arg3);
    wasFakeCalled= true;
}

static void setUp(void) {
    _assertions= 0;
    _mockExit= false;
    wasFakeCalled= false;
    
    Mock_Reset(testFn);
}

static void test_MockDepth_Void_Arg4(void) {
    setUp();

    for(uint32_t i= 0; i < _mockDepth+1; i++) {
        testFn(0, 1, 2, 3);
    }
}

static void test_Pass_AssertCallCount_Arg4(void) {
    setUp();
    Assert_CallCount(0, testFn);

    testFn(0, 1, 2, 3);
    Assert_CallCount(1, testFn);

    testFn(1, 2, 3, 4);
    Assert_CallCount(2, testFn);

    if (_assertions != 3) {
        printf("**Fail: test_Pass_AssertCallCount_Arg4\n");
        exit(-1);
    }
}

static void test_Fail_AssertCallCount_Arg4(void) {
    setUp();
    Assert_CallCount(0, testFn);

    testFn(0, 1, 2, 3);
    testFn(1, 2, 3, 4);
    Assert_CallCount(1, testFn);

    if (_assertions != 1) {
        printf("**Fail: test_Fail_AssertCallCount_Arg4\n");
        exit(-1);
    }
}

static void test_Pass_AssertCalledOnce_Arg4(void) {
    setUp();

    testFn(0, 1, 2, 3);
    Assert_CalledOnce(testFn);

    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalledOnce_Arg4\n");
        exit(-1);
    }
}

static void test_Fail_AssertCalledOnce_Arg4(void) {
    setUp();

    Assert_CalledOnce(testFn);
    testFn(0, 1, 2, 3);
    testFn(1, 2, 3, 4);
    Assert_CalledOnce(testFn);

    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalledOnce_Arg4\n");
        exit(-1);
    }
}

static void test_Pass_AssertNotCalled_Arg4(void) {
    setUp();

    Assert_NotCalled(testFn);

    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertNotCalled_Arg4\n");
        exit(-1);
    }
}

static void test_Fail_AssertNotCalled_Arg4(void) {
    setUp();

    testFn(0, 1, 2, 3);
    Assert_NotCalled(testFn);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertNotCalled_Arg4\n");
        exit(-1);
    }
}

static void test_Pass_AssertCalled4_Arg4(void) {
    setUp();

    testFn(0, 1, 2, 3);
    testFn(1, 2, 3, 4);
    testFn(2, 3, 4, 5);
    testFn(3, 4, 5, 6);

    Assert_Called4(testFn, 2, 3, 4, 5);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalled4_Arg4\n");
        exit(-1);
    }
}

static void test_Fail_AssertCalled4_Arg4(void) {
    setUp();

    testFn(0, 1, 2, 3);
    testFn(1, 2, 3, 4);
    testFn(2, 3, 4, 5);
    testFn(3, 4, 5, 6);

    Assert_Called4(testFn, 0, 1, 2, 4);
    Assert_Called4(testFn, 0, 1, 4, 3);
    Assert_Called4(testFn, 0, 4, 2, 3);
    Assert_Called4(testFn, 4, 1, 2, 3);
    Assert_Called4(testFn, 4, 4, 4, 4);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalled4_Arg4\n");
        exit(-1);
    }
}

static void test_Pass_AssertCalledFirst_Arg4(void) {
    setUp();

    testFn(0, 1, 2, 3);
    testFn(1, 2, 3, 4);

    Assert_CalledFirst4(testFn, 0, 1, 2, 3);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalledFirst_Arg4\n");
        exit(-1);
    }
}

static void test_Fail_AssertCalledFirst_Arg4(void) {
    setUp();

    testFn(1, 2, 3, 4);
    testFn(0, 1, 2, 3);

    Assert_CalledFirst4(testFn, 0, 1, 2, 3);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalledFirst_Arg4\n");
        exit(-1);
    }    
}

static void test_FailNoCalles_AssertCalledFirst_Arg4() {
    setUp();

    Assert_CalledFirst4(testFn, 0, 1, 2, 3);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalledFirst_Arg4\n");
        exit(-1);
    }    
}

static void test_Pass_AssertCalledLast_Arg4(void) {
    setUp();

    testFn(0, 1, 2, 3);
    testFn(1, 2, 3, 4);

    Assert_CalledLast4(testFn, 1, 2, 3, 4);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalledLast_Arg4\n");
        exit(-1);
    }
}

static void test_Fail_AssertCalledLast_Arg4(void) {
    setUp();

    testFn(1, 2, 3, 4);
    testFn(0, 2, 3, 4);

    Assert_CalledLast4(testFn, 1, 2, 3, 4);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalledLast_Arg4\n");
        exit(-1);
    }    
}

static void test_FailNoCalles_AssertCalledLast_Arg4() {
    setUp();

    Assert_CalledLast4(testFn, 0, 1, 2, 3);
    
    if (_assertions != 0) {
        printf("**Fail: test_FailNoCalles_AssertCalledLast_Arg4\n");
        exit(-1);
    }    
}

static void test_Pass_AssertCalledN_Arg4(void) {
    setUp();

    testFn(0, 1, 2, 3);
    testFn(1, 2, 3, 4);

    Assert_CalledN4(2, testFn, 1, 2, 3, 4);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalledLast_Arg4\n");
        exit(-1);
    }
}

static void test_Fail_AssertCalledN_Arg4(void) {
    setUp();

    testFn(1, 2, 3, 4);
    testFn(0, 1, 2, 3);

    Assert_CalledN4(2, testFn, 1, 2, 3, 4);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalledLast_Arg4\n");
        exit(-1);
    }    
}

static void test_FailNoCalles_AssertCalledN_Arg4(void) {
    setUp();
    
    Assert_CalledN4(2, testFn, 0, 1, 2, 3);
    
    if (_assertions != 0) {
        printf("**Fail: test_FailNoCalles_AssertCalledLast_Arg4\n");
        exit(-1);
    }    
}

static void test_Pass_AssertAllCalls_Arg4(void) {
    setUp();

    testFn(0, 1, 2, 3);
    testFn(0, 1, 2, 3);
    testFn(0, 1, 2, 3);

    Assert_AllCalls4(testFn, 3);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertAllCalls_Arg4\n");
        exit(-1);
    }
}

static void test_Fail_AssertAllCalls_Arg4(void) {
    setUp();

    testFn(0, 1, 2, 3);
    testFn(0, 1, 2, 3);
    testFn(1, 2, 3, 4);

    Assert_AllCalls4(testFn, 3);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertAllCalls_Arg4\n");
        exit(-1);
    }    
}

static void test_CustomMock_Arg4(void) {
    setUp();
    Mock_Custom(testFn, fake_testFn);
    
    testFn(1, 2, 3, 4);
    
    if (wasFakeCalled == false) {
        printf("**Fail: test_CustomMock_Arg4\n");
        exit(-1);
    }        
}

int main(int argc, char **argv) {
    test_MockDepth_Void_Arg4();
    
    test_Pass_AssertCallCount_Arg4();
    test_Fail_AssertCallCount_Arg4();

    test_Pass_AssertCalledOnce_Arg4();
    test_Fail_AssertCalledOnce_Arg4();

    test_Pass_AssertNotCalled_Arg4();
    test_Fail_AssertNotCalled_Arg4();

    test_Pass_AssertCalled4_Arg4();
    test_Fail_AssertCalled4_Arg4();
    
    test_Pass_AssertCalledFirst_Arg4();
    test_Fail_AssertCalledFirst_Arg4();
    test_FailNoCalles_AssertCalledFirst_Arg4();

    test_Pass_AssertCalledLast_Arg4();
    test_Fail_AssertCalledLast_Arg4();
    test_FailNoCalles_AssertCalledLast_Arg4();

    test_Pass_AssertCalledN_Arg4();
    test_Fail_AssertCalledN_Arg4();
    test_FailNoCalles_AssertCalledN_Arg4();

    test_Pass_AssertAllCalls_Arg4();
    test_Fail_AssertAllCalls_Arg4();
    
    test_CustomMock_Arg4();
    
    printf("**Tests complete\n");
    return 0;
}
