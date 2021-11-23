#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "../lib/CuTest-AAU/CuTest.h"

#include "./definitions.h"
#include "./ui.h"
#include "./utilities.h"

int getIdFromString(char *, Recipe *, int);
void padAround(char [], char [], int);
void printLine(char [], char [], char [], int, int []);

//This function ask the user for a recipe name. If it cannot match the user input to a recipe, it will return itself, and thus start the process again.
//It returns an `int` corresponding the index of the recipe in the recipes array.
int requestRecipeName(Recipe *recipes, int recipeCount){
    char recipeName[MAX_RECIPE_NAME];

    printf("What recipe do you want to make? ");
    const int inputs = scanf(" %s", recipeName);

    flushInput();

    if (inputs <= 0)
        return requestRecipeName(recipes, recipeCount);


    int id = getIdFromString(recipeName, recipes, recipeCount);

    if (id == -1)
        return requestRecipeName(recipes, recipeCount);
    else
        return id;

}

/**
 * Takes the name (string) of a recipe, and returns the recipe's index in the recipes array.
 */
int getIdFromString(char *recipeName, Recipe *recipes, int recipeCount){
    char recipeNameInLower[MAX_RECIPE_NAME];
    strcpy(recipeNameInLower, recipeName);
    toLowerCase(recipeNameInLower);

    for (int i = 0; i < recipeCount; i++){
        if (strcmp(recipes[i].name, recipeNameInLower) == 0){
            return i;
        }
    }
    return -1;
}

/**
 * Asks the user how many people they are making dinner for, and returns the value in an int.
 */
int requestAmountOfPeople(){
    int amountOfPeople = 0;
    printf("How many people are you cooking for (1─100)? ");
    int res = scanf(" %d", &amountOfPeople);

    flushInput();

    if (amountOfPeople <= 0 || amountOfPeople > 100 || res != 1){
        return requestAmountOfPeople();
    }
    return amountOfPeople;
}


void printListOfAlternativeRecipes(Recipe alternativeRecipes[]){

    int cellLengths[] = {3, 28, 10};
    const int numberOfCells = sizeof(cellLengths) / sizeof(cellLengths[0]);

    printf("\nHere are some alternative versions:\n");
    printLine("┌", "┬", "┐", numberOfCells, cellLengths);

    for(int r = 0; r < RECIPES_IN_ALTERNATIVES_LIST; r++){
        char name[MAX_RECIPE_NAME];
        strcpy(name, alternativeRecipes[0].name);
        capitaliseFirst(name);
        printf("│ %i │ %-26s │ %3d%% CO₂ │", r +1, name, -50);
        if(r < RECIPES_IN_ALTERNATIVES_LIST -1) printLine("├", "┼", "┤", numberOfCells, cellLengths);
    }

    printLine("└", "┴", "┘", numberOfCells, cellLengths);
    printf("\n");

}

/**
 * Ask the user which recipes number they want.
 * Returns the choice in an int pointer.
 */
int requestRecipeNumber(){
    int recipeNumber;

    bool inputSuccess = false;
    while(!inputSuccess){

        printf("Which version would you like to try making? ");
        const int inputs = scanf(" %d", &recipeNumber);

        inputSuccess = inputs == 1 && recipeNumber >= 1 && recipeNumber <= 5;

        if(!inputSuccess){
            printf("Sorry, I did not understand that. Please input a number between 1 and 5\n");
        }

        flushInput();
    }

    return recipeNumber -1;
}

/**
 * Prints information about a given recipe.
 */
void printRecipe(Recipe recipe, int people){
    /**
     * For mysterious reasons, the last digit of "cellLengths" becomes really big, and wrecks the system.
     * This issue is solved with a hack: add an extra item at the end of the array, and don't read it.
     */
    int cellLengths[] = {22, 14, 14, 0};
    const int numberOfCells = sizeof(cellLengths) / sizeof(cellLengths[0]) - 1;

    const int titleLength = 50;
    char title[titleLength];
    char name[MAX_RECIPE_NAME];
    strcpy(name, recipe.name);
    capitaliseFirst(name);
    padAround(name, title, titleLength);

    printf("\nHere you go:\n");
    printLine("┌", "─", "┐", numberOfCells, cellLengths);
    printf("│ %s │", title);
    printLine("├", "┬", "┤", numberOfCells, cellLengths);
    for (int i = 0; i < recipe.ingredientCount; i++){
        char ingredientName[MAX_INGREDIENT_NAME];
        strcpy(ingredientName, recipe.ingredients[i].name);
        capitaliseFirst(ingredientName);

        //TODO: print the correct g CO₂ number
        printf("│ %-20s │ %9.1lf(g) │ %5d(g CO₂) │", ingredientName, recipe.ingredients[i].amount * people , 25);
        if(i < recipe.ingredientCount - 1) printf("\n");

    }
    printLine("├", "┴", "┤", numberOfCells, cellLengths);

    //TODO: print the correct g CO₂ number
    printf("│ Amount of CO₂: %-35d │", 10);

    printLine("└", "─", "┘", numberOfCells, cellLengths);
    printf("\n");
}

/**
 * Takes a string and inserts it in the center of a wider string.
 * Useful when you want to center some text in a graphical output.
 */
void padAround(char string[], char centeredString[], int centeredStringLength){

    const int stringLength = strlen(string);
    const int frontPadding = floor((centeredStringLength - stringLength) / 2);

    for(int c = 0; c < centeredStringLength; c++) centeredString[c] = ' ';
    for(int c = 0; c < stringLength; c++) centeredString[c + frontPadding] = string[c];

}

/**
 * Prints a vertical table delimiter line.
 * Allows defining the number- and length of cells, along with which start, end, and delimiter characters should be used.
 */
void printLine(char start[], char delimiter[], char end[], int numberOfCells, int cellLengths[]){

    printf("\n%s", start);

    for(int c = 0; c < numberOfCells; c++){
        if(c != 0) printf("%s", delimiter);
        for(int l = 0; l < cellLengths[c]; l++) printf("─");
    }

    printf("%s\n", end);

}
