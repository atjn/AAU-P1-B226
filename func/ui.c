#include "../lib/CuTest-AAU/CuTest.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void requestRecipeName(){

}

void requestAmountOfPeople(){

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

        // Flush the input buffer, otherwise scanf will read the previous answer, and create an infinite loop
        int c; while((c = getchar()) != '\n' && c != EOF);
    }

    return recipeNumber;
}

void printRecipe(int recipeNumber){
    printf(" %d", recipeNumber);
}
