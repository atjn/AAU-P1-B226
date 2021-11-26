#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/CuTest-AAU/CuTest.h"

float calculateCoo(Recipe recipe, IngredientData *ingredients, int ingrNum);

// Function to calculate and return alternative recipes
// The function takes the recipe, recipelist, and the parameter alternativeRecipes
// in with the alternative recipes will be returned. The func also takes the ingredient list and its length.
void makeListOfAlternativeRecipes(int recipeIndex, Recipe recipes[], Recipe alternativeRecipes[], IngredientData ingredients[], const int ingrNum){
    //Dummy-output:
    for(int i = 0; i < RECIPES_IN_ALTERNATIVES_LIST; i++) alternativeRecipes[i] = recipes[recipeIndex * 0];

    float recipeCoo = calculateCoo(recipes[recipeIndex], ingredients, ingrNum);

    printf("\nThis recipe of a %s has a carbon footprint of: %.2f Kg/CO₂ pr. person\n", recipes[recipeIndex].name, recipeCoo);

}

// Calculating the total COO emission of a given recipe
// TODO: change the structure of the Ingredient struct to include
// a pointer to the corresponding IngredientData struct
float calculateCoo(Recipe recipe, IngredientData *ingredients, int ingrNum) {
    float tempCOO = 0;
    for (int i = 0; i < recipe.ingredientCount; i++) {
        for (int j = 0; j < ingrNum; j++) {
            if (strcmp(recipe.ingredients[i].name, ingredients[j].name) == 0) {
                tempCOO += ingredients[j].coo * (recipe.ingredients[i].amount/1000);
                break;
            }
        }
    }
    return tempCOO;
}
