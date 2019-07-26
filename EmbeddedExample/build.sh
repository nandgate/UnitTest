#!/usr/bin/env bash

# We want to ensure that the unit test are run EVERY build.
# I typically wrap the running of the unit tests into a function like this
# to make it easier to push down, run the test then pop back up to complete
# the build.
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

# This run the entire test suit.
unit_test

# do stuff to build the app for the target here...

echo Build complete.
