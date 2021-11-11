#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>


#include "../lib/CuTest-AAU/CuTest.h"
#include "./ui.h"

void toLowerCase(char* recipeName){

    for(int i = 0; recipeName[i]; i++){
        recipeName[i] = tolower(recipeName[i]);
    }
}

int requestRecipeName(Recipe* recipes, int recipeCount){
    char* recipeName = "";

    printf("What recipe do you want to eat?");
    const int inputs = scanf("%c", recipeName);

    // Flush the input buffer, otherwise scanf will read the previous answer, and create an infinite loop
    int c; while((c = getchar()) != '\n' && c != EOF);

    if (inputs <= 0)
        return requestRecipeName(recipes, recipeCount);


    int id = getIdFromString(recipeName, recipes, recipeCount);

    if (id == -1)
        return requestRecipeName(recipes, recipeCount);
    else
        return id;

}


int getIdFromString(char *recipeName, Recipe* recipes, int recipeCount){
    toLowerCase(recipeName);

    for (int i = 0; i < recipeCount; i++){
        if (recipes[i].recipeName == recipeName){
            return i;
        }
    }
    return -1;
}





void requestAmountOfPeople(){

}

void printListOfRecipes(){

}

void requestRecipeNumber(){

}

void printRecipe(){

}
