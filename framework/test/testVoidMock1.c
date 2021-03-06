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
* Except as contained in this notice, the name of NAND Gate Technologies LLC
* shall not be used in advertising or otherwise to promote the sale, use or 
* other dealings in this Software without prior written authorization from 
* NAND Gate Technologies.
******************************************************************************/

#include "../UnitTest.h"

Mock_Vars(5);   // must come before mocks

Mock_Void1(testFn, uint8_t);
Mock_Void1(testFnOther, uint8_t);

bool wasFakeCalled;
void fake_testFn(uint8_t arg0) {
    Assert_Equals(1, arg0);
    wasFakeCalled= true;
}

static void setUp(void) {
    _assertions= 0;
    _mockExit= false;
    wasFakeCalled= false;
    
    Mock_Reset(testFn);
    Mock_Reset(testFnOther);
}

static void test_MockDepth_Void_Arg1(void) {
    setUp();

    for(uint32_t i= 0; i < _mockDepth+1; i++) {
        testFn(0);
    }
}

static void test_Pass_AssertCallCount_Arg1(void) {
    setUp();
    Assert_CallCount(0, testFn);

    testFn(0);
    Assert_CallCount(1, testFn);

    testFn(1);
    Assert_CallCount(2, testFn);

    if (_assertions != 3) {
        printf("**Fail: test_Pass_AssertCallCount_Arg1\n");
        exit(-1);
    }
}

static void test_Fail_AssertCallCount_Arg1(void) {
    setUp();
    Assert_CallCount(0, testFn);

    testFn(0);
    testFn(1);
    Assert_CallCount(1, testFn);

    if (_assertions != 1) {
        printf("**Fail: test_Fail_AssertCallCount_Arg1\n");
        exit(-1);
    }
}

static void test_Pass_AssertCalledOnce_Arg1(void) {
    setUp();

    testFn(1);
    Assert_CalledOnce(testFn);

    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalledOnce_Arg1\n");
        exit(-1);
    }
}

static void test_Fail_AssertCalledOnce_Arg1(void) {
    setUp();

    Assert_CalledOnce(testFn);
    testFn(0);
    testFn(1);
    Assert_CalledOnce(testFn);

    if (_assertions != 0) {
        printf("**Fail: test_Pass_AssertCalledOnce_Arg1\n");
        exit(-1);
    }
}

static void test_Pass_AssertNotCalled_Arg1(void) {
    setUp();

    Assert_NotCalled(testFn);

    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertNotCalled_Arg1\n");
        exit(-1);
    }
}

static void test_Fail_AssertNotCalled_Arg1(void) {
    setUp();

    testFn(0);
    Assert_NotCalled(testFn);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertNotCalled_Arg1\n");
        exit(-1);
    }
}

static void test_Pass_AssertCalled1_Arg1(void) {
    setUp();

    testFn(0);
    testFn(1);
    testFn(2);
    testFn(3);

    Assert_Called1(testFn, 2);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalled1_Arg1\n");
        exit(-1);
    }
}

static void test_Fail_AssertCalled1_Arg1(void) {
    setUp();

    testFn(0);
    testFn(1);
    testFn(2);
    testFn(3);

    Assert_Called1(testFn, 4);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalled1_Arg1\n");
        exit(-1);
    }
}

static void test_Pass_AssertCalledFirst_Arg1(void) {
    setUp();

    testFn(0);
    testFn(1);

    Assert_CalledFirst1(testFn, 0);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalledFirst_Arg1\n");
        exit(-1);
    }
}

static void test_Fail_AssertCalledFirst_Arg1(void) {
    setUp();

    testFn(1);
    testFn(0);

    Assert_CalledFirst1(testFn, 0);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalledFirst_Arg1\n");
        exit(-1);
    }    
}

static void test_FailNoCalles_AssertCalledFirst_Arg1() {
    setUp();

    Assert_CalledFirst1(testFn, 0);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalledFirst_Arg1\n");
        exit(-1);
    }    
}

static void test_Pass_AssertCalledLast_Arg1(void) {
    setUp();

    testFn(0);
    testFn(1);

    Assert_CalledLast1(testFn, 1);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalledLast_Arg1\n");
        exit(-1);
    }
}

static void test_Fail_AssertCalledLast_Arg1(void) {
    setUp();

    testFn(1);
    testFn(0);

    Assert_CalledLast1(testFn, 1);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalledLast_Arg1\n");
        exit(-1);
    }    
}

