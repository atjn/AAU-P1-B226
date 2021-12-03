
#include <stdbool.h>

void makeListOfAlternativeRecipes(int recipeIndex, Recipe recipes[], Recipe alternativeRecipes[], IngredientData ingredients[], const int ingrNum, Category categories[], const int categoriesLength, const bool optimize);
float calculateRecipeCoo(Recipe *recipe, IngredientData *ingredients, int ingrNum);
float getIngrCoo(Ingredient *ingredient, IngredientData *ingredients, int ingrNum);
