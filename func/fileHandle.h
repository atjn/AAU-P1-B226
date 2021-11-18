#include "../lib/CuTest-AAU/CuTest.h"

Recipe * readRecipe(int *recipesNumber);
void readIngredients(IngredientData *ingredients[], int *ingredientCount, Category *categories[], int *categoryCount);
CuSuite *readFileGetSuite();