static void test_FailNoCalles_AssertCalledLast_Arg1() {
    setUp();

    Assert_CalledLast1(testFn, 0);
    
    if (_assertions != 0) {
        printf("**Fail: test_FailNoCalles_AssertCalledLast_Arg1\n");
        exit(-1);
    }    
}

static void test_Pass_AssertCalledN_Arg1(void) {
    setUp();

    testFn(0);
    testFn(1);

    Assert_CalledN1(2, testFn, 1);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalledLast_Arg1\n");
        exit(-1);
    }
}

static void test_Fail_AssertCalledN_Arg1(void) {
    setUp();

    testFn(1);
    testFn(0);

    Assert_CalledN1(2, testFn, 1);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalledLast_Arg1\n");
        exit(-1);
    }    
}

static void test_FailNoCalles_AssertCalledN_Arg1(void) {
    setUp();
    
    Assert_CalledN1(2, testFn, 0);
    
    if (_assertions != 0) {
        printf("**Fail: test_FailNoCalles_AssertCalledLast_Arg1\n");
        exit(-1);
    }    
}

static void test_Pass_AssertAllCallsEquals_Arg1(void) {
    setUp();

    testFn(0);
    testFn(0);
    testFn(0);

    Assert_AllCallsEquals1(testFn, 0);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertAllCallsEquals_Arg1\n");
        exit(-1);
    }
}

static void test_Fail_AssertAllCallsEquals_Arg1(void) {
    setUp();

    testFn(0);
    testFn(0);
    testFn(1);

    Assert_AllCallsEquals1(testFn, 2);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertAllCallsEquals_Arg1\n");
        exit(-1);
    }    
}

static void test_Pass_AssertAllCallsLessThan_Arg1(void) {
    setUp();

    testFn(0);
    testFn(1);
    testFn(2);

    Assert_AllCallsLessThan1(testFn, 3);

    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertAllCallsLessThan_Arg1\n");
        exit(-1);
    }
}

static void test_Fail_AssertAllCallsLessThan_Arg1(void) {
    setUp();

    testFn(0);
    testFn(1);
    testFn(2);

    Assert_AllCallsLessThan1(testFn, 2);

    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertAllCallsLessThan_Arg1\n");
        exit(-1);
    }
}

static void test_Pass_AssertAllCallsGreaterThan_Arg1(void) {
    setUp();

    testFn(2);
    testFn(3);
    testFn(4);

    Assert_AllCallsGreaterThan1(testFn, 1);

    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertAllCallsGreaterThan_Arg1\n");
        exit(-1);
    }
}

static void test_Fail_AssertAllCallsGreaterThan_Arg1(void) {
    setUp();

    testFn(2);
    testFn(3);
    testFn(4);

    Assert_AllCallsGreaterThan1(testFn, 2);

    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertAllCallsGreaterThan_Arg1\n");
        exit(-1);
    }
}

static void test_CustomMock_Arg1(void) {
    setUp();
    Mock_Custom(testFn, fake_testFn);
    
    testFn(1);
    
    if (wasFakeCalled == false) {
        printf("**Fail: test_CustomMock_Arg1\n");
        exit(-1);
    }        
}

int main(int argc, char **argv) {
    test_MockDepth_Void_Arg1();
    
    test_Pass_AssertCallCount_Arg1();
    test_Fail_AssertCallCount_Arg1();

    test_Pass_AssertCalledOnce_Arg1();
    test_Fail_AssertCalledOnce_Arg1();

    test_Pass_AssertNotCalled_Arg1();
    test_Fail_AssertNotCalled_Arg1();

    test_Pass_AssertCalled1_Arg1();
    test_Fail_AssertCalled1_Arg1();

    test_Pass_AssertCalledFirst_Arg1();
    test_Fail_AssertCalledFirst_Arg1();    
    test_FailNoCalles_AssertCalledFirst_Arg1();    

    test_Pass_AssertCalledLast_Arg1();
    test_Fail_AssertCalledLast_Arg1();    
    test_FailNoCalles_AssertCalledLast_Arg1();    

    test_Pass_AssertCalledN_Arg1();
    test_Fail_AssertCalledN_Arg1();    
    test_FailNoCalles_AssertCalledN_Arg1();    
    
    test_Pass_AssertAllCallsEquals_Arg1();
    test_Fail_AssertAllCallsEquals_Arg1();

    test_Pass_AssertAllCallsLessThan_Arg1();
    test_Fail_AssertAllCallsLessThan_Arg1();

    test_Pass_AssertAllCallsGreaterThan_Arg1();
    test_Fail_AssertAllCallsGreaterThan_Arg1();

    test_CustomMock_Arg1();
    
    printf("**Tests complete\n");
    return 0;
}
