#include "../lib/CuTest-AAU/CuTest.h"
#include "./definition.h"

int requestRecipeName(Recipe* recipes, int recipeCount);
void requestAmountOfPeople();
void printListOfRecipes();
int requestRecipeNumber();
void printRecipe(int);
CuSuite *requestRecipeNameGetSuite();
CuSuite *requestAmountOfPeopleGetSuite();
CuSuite *printListOfRecipesGetSuite();
CuSuite *requestRecipeNumberGetSuite();
CuSuite *printRecipeGetSuite();

