#!/usr/bin/env bash

function unit_test {
    pushd test
    ./test.sh
    testResult=$?
    popd

    if [ $testResult -ne 0 ]
    then
	    echo "unit test failures- build halted"
        exit 0
    fi
    echo "unit tests passed, building for target"
}

unit_test

# do stuff to build the app here...

echo Build complete.
