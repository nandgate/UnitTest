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

Mock_Void(testFn);

bool wasFakeCalled;
void fake_testFn(void) {
    wasFakeCalled= true;
}

static void setUp(void) {
    _assertions= 0;
    _mockExit= false;
    wasFakeCalled= false;
    
    Mock_Reset(testFn);
}

static void test_MockDepth_Void_Arg0(void) {
    setUp();

    for(uint32_t i= 0; i < _mockDepth+1; i++) {
        testFn();
    }
}

static void test_Pass_AssertCallCount_Arg0(void) {
    setUp();
    Assert_CallCount(0, testFn);

    testFn();
    Assert_CallCount(1, testFn);

    testFn();
    Assert_CallCount(2, testFn);

    if (_assertions != 3) {
        printf("**Fail: test_Pass_AssertCallCount_Arg0\n");
        exit(-1);
    }
}

static void test_Fail_AssertCallCount_Arg0(void) {
    setUp();
    Assert_CallCount(0, testFn);

    testFn();
    testFn();
    Assert_CallCount(1, testFn);

    if (_assertions != 1) {
        printf("**Fail: test_Fail_AssertCallCount_Arg0\n");
        exit(-1);
    }
}

static void test_Pass_AssertCalledOnce_Arg0(void) {
    setUp();

    testFn();
    Assert_CalledOnce(testFn);

    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalledOnce_Arg0\n");
        exit(-1);
    }
}

static void test_Fail_AssertCalledOnce_Arg0(void) {
    setUp();

    Assert_CalledOnce(testFn);
    testFn();
    testFn();
    Assert_CalledOnce(testFn);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalledOnce_Arg0\n");
        exit(-1);
    }
}

static void test_Pass_AssertNotCalled_Arg0(void) {
    setUp();

    Assert_NotCalled(testFn);

    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertNotCalled_Arg0\n");
        exit(-1);
    }
}

static void test_Fail_AssertNotCalled_Arg0(void) {
    setUp();

    testFn();
    Assert_NotCalled(testFn);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertNotCalled_Arg0\n");
        exit(-1);
    }
}

static void test_Pass_AssertCalled_Arg0(void) {
    setUp();

    testFn();
    Assert_Called0(testFn);
    
    if (_assertions != 1) {
        printf("**Fail: test_Pass_AssertCalled_Arg0\n");
        exit(-1);
    }    
}

static void test_Fail_AssertCalled_Arg0(void) {
    setUp();

    Assert_Called0(testFn);
    
    if (_assertions != 0) {
        printf("**Fail: test_Fail_AssertCalled_Arg0\n");
        exit(-1);
    }    
}

static void test_CustomMock_Arg0(void) {
    setUp();
    Mock_Custom(testFn, fake_testFn);
    
    testFn();
    
    if (wasFakeCalled == false) {
        printf("**Fail: test_CustomMock_Arg0\n");
        exit(-1);
    }        
}

int main(int argc, char **argv) {
    test_MockDepth_Void_Arg0();
    
    test_Pass_AssertCallCount_Arg0();
    test_Fail_AssertCallCount_Arg0();

    test_Pass_AssertCalledOnce_Arg0();
    test_Fail_AssertCalledOnce_Arg0();

    test_Pass_AssertNotCalled_Arg0();
    test_Fail_AssertNotCalled_Arg0();
    
    test_Pass_AssertCalled_Arg0();
    test_Fail_AssertCalled_Arg0();    
    
    test_CustomMock_Arg0();
    
    printf("**Tests complete\n");
    return 0;
}
