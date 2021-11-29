#include "../lib/CuTest-AAU/CuTest.h"

#include <stdio.h>
#include <ctype.h>

void flushInput(){
    int inputChar;

    while((inputChar = getchar()) != '\n' && inputChar != EOF);
}

void capitaliseFirst(char* string){

    string[0] = toupper(string[0]);

}

void testCapitaliseFirst(CuTest* testCase){

    char string1[] = "hello";
    capitaliseFirst(string1);
    CuAssertStrEquals(testCase, "Hello", string1);

    char string2[] = "hello _?";
    capitaliseFirst(string2);
    CuAssertStrEquals(testCase, "Hello _?", string2);

    char string3[] = "Hello";
    capitaliseFirst(string3);
    CuAssertStrEquals(testCase, "Hello", string3);

    char string4[] = "HELLO";
    capitaliseFirst(string4);
    CuAssertStrEquals(testCase, "HELLO", string4);

    char string5[] = "&unicorns";
    capitaliseFirst(string5);
    CuAssertStrEquals(testCase, "&unicorns", string5);

    char string6[] = "123";
    capitaliseFirst(string6);
    CuAssertStrEquals(testCase, "123", string6);

    char string7[] = "";
    capitaliseFirst(string7);
    CuAssertStrEquals(testCase, "", string7);

    char string8[] = " ";
    capitaliseFirst(string8);
    CuAssertStrEquals(testCase, " ", string8);

    char string9[] = "   ";
    capitaliseFirst(string9);
    CuAssertStrEquals(testCase, "   ", string9);

}

void toLowerCase(char* string){

    for(int i = 0; string[i]; i++){
        string[i] = tolower(string[i]);
    }

}

void testToLowerCase(CuTest* testCase){

    char string1[] = "PHOENIX";
    toLowerCase(string1);
    CuAssertStrEquals(testCase, "phoenix", string1);

    char string2[] = "PhoenIx";
    toLowerCase(string2);
    CuAssertStrEquals(testCase, "phoenix", string2);

    char string3[] = "moO";
    toLowerCase(string3);
    CuAssertStrEquals(testCase, "moo", string3);

    char string4[] = "moo";
    toLowerCase(string4);
    CuAssertStrEquals(testCase, "moo", string4);

    char string5[] = "Ph03n1x says MOO!!";
    toLowerCase(string5);
    CuAssertStrEquals(testCase, "ph03n1x says moo!!", string5);

    char string6[] = "";
    toLowerCase(string6);
    CuAssertStrEquals(testCase, "", string6);

    char string7[] = " ";
    toLowerCase(string7);
    CuAssertStrEquals(testCase, " ", string7);

    char string8[] = "&_!/";
    toLowerCase(string8);
    CuAssertStrEquals(testCase, "&_!/", string8);

}
