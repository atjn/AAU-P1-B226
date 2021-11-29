
/**
 * @brief This function reads the recipe file
 *
 * This function is used in the beginning of the foodForChange.c file to load the recipes file in the data folder
 * The function takes a pointer to an integer as a parameter. The parameter is used to return the number to recipes loaded
 * The function returns a pointer to the array of structs loaded
 * Using semicolons instead of commas in the .csv files (Thanks Microsoft)
 *
 * @param recipesNumber A pointer in which the length of the recipes array is returned
 * @return Recipe* An array of loaded recipes
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
 * @param dataPath Path to the ingredients.csv file
 * @param ingredients A pointer in which the loaded array of ingredients are returned
 * @param categories A pointer in which the loaded array of categories are returned
 * @param ingredientsLength A pointer in which the length of the ingredients array is returned
 * @param categoriesLength A pointer in which the length of the categories array is returned
 * @return void
 */
void readIngredients(const char *, IngredientData **, Category **, int *, int *);
