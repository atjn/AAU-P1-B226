
#include <stdbool.h>

/**
 * @brief generates a list of alternative recipes with varying levels of improved Co2-reductions
 *
 * @param recipeIndex
 * @param recipes
 * @param alternativeRecipes - returns a list of alternative recipes
 * @param ingredients
 * @param ingrNum
 * @param categories
 * @param categoriesLength
 */
void makeListOfAlternativeRecipes(int recipeIndex, Recipe recipes[], Recipe alternativeRecipes[], IngredientData ingredients[], const int ingrNum, Category categories[], const int categoriesLength);

/**
 * @brief generates a list of alternative recipes with varying levels of improved Co2-reductions. This version is 100% accurate, but very slow. Only used for bench testing.
 *
 * @param recipeIndex
 * @param recipes
 * @param alternativeRecipes - returns a list of alternative recipes
 * @param ingredients
 * @param ingrNum
 * @param categories
 * @param categoriesLength
 */
void makeListOfAlternativeRecipes__UNOPTIMIZED(int recipeIndex, Recipe recipes[], Recipe alternativeRecipes[], IngredientData ingredients[], const int ingrNum, Category categories[], const int categoriesLength);
