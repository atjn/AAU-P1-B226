/**
 * @brief Flushes the input buffer.
 *
 * This is useful when taking input from the user with `scanf`,
 * because unreadable input might be left in the buffer, causing an infinite loop.
 *
 * @param void
 * @return void
 */
void flushInput();


/**
 * @brief Capitalises the first character of a string.
 *
 * @param char* String of which first character will be uppercase.
 * @return void
 */
void capitaliseFirst(char*);

/**
 * @brief Takes the letters in a char array and makes them all lower case.
 *
 * @param char* String of which all characters will be lowercase.
 * @return void
 */
void toLowerCase(char*);
int factorial(const int);

/**
 * @brief A function to get the index of a speciic category
 *
 * This function is used to get the index of the category with categoryName in the array categories.
 * Takes the name (string) of a category, and returns it's index in the array of categories.
 * If no match is found, returns -1.
 *
 * @param categoryName
 * @param categories
 * @param categoriesLength
 * @return int
 */
int getCategoryIndex(const char *, const Category *, const int);
float calculateRecipeCoo(Recipe *, IngredientData *, int);
float getIngrCoo(Ingredient *, IngredientData *, int);
