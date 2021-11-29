/**
 * @brief Lists loaded recipes
 * @param recipes Pointer to array of recipes
 * @param recipesCount Number of recipes
 *
 * @return void
 */
void listLoadedRecipes(Recipe *recipes, int recipeCount);

/**
 * @brief Asks the user for a recipe name
 * @param recipes Pointer to array of recipes
 * @param recipesCount Number of recipes in recepies pointer
 *
 * @return int Index of recipe in recipes array
 */
int requestRecipeName(Recipe* recipes, int recipeCount);

/**
 * @brief Asks the user how many people they are making dinner for
 *
 * @return int Amount of people
 */
int requestAmountOfPeople();

/**
 * @brief Prints the alternative recepies
 * @param recipes Pointer to array of recipes
 *
 * @return void
 */
void printListOfAlternativeRecipes(Recipe[]);

/**
 * @brief Prompts the user for a recipe number
 *
 * @return void
 */
int requestRecipeNumber();

/**
 * @brief Prints a recipe with its CO2 output in grams
 *
 * @param recipe Pointer to a recipe
 * @param people Amount of people who are eating
 * @param ingredients Pointer to the ingredient data for CO2 purposes
 * @param ingrNum Amount of total ingredients
 *
 * @return void
 */
void printRecipe(Recipe *recipe, const int people, IngredientData *ingredients, const int ingrNum);
