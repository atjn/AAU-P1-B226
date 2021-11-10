#include "../lib/CuTest-AAU/CuTest.h"
#include <stdio.h>
#include <math.h>
#include "definition.h"

/**
 * Sample function - this is what a function looks like with an included function test.
 */

int gaming(){
    return 3;
}

void testGaming(CuTest *tc){
    int actual = gaming();
    int expected = 3;
    CuAssertIntEquals(tc, expected, actual);
}
