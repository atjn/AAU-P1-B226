#include "../lib/CuTest-AAU/CuTest.h"
#include "definitions.h"

#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

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

/**
 * Takes the letters in a char array and makes them all lower case.
 */
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

/**
 * Returns the factorial of a given integer
 */
int factorial(const int size){
    assert(size >= 0);
    int result = 1;
    for (int i = 1; i <= size; i++){
        result = result * i;
    }
    return result;
}

void testFactorial(CuTest *testCase){

    CuAssertIntEquals(testCase, 1, factorial(1));

     CuAssertIntEquals(testCase, 120, factorial(5));

     CuAssertIntEquals(testCase, 5040, factorial(7));

     CuAssertIntEquals(testCase, 1, factorial(0));

}

/**
 * Takes the name (string) of a category, and returns it index in the array of categories.
 * If no match is found, returns -1.
 */
int getCategoryIndex(const char *categoryName, const Category *categories, const int categoriesLength) {

    for (int i = 0; i < categoriesLength; i++){
        if (strcmp(categoryName, categories[i].name) == 0) {
            return i;
        }
    }

    return -1;
}

void testGetCategoryIndex(CuTest* tc){

    const Category categories[] = {
        {
            "cowsFarts",
            {NULL},1,
        },
        {
            "cows",
            {NULL},1,
        },
        {
            "based beans",
            {NULL},1,
        },
        {
            "3 acres of 5",
            {NULL},1,
        },
    };
    const int categoriesLength = sizeof(categories) / sizeof(categories[0]);

    CuAssertIntEquals(tc, 0, getCategoryIndex("cowsFarts", categories, categoriesLength));
    CuAssertIntEquals(tc, 1, getCategoryIndex("cows", categories, categoriesLength));
    CuAssertIntEquals(tc, -1, getCategoryIndex("cow", categories, categoriesLength));

    CuAssertIntEquals(tc, 2, getCategoryIndex("based beans", categories, categoriesLength));
    CuAssertIntEquals(tc, 3, getCategoryIndex("3 acres of 5", categories, categoriesLength));

    CuAssertIntEquals(tc, -1, getCategoryIndex("3", categories, categoriesLength));
    CuAssertIntEquals(tc, -1, getCategoryIndex("5", categories, categoriesLength));
    CuAssertIntEquals(tc, -1, getCategoryIndex("s", categories, categoriesLength));
    CuAssertIntEquals(tc, -1, getCategoryIndex(" ", categories, categoriesLength));
    CuAssertIntEquals(tc, -1, getCategoryIndex("", categories, categoriesLength));

}

/**
 * Calculating the total COO emission of a given recipe
 * TODO: change the structure of the Ingredient struct to include
 * a pointer to the corresponding IngredientData struct
 */
float calculateRecipeCoo(Recipe *recipe, IngredientData *ingredients, int ingrNum) {
    float tempCOO = 0;
    for (int i = 0; i < recipe->ingredientCount; i++) {
        for (int j = 0; j < ingrNum; j++) {
            if (strcmp(recipe->ingredients[i].name, ingredients[j].name) == 0) {
                tempCOO += ingredients[j].coo * (recipe->ingredients[i].amount/1000);
                break;
            }
        }
    }
    return tempCOO;
}

/**
 * Returns the total COO emission of a given ingredient
 * TODO: change the structure of the Ingredient struct to include
 * a pointer to the corresponding IngredientData struct
 */
float getIngrCoo(Ingredient *ingredient, IngredientData *ingredients, int ingrNum) {
    float tempCoo = 0;
    for (int j = 0; j < ingrNum; j++) {
        if (strcmp(ingredient->name, ingredients[j].name) == 0) {
            tempCoo = ingredients[j].coo;
        }
    }
    return tempCoo;
}
