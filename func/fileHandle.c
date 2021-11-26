#include "../lib/CuTest-AAU/CuTest.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "definitions.h"


/* Functions */
int getCategoryIndex(const char *, const Category *, const int);
void sanitize(char*);

/* This function is used in the beginning of the foodForChange.c file to load the recipes file in the data folder */
/* The function takes a pointer to an integer as a parameter. The parameter is used to return the number to recipes loaded */
/* The function returns a pointer to the array of structs loaded */
/* Using semicolons instead of commas in the .csv files (Thanks Microsoft) */
Recipe * readRecipe(int *recipesNumber) {
    /* Tempoary variabls for reading the recipe file */
    FILE *fp;
    char line[60];
    int len = 60;
    char ingredientDelim[] = ";";

    /* Other variables */
    int recipesNum = -1;
    Recipe *loadedRecipes;

    /* Opening the recipes file */
    fp = fopen(RECIPES_LOCATION, "r");
    if (fp == NULL) exit(EXIT_FAILURE);

    /* Reading the file to get the number of recipes */
    while (fgets(line, len, fp) != NULL) {
        if (line[0] != ';') {
            recipesNum++;
        }
    }

    /* Allocating memory for the loaded recipes array */
    loadedRecipes = malloc(recipesNum * sizeof(Recipe));

    int currRecipeIndex = -1;
    int currLine = 0;
    int tempIngredientCount = 0;
    int tempIngredientInfoCount = 0;

    /* Rewinding the file to start reading it again */
    rewind(fp);

    /* Reading the file to get the number of recipes */
    while (fgets(line, len, fp) != NULL) {
        /* Skipping the first line containing CSV metadata */
        if (currLine == 0) {
            currLine++;
            continue;
        }

        /* Checking if line starts with semicolon, if so its an ingredient and the if statement does not run */
        if (line[0] != ';') {
            currRecipeIndex++;
            tempIngredientCount = 0;


            /* Replacing the first ";" with an '\0' character to make the snprintf function work the same on Linux, macOS and Windows */
            for (int i = 0; i < (int) strlen(line); i++) {
                if (line[i] == ';') {
                    line[i] = '\0';
                    break;
                }
            }

            /* Copies the recipe name into the given structs recipeName variable */
            snprintf(loadedRecipes[currRecipeIndex].name, strlen(line) + 1, "%s", line);
            strcat(loadedRecipes[currRecipeIndex].name, "\0");
        }
        else {
            /* Splits the line variable every time we encounter a semicolon */
            char *ingredientPtr = strtok(line, ingredientDelim);
            while(ingredientPtr != NULL) {
                ingredientPtr[strcspn(ingredientPtr, "\n")] = 0;
                /* Stores the ingredient name for the given ingredient */
                if (tempIngredientInfoCount == 0) {
                    strcpy(loadedRecipes[currRecipeIndex].ingredients[tempIngredientCount].name, ingredientPtr);
                    tempIngredientInfoCount++;
                }
                /* Stores the amount (Grams) for the given ingredient */
                else if (tempIngredientInfoCount == 1) {
                    loadedRecipes[currRecipeIndex].ingredients[tempIngredientCount].amount = atof(ingredientPtr);
                    tempIngredientInfoCount++;
                }
                /* Stores the weight for the given ingredient */
                else if (tempIngredientInfoCount == 2) {
                    loadedRecipes[currRecipeIndex].ingredients[tempIngredientCount].weight = (unsigned short) atoi(ingredientPtr);
                    loadedRecipes[currRecipeIndex].ingredientCount++;
                    tempIngredientInfoCount = 0;
                    tempIngredientCount++;
                }
                ingredientPtr = strtok(NULL, ingredientDelim);
            }
        }
        currLine++;
    }

    /* For loop for checking input */
   /* for (int i = 0; i < 1; i++) {
        printf("%s\n", loadedRecipes[i].name);
        printf("%d\n", loadedRecipes[i].ingredientCount);
        for (unsigned short j = 0; j < loadedRecipes[i].ingredientCount; j++) {
            printf("%s, %f, %hu\n", loadedRecipes[i].ingredients[j].name,
                                     loadedRecipes[i].ingredients[j].amount,
                                     loadedRecipes[i].ingredients[j].weight);
        }
    }
    */

    /* Closing the file */
    fclose(fp);

    *recipesNumber = recipesNum;
    return loadedRecipes;
}

