#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "func/definitions.h"
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

    int recipesLength, ingredientsLength, categoriesLength;
    Recipe *recipes = readRecipe(&recipesLength);
    IngredientData *ingredients = NULL;
    Category *categories = NULL;
    readIngredients(INGREDIENT_DATA_LOCATION, &ingredients, &categories, &ingredientsLength, &categoriesLength);

    listLoadedRecipes(recipes, recipesLength);
    const int originalRecipeIndex = requestRecipeName(recipes, recipesLength);
    const int people = requestAmountOfPeople();

    Recipe alternativeRecipes[RECIPES_IN_ALTERNATIVES_LIST];
    makeListOfAlternativeRecipes(originalRecipeIndex, recipes, alternativeRecipes, ingredients, ingredientsLength);
    printListOfAlternativeRecipes(alternativeRecipes);
    const int alternativeRecipeIndex = requestRecipeNumber();

    printRecipe(&alternativeRecipes[alternativeRecipeIndex], people, ingredients, ingredientsLength);

    free(recipes);
    free(ingredients);
    free(categories);

}
