/**
 * @brief lists loaded recipes
 * @param recipes pointer to array of recipes
 * @param recipesCount number of recipes
 *
 * @return void
 */
void listLoadedRecipes(Recipe *recipes, int recipeCount);

/**
 * @brief asks the user for a recipe name
 * @param recipes pointer to array of recipes
 * @param recipesCount number of recipes in recepies pointer
 *
 * @return int index of recipe in recipes array
 */
int requestRecipeName(Recipe* recipes, int recipeCount);

/**
 * @brief asks the user how many people they are making dinner for
 *
 * @return int amount of people
 */
int requestAmountOfPeople();

/**
 * @brief prints the alternative recepies
 * @param recipes pointer to array of recipes
 *
 * @return void
 */
void printListOfAlternativeRecipes(Recipe[]);

/**
 * @brief prompts the user for a recipe number
 *
 * @return void
 */
int requestRecipeNumber();

/**
 * @brief prints a recipe with its co2 output in grams
 *
 * @param recipe a pointer to a recipe
 * @param people amount of people who are eating
 * @param ingredients pointer to the ingredient data for co2 purposes
 * @param ingrNum amount of total ingredients
 *
 * @return void
 */
void printRecipe(Recipe *recipe, const int people, IngredientData *ingredients, const int ingrNum);