void readIngredients(const char *dataPath, IngredientData **ingredients, Category **categories, int *ingredientsLength, int *categoriesLength){

    // Open the ingredients data file
    FILE *rawFile = fopen(dataPath, "r");
    assert(rawFile != NULL);
    char rawFileLine[MAX_FILE_LINE_LENGTH];

    // Count the total number of ingredients and allocate memory accordingly
    *ingredientsLength = -1;
    while(fgets(rawFileLine, MAX_FILE_LINE_LENGTH, rawFile) != NULL){
        *ingredientsLength += 1;
        assert(*ingredientsLength <= MAX_INGREDIENTS);
    }
    rewind(rawFile);
    *ingredients = (IngredientData *) malloc(*ingredientsLength * sizeof(IngredientData));

    // Memory for categories is allocated dynamically as they are discovered
    *categoriesLength = 0;

    // Loop over every line in the file
    int lineIndex = -1;
    while (fgets(rawFileLine, MAX_FILE_LINE_LENGTH, rawFile) != NULL) {
        lineIndex++;
        const int ingredientIndex = lineIndex -1;

        // Skip the first line (it only contains CSV metadata)
        if(lineIndex == 0) continue;

        sanitize(rawFileLine);

        // Loop over every cell in the line
        int cellIndex = -1;
        char *cellContents = strtok(rawFileLine, FILE_CELL_DELIMITER);
        while(cellContents != NULL) {
            cellIndex++;

            switch(cellIndex){
                // Store the ingredient name
                case 0: {
                    assert(strlen(cellContents) < MAX_INGREDIENT_NAME);
                    strcpy((*ingredients)[ingredientIndex].name, cellContents);
                    break;
                }
                // Store the ingredient CO₂ footprint
                case 1: {
                    const double coo = atof(cellContents);
                    assert(coo > 0 || strcmp(cellContents, "0") == 0 || strcmp(cellContents, "0.0") == 0);
                    (*ingredients)[ingredientIndex].coo = coo;
                    break;
                }
                // Store the ingredient in the correct category lists
                case 2: {
                    // Loop over every category associated with this ingredient
                    char *categoryName = strtok(cellContents, FILE_CATEGORY_DELIMITER);
                    while (categoryName != NULL) {

                        // Get the index of the category.
                        int categoryIndex = getCategoryIndex(categoryName, *categories, *categoriesLength);

                        // If the category doesn't exist, create it.
                        if(categoryIndex == -1){
                            *categoriesLength += 1;
                            assert(*categoriesLength <= MAX_CATEGORIES);
                            categoryIndex = *categoriesLength -1;
                            *categories = (Category *) realloc(*categories, *categoriesLength * sizeof(Category));
                            assert(strlen(categoryName) < MAX_CATEGORY_NAME);
                            strcpy((*categories)[categoryIndex].name, categoryName);
                            (*categories)[categoryIndex].ingredientCount = 0;
                        }

                        // Add data about the ingredient to the category.
                        (*categories)[categoryIndex].ingredientCount++;
                        assert((*categories)[categoryIndex].ingredientCount <= MAX_INGREDIENTS_CATEGORY);
                        (*categories)[categoryIndex].ingredientData[(*categories)[categoryIndex].ingredientCount-1] = &(*ingredients)[ingredientIndex];

                        // Fetch the next category
                        categoryName = strtok(NULL, FILE_CATEGORY_DELIMITER);
                    }
                    break;
                }

            }
            // Fetch the next cell
            cellContents = strtok(NULL, FILE_CELL_DELIMITER);
        }

    }

    // Close the file
    fclose(rawFile);
}


