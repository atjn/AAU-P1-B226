#include "lib/CuTest-AAU/CuTest.h"

/**
 * Sample function - this is what a function looks like with an included function test.
 */

int function(){
    return 1;
}

void testFunction1(CuTest *tc){
    int actual = function();
    int expected = 1;
    CuAssertIntEquals(tc, expected, actual);
}

int howLongIsAddisSlong(){
    int cm = 32;
    return cm;
}

void testFunktion2(CuTest *tc){
    int actual = howLongIsAddisSlong();
    int expected = 32;
    CuAssertIntEquals(tc, expected, actual);
}