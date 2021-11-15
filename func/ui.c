#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../lib/CuTest-AAU/CuTest.h"

#include "./definition.h"
#include "./ui.h"
#include "./utilities.h"



//This function is a utility only used inside this file.
//This function takes the letters in a char array and makes it lower case.
void toLowerCase(char* string){

    for(int i = 0; string[i]; i++){
        string[i] = tolower(string[i]);
    }
}


//This function is a utility only used inside this file.
//This function gets the index of a recipe in the recipes array.
int getIdFromString(char *recipeName, Recipe* recipes, int recipeCount){
    toLowerCase(recipeName);

    for (int i = 0; i < recipeCount; i++){
        if (recipes[i].name == recipeName){
            return i;
        }
    }
    return -1;
}


//This function ask the user for a recipe name. If it cannot match the user input to a recipe, it will return itself, and thus start the process again.
//It returns an `int` corresponding the index of the recipe in the recipes array.
int requestRecipeName(Recipe* recipes, int recipeCount){
    char* recipeName = "";

    printf("What recipe do you want to eat?");
    const int inputs = scanf("%c", recipeName);

    flushInput();

    if (inputs <= 0)
        return requestRecipeName(recipes, recipeCount);


    int id = getIdFromString(recipeName, recipes, recipeCount);

    if (id == -1)
        return requestRecipeName(recipes, recipeCount);
    else
        return id;

}


int requestAmountOfPeople(){
    int amountOfPeople = 0;
    printf("How many people are you cooking for (1-100)?");
    int res = scanf("%d", &amountOfPeople);

    flushInput();

    if (amountOfPeople <= 0 || amountOfPeople > 100 || res != 1){
        return requestAmountOfPeople();
    }
    return amountOfPeople;
}


void printListOfRecipes(){

}

/**
 * Ask the user which recipes number they want.
 * Returns the choice in an int pointer.
 */
int requestRecipeNumber(){
    int recipeNumber;

    bool inputSuccess = false;
    while(!inputSuccess){

        printf("Which version did you want? > ");
        const int inputs = scanf(" %d", &recipeNumber);

        inputSuccess = inputs == 1 && recipeNumber >= 1 && recipeNumber <= 5;

        if(!inputSuccess){
            printf("Sorry, I did not understand that. Please input a number between 1 and 5\n");
        }

        flushInput();
    }

    return recipeNumber;
}

void printRecipe(int recipeNumber){
    printf(" %d", recipeNumber);
}
