#include "../lib/CuTest-AAU/CuTest.h"
#include "./definition.h"

int requestRecipeName(Recipe* recipes, int recipeCount);
int getIdFromString(char* recipeName, Recipe* recipes, int recipeCount);
void requestAmountOfPeople();
void printListOfRecipes();
void requestRecipeNumber();
void printRecipe();
CuSuite *requestRecipeNameGetSuite();
CuSuite *requestAmountOfPeopleGetSuite();
CuSuite *printListOfRecipesGetSuite();
CuSuite *requestRecipeNumberGetSuite();
CuSuite *printRecipeGetSuite();

