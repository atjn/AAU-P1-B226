#include "../lib/CuTest-AAU/CuTest.h"

int requestRecipeName(Recipe* recipes, int recipeCount);
int requestAmountOfPeople();
void printListOfRecipes();
int requestRecipeNumber();
void printRecipe(Recipe);
CuSuite *requestRecipeNameGetSuite();
CuSuite *requestAmountOfPeopleGetSuite();
CuSuite *printListOfRecipesGetSuite();
CuSuite *requestRecipeNumberGetSuite();
CuSuite *printRecipeGetSuite();

