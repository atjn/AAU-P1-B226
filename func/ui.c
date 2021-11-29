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
#include "./algorithm.h"

int getIdFromString(char *, Recipe *, int);


void listLoadedRecipes(Recipe *recipes, int recipeCount){
    char printList;

    // Asking the user whether a list of the loaded recipes should be printed?
    printf("Would you like a list of recipes? (Y/N)\n");
    const int inputs = scanf(" %c", &printList);

    flushInput();

    if (inputs == 1 && (printList == 'y' || printList == 'Y')) {
        printf("\nThe loaded recipes are: \n");
        for (int i = 0; i < recipeCount; i++) {
            printf("\t - %s\n", recipes[i].name);
        }
    }
}

//This function ask the user for a recipe name. If it cannot match the user input to a recipe, it will return itself, and thus start the process again.
//It returns an `int` corresponding the index of the recipe in the recipes array.
int requestRecipeName(Recipe *recipes, int recipeCount){
    char recipeName[MAX_RECIPE_NAME];

    printf("\nWhat recipe do you want to make? ");
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
 * @brief gets the id of a recipe
 * @param recipeName name of the recipe
 * @param recipes pointer to array of recipes
 * @param recipesCount number of recipes in recepies pointer
 *
 * @return int id of the recipe in the array recepies
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
 * @brief asks the user how many people they are making dinner for
 *
 * @return int amount of people
 */
int requestAmountOfPeople(){
    int amountOfPeople = 0;
    printf("\nHow many people are you cooking for (1-100)? ");
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

        if(r == 0){
            printf("---------------------------------------------\n");
        }else{
            printf("|-------------------------------------------|\n");
        }
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

        inputSuccess = inputs == 1 && recipeNumber >= 1 && recipeNumber <= RECIPES_IN_ALTERNATIVES_LIST;

        if(!inputSuccess){
            printf("Sorry, I did not understand that. Please input a number between 1 and %d\n", RECIPES_IN_ALTERNATIVES_LIST);
        }

        flushInput();
    }

    return recipeNumber -1;
}

/**
 * Prints information about a given recipe.
 */
void printRecipe(Recipe *recipe, const int people, IngredientData *ingredients, const int ingrNum){

    char name[MAX_RECIPE_NAME];
    strcpy(name, recipe->name);
    capitaliseFirst(name);

    printf("\nHere you go:\n");
    printf("------------------------------------------------------\n");
    printf("|                       %-10s                   |\n", name);
    printf("|----------------------------------------------------|\n");
    printf("|      Ingredient      |  Amount (g)  |    CO2 (g)   |\n");
    printf("|----------------------------------------------------|\n");
    for (int i = 0; i < recipe->ingredientCount; i++){
        char ingredientName[MAX_INGREDIENT_NAME];
        strcpy(ingredientName, recipe->ingredients[i].name);
        capitaliseFirst(ingredientName);
        printf("| %-20s | %12.1lf | %12.1lf |\n", ingredientName, recipe->ingredients[i].amount * people,
                                                        (getIngrCoo(&recipe->ingredients[i], ingredients, ingrNum)) * recipe->ingredients[i].amount * people);
    }
    printf("|----------------------------------------------------|\n");
    printf("| Amount of CO2 (kg): %-10.1lf                     |\n", calculateRecipeCoo(recipe, ingredients, ingrNum) * people);
    printf("------------------------------------------------------\n");
}
