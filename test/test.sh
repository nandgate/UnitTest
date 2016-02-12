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

runManualTests() {
    :   # this is the null command, remove it when tests manually specified
}

CC_FLAGS="-arch i386 -std=c99 -Wall -Iinclude -I../app/include"

runTest() {
    #echo
    echo "gcc $CC_FLAGS $*"
    gcc -o test.exe $CC_FLAGS $*
    ./test.exe
    rm test.exe
}

runAutoTests() {
    testPath="../app/source"${1:+/$1}
    for sourceFilePath in $(find $testPath -name '*.c'); do
        # TODO: black list manually specified source files.
        sourceFileName=${sourceFilePath##*/}
        sourcePath=${sourceFilePath%/*}
        modulePath=${sourcePath#*app/}
        testFileName="test_${sourceFileName}"
        testFilePath="${modulePath}/$testFileName"

        if [ -e "$testFilePath" ]
        then
            runTest $sourceFilePath $testFilePath
        fi
    done
}

rm -f assertions.txt
if [ -z $1 ]
then
    runManualTests
fi

runAutoTests $1

if [ -e "assertions.txt" ]
then
    echo
    echo -n Total Assertions:
    cat assertions.txt
fi

