#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "func/definition.h"
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
    /* How to use the readFile funtion */

    int recipesNumber;
    Recipe *recipes = readRecipe(&recipesNumber);
    //printf("%d\n", recipesNumber);
    free(recipes);

    IngredientData **ingredients = 0;
    int ingredientsNumber;
    Category **categories = 0;
    int categoriesNumber;
    readIngredients(ingredients, &ingredientsNumber, categories, &categoriesNumber);
    free(categories);
    free(ingredients);

    /*
    //requestRecipeName();
    requestAmountOfPeople();
    makeListOfRecipes();
    printListOfRecipes();

    const int recipeNumber = requestRecipeNumber();
    printRecipe(recipeNumber);
    */
}
