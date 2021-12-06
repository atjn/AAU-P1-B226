
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
 * @param optimize - should the algorithm be 100% accurate towards its given targets, or should it optimize for speed, and allow a certain level of inaccuracy
 */
void makeListOfAlternativeRecipes(int recipeIndex, Recipe recipes[], Recipe alternativeRecipes[], IngredientData ingredients[], const int ingrNum, Category categories[], const int categoriesLength, const bool optimize);
