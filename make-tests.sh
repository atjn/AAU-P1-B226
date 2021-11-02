#!/usr/bin/env bash

# NOTE: This is a modified version of the "make-tests" script in the CuTest library, distributed under a Zlib-like license.
# The original script, along with a full license and author details can be found in the "lib/CuTest-AAU/" folder in this repository.

# Auto generate single AllTests file for CuTest.
# Searches through all *.c files in the current directory.
# Prints to stdout.
# Author: Asim Jalis
# Date: 01/08/2003

if test $# -eq 0 ; then FILES=*.c ; else FILES=$* ; fi

echo '

/*
 * This is auto-generated code. Edit at your own peril.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lib/CuTest-AAU/CuTest.h"

'

cat $FILES | grep '^void test' |
    sed -e 's/(.*$//' \
        -e 's/$/(CuTest*);/' \
        -e 's/^/extern /'

echo \
'

bool runAllTests(){
    bool success = true;

    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();

'
cat $FILES | grep '^void test' |
    sed -e 's/^void //' \
        -e 's/(.*$//' \
        -e 's/^/    SUITE_ADD_TEST(suite, /' \
        -e 's/$/);/'

echo \
"
    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);

    /*
     * This information should ideally be passed as a bool directly from CuTest,
     * but we don't want to change upstream code, so this hack will suffice
     */
    if(strchr(output->buffer, 'F') != NULL) success = false;

    CuSuiteDetails(suite, output);
    printf(\"%s\n\", output->buffer);
    CuStringDelete(output);
    CuSuiteDelete(suite);

    return success;
}
"
