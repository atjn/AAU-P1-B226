#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "func/definition.h"
#include "func/fileHandle.h"
#include "func/ui.h"
#include "func/algorithm.h"
#include "tests.h"

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

    /*
    int recipesNumber;
    Recipe *recipes = readRecipe(&recipesNumber);
    */
    //printf("Loaded recipes: %d\n", recipesNumber);

    int ingredientsNumber;
    int categoriesNumber;
    IngredientData *ingredients = readIngredients(&ingredientsNumber);
    Category *categories = readCategories(&categoriesNumber, ingredients);

    printf("%s\n", ingredients[3].name);
    printf("%s\n", categories[3].categoryName);

    //free(categories);
    //free(ingredients);
    /*
    const int people = requestAmountOfPeople();

    makeListOfRecipes();
    //const int recipeNumber = requestRecipeNumber();
    printListOfRecipes();

    const int recipeIndex = requestRecipeName(recipes, recipesNumber);
    printRecipe(recipes[recipeIndex], people);

    free(recipes);
    */
}
