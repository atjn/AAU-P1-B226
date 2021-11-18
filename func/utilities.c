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

void testCapitaliseFirst(CuTest* testCase){

    char string1[] = "hello";
    CuAssertStrEquals(testCase, "Hello", capitaliseFirst(string1));

    char string2[] = "hello _?";
    CuAssertStrEquals(testCase, "Hello _?", capitaliseFirst(string2));

    char string3[] = "Hello";
    CuAssertStrEquals(testCase, "Hello", capitaliseFirst(string3));

    char string4[] = "HELLO";
    CuAssertStrEquals(testCase, "HELLO", capitaliseFirst(string4));

    char string5[] = "&unicorns";
    CuAssertStrEquals(testCase, "&unicorns", capitaliseFirst(string5));

    char string6[] = "123";
    CuAssertStrEquals(testCase, "123", capitaliseFirst(string6));

    char string7[] = "";
    CuAssertStrEquals(testCase, "", capitaliseFirst(string7));

    char string8[] = " ";
    CuAssertStrEquals(testCase, " ", capitaliseFirst(string8));

    char string9[] = "   ";
    CuAssertStrEquals(testCase, "   ", capitaliseFirst(string9));

}
