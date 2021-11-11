#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "func/fileHandle.h"
#include "func/ui.h"
#include "func/algorithm.h"
#include "func/tests.h"

void foodForChange();

int main(int argc, char **argv){

    for (int a = 0; a < argc; a++){
        if(strcmp(argv[a], "-t") == 0 || strcmp(argv[a], "--test") == 0){
            printf("Running built-in unit tests:\n");
            const bool success = runAllTests();
            exit(success ? EXIT_SUCCESS : EXIT_FAILURE);
        }
    }

    foodForChange();

    exit(EXIT_SUCCESS);
}

void foodForChange(){
    int recipeNumber;

    readFile();
    requestRecipeName();
    requestAmountOfPeople();
    makeListOfRecipes();
    printListOfRecipes();
    requestRecipeNumber(&recipeNumber);
    printRecipe();

}
