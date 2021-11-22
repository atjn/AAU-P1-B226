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
 * Capitalises the first character of a string.
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

/**
 * Takes the letters in a char array and makes them all lower case.
 */
const char* toLowerCase(char* string){

    char* lowerString = string;

    for(int i = 0; string[i]; i++){
        string[i] = tolower(string[i]);
    }

    return lowerString;
}

void testToLowerCase(CuTest* testCase){

    char string1[] = "PHOENIX";
    CuAssertStrEquals(testCase, "phoenix", toLowerCase(string1));

    char string2[] = "PhoenIx";
    CuAssertStrEquals(testCase, "phoenix", toLowerCase(string2));

    char string3[] = "moO";
    CuAssertStrEquals(testCase, "moo", toLowerCase(string3));

    char string4[] = "moo";
    CuAssertStrEquals(testCase, "moo", toLowerCase(string4));

    char string5[] = "Ph03n1x says MOO!!";
    CuAssertStrEquals(testCase, "ph03n1x says moo!!", toLowerCase(string5));

    char string6[] = "";
    CuAssertStrEquals(testCase, "", toLowerCase(string6));

    char string7[] = " ";
    CuAssertStrEquals(testCase, " ", toLowerCase(string7));

    char string8[] = "&_!/";
    CuAssertStrEquals(testCase, "&_!/", toLowerCase(string8));

}
