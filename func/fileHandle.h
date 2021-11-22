#include "../lib/CuTest-AAU/CuTest.h"

Recipe * readRecipe(int *recipesNumber);
IngredientData * readIngredients(int *ingredientCount);
Category * readCategories(int *categoryCount, IngredientData *ingredients);
CuSuite *readFileGetSuite();
