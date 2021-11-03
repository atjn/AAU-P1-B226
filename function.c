#include "lib/CuTest-AAU/CuTest.h"

/**
 * Sample function - this is what a function looks like with an included function test.
 */

int function(){
    return 1;
}
int jespersFunction(){
    return 3;
}


void testFunction1(CuTest *tc){
    int actual = function();
    int expected = 1;
    CuAssertIntEquals(tc, expected, actual);
}

void testJespersFunction(CuTest *tc){
    int actual = jespersFunction();
    int expected = 2;
    CuAssertIntEquals(tc, expected, actual);
}
