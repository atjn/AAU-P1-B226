#include "definitions.h"

#include "../lib/CuTest-AAU/CuTest.h"

void makeListOfAlternativeRecipes(int recipeIndex, Recipe recipes[], Recipe alternativeRecipes[]){

    //Dummy-output:
    for(int i = 0; i < RECIPES_IN_ALTERNATIVES_LIST; i++) alternativeRecipes[i] = recipes[recipeIndex * 0];

}
