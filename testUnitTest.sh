#!/bin/bash
###############################################################################
# Copyright (C) <2016> NAND Gate Technologies LLC
# Permission is hereby granted, free of charge, to any person obtaining a copy 
# of this software and associated documentation files (the "Software"), to 
# deal in the Software without restriction, including without limitation the 
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
# sell copies of the Software, and to permit persons to whom the Software is 
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in 
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
# NAND GATE TECHNOLOGIES LLC BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
# THE SOFTWARE.
# 
# Except as contained in this notice, the name of NAND Gate Technolgies LLC 
# shall not be used in advertising or otherwise to promote the sale, use or 
# other dealings in this Software without prior written authorization from 
# NAND Gate Technolgies.
###############################################################################

function runTest {
    echo -e "\n**" $1
    rm a.out
    gcc -std=c99 -Wall $1
    ./a.out
}

clear
runTest testBasic.c
runTest testValueMock0.c
runTest testValueMock1.c
runTest testValueMock2.c
runTest testValueMock3.c
runTest testValueMock4.c
runTest testValueMock5.c
runTest testVoidMock0.c
runTest testVoidMock1.c
runTest testVoidMock2.c
runTest testVoidMock3.c
runTest testVoidMock4.c
runTest testVoidMock5.c