void testReadIngredients(CuTest* tc){

    IngredientData correctIngredients[] = {
        {"very balanced raddish", 1},
        {"beef from the future", 0},
        {"5 carrots", 0.37},
        {"pea drink", 0.48},
        {"beef beef buffalo", 80.89},
        {"truffles", 30},
    };
    const int correctIngredientsLength = sizeof(correctIngredients) / sizeof(correctIngredients[0]);

    const Category correctCategories[] = {
        {
            "rabbitFood",
            {
                &correctIngredients[0],
                &correctIngredients[2],
                &correctIngredients[3],
            },
            3,
        },
        {
            "goodStuff",
            {
                &correctIngredients[1],
                &correctIngredients[4],
            },
            2,
        },
        {
            "veryIncrediblyCrazyMonumentallyLongCategoryName",
            { &correctIngredients[3], },
            1,
        },
        {
            "category 3",
            { &correctIngredients[3], },
            1,
        },
        {
            "rich people things",
            { &correctIngredients[5], },
            1,
        },
    };
    const int correctCategoriesLength = sizeof(correctCategories) / sizeof(correctCategories[0]);

    int ingredientsLength, categoriesLength;
    IngredientData *ingredients = NULL;
    Category *categories = NULL;
    readIngredients("fixtures/ingredients.csv", &ingredients, &categories, &ingredientsLength, &categoriesLength);

    CuAssertPtrNotNull(tc, ingredients);
    CuAssertPtrNotNull(tc, categories);

    CuAssertIntEquals(tc, correctIngredientsLength, ingredientsLength);

    for(int i = 0; i < correctIngredientsLength; i++){
        CuAssertStrEquals(tc, correctIngredients[i].name, ingredients[i].name);
        CuAssertDblEquals(tc, correctIngredients[i].coo, ingredients[i].coo, 0);
    }

    CuAssertIntEquals(tc, correctCategoriesLength, categoriesLength);

    for(int c = 0; c < correctCategoriesLength; c++){
        CuAssertStrEquals(tc, correctCategories[c].name, categories[c].name);
        CuAssertDblEquals(tc, correctCategories[c].ingredientCount, categories[c].ingredientCount, 0);
        for(int i = 0; i < correctCategories[c].ingredientCount; i++){
            CuAssertStrEquals(tc, correctCategories[c].ingredientData[i]->name, categories[c].ingredientData[i]->name);
        }
    }

    free(ingredients);
    free(categories);
}

/**
 * Takes the name (string) of a category, and returns it index in the array of categories.
 * If no match is found, returns -1.
 */
int getCategoryIndex(const char *categoryName, const Category *categories, const int categoriesLength) {

    for (int i = 0; i < categoriesLength; i++){
        if (strcmp(categoryName, categories[i].name) == 0) {
            return i;
        }
    }

    return -1;
}

void testGetCategoryIndex(CuTest* tc){

    const Category categories[] = {
        {
            "cowsFarts",
            {NULL},1,
        },
        {
            "cows",
            {NULL},1,
        },
        {
            "based beans",
            {NULL},1,
        },
        {
            "3 acres of 5",
            {NULL},1,
        },
    };
    const int categoriesLength = sizeof(categories) / sizeof(categories[0]);

    CuAssertIntEquals(tc, 0, getCategoryIndex("cowsFarts", categories, categoriesLength));
    CuAssertIntEquals(tc, 1, getCategoryIndex("cows", categories, categoriesLength));
    CuAssertIntEquals(tc, -1, getCategoryIndex("cow", categories, categoriesLength));

    CuAssertIntEquals(tc, 2, getCategoryIndex("based beans", categories, categoriesLength));
    CuAssertIntEquals(tc, 3, getCategoryIndex("3 acres of 5", categories, categoriesLength));

    CuAssertIntEquals(tc, -1, getCategoryIndex("3", categories, categoriesLength));
    CuAssertIntEquals(tc, -1, getCategoryIndex("5", categories, categoriesLength));
    CuAssertIntEquals(tc, -1, getCategoryIndex("s", categories, categoriesLength));
    CuAssertIntEquals(tc, -1, getCategoryIndex(" ", categories, categoriesLength));
    CuAssertIntEquals(tc, -1, getCategoryIndex("", categories, categoriesLength));

}

/**
 * This function removes characters that some systems cant handle.
 * The function takes a string and makes the changes directly on the string.
 */
void sanitize(char* string){

    // Remove the newline at the end of the string, otherwise it could for example be interpreted as a delimiter for an extra category
    string[strcspn(string, "\n")] = '\0';

    // If we have a char 13 in the string, make it a end of string character.
    // This is a problem on Windows when using WSL.
    int i = 0;
    while(string[i] != '\0'){
        if (string[i] == (char) 13) string[i] = '\0';
        i++;
    }
}
