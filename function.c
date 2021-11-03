#include "lib/CuTest-AAU/CuTest.h"
#include <stdio.h>
#include <math.h>

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

int function(){
    return 1;
}
int jespersFunction(){
    return 2;
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

int brixFunction() {
    for (int i = 0; i < pow(10, 2); i++) {
        //printf("Abekat %d\n", i);
    }
    return 1;
}

void testFunction2(CuTest *tc){
    int actual = brixFunction();
    int expected = 1;

    CuAssertIntEquals(tc, expected, actual);
}
