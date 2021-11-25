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


    printf("\nHere are some alternative versions:\n");

    for(int r = 0; r < RECIPES_IN_ALTERNATIVES_LIST; r++){
        char name[MAX_RECIPE_NAME];
        strcpy(name, alternativeRecipes[0].name);
        capitaliseFirst(name);
        printf("---------------------------------------------\n");
        printf("| %d | %-26s | %3d%% CO2 |\n", r +1, name, -50);

    }
    printf("---------------------------------------------\n");
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

void printRecipe(const Recipe *recipe, const int people){

    printf("\n\n");
    printf("------------------------------------------------------\n");
    char name[MAX_RECIPE_NAME];
    strcpy(name, recipe->name);
    capitaliseFirst(name);
    printf("|                       %-10s                   |\n", name);
    printf("|----------------------------------------------------|\n");
    for (int i = 0; i < recipe->ingredientCount; i++){
        //TODO: do the number
        printf("| %-20s | %9.1lf(g) | %5d(g CO₂) |\n", name, recipe->ingredients[i].amount*people , 25);

    }
    printf("|----------------------------------------------------|\n");
    //TODO: do the number
    printf("| Amount of CO2: %-10d                          |\n", 10);
    printf("------------------------------------------------------\n");
}
