#include "../lib/CuTest-AAU/CuTest.h"

#include <stdio.h>
#include <ctype.h>

/**
 * Flushes the input buffer.
 * This is useful when taking input from the user with `scanf`,
 * because unreadable input might be left in the buffer, causing an infinite loop.
 */
void flushInput(){
    int inputChar;

    while((inputChar = getchar()) != '\n' && inputChar != EOF);
}

/**
This function capitalises the first character of a string.
*/
const char* capitaliseFirst(char* string){

    string[0] = toupper(string[0]);
    return string;
}
