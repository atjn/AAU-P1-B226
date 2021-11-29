
/**
 * @brief This function reads the recipe file
 *
 * This function is used in the beginning of the foodForChange.c file to load the recipes file in the data folder
 * The function takes a pointer to an integer as a parameter. The parameter is used to return the number to recipes loaded
 * The function returns a pointer to the array of structs loaded
 * Using semicolons instead of commas in the .csv files (Thanks Microsoft)
 *
 * @param recipesNumber Number of recipes
 * @return Recipe*
 */
Recipe * readRecipe(int *recipesNumber);

/**
 * @brief This function reads the ingredientsdata file
 *
 * This function is used in the beginning of the foodForChange.c file to load the ingredients file in the data folder
 * The function takes a pointer to the path of the data file as a parameter.
 * The function also takes a pointer to an array of IngredientsData and an array of Category. These parameters are used to return the loaded ingredients and categories.
 * The function also takes a pointer to the integers ingredientsLength and categoriesLength. These parameters are used to return the length of the two arrays.
 *
 * @param dataPath Path to data
 * @param ingredients Ingredients of recipe
 * @param categories Categories of recipe
 * @param ingredientsLength Amount of ingredients of recipe
 * @param categoriesLength Amount of categories of recipe
 * @return void
 */
void readIngredients(const char *, IngredientData **, Category **, int *, int *);
