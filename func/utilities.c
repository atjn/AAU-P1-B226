#include "../lib/CuTest-AAU/CuTest.h"

#include <stdio.h>

/**
 * Flush the input buffer.
 * Otherwise scanf will read the previous answer, and create an infinite loop.
 */
void flushInput(){
    int inputChar;

    while((inputChar = getchar()) != '\n' && inputChar != EOF);
}
