#include "../lib/CuTest-AAU/CuTest.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "definitions.h"

/* Including gnu strtok revised function */
#include "../lib/GNU-Func/strtok_gnu.h"

/* Functions */
int categoryExist(char categoryName[], Category *categoryArray, int categoryLength);


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

            /* Copies the recipe name into the given structs recipeName variable */
            snprintf(loadedRecipes[currRecipeIndex].name, strlen(line) - 3, "%s", line);
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
        printf("%s\n", loadedRecipes[i].recipeName);
        printf("%d\n", loadedRecipes[i].ingredientCount);
        for (unsigned short j = 0; j < loadedRecipes[i].ingredientCount; j++) {
            printf("%s, %f, %hu\n", loadedRecipes[i].ingredients[j].ingredientName,
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

IngredientCategory readIngredients() {
    FILE *fp;
    char line[128];
    int len = 128;
    char ingredientDelim[] = ";";
    char categoryDelim[] = ".";

    /* Other variables */
    int ingredientNum = -1;
    int categoryNum = 0;

    IngredientCategory ingrCatData;
    ingrCatData.ingredientsCount = 0;

    /* Opening the recipes file */
    fp = fopen(INGREDIENT_DATA_LOCATION, "r");
    if (fp == NULL) exit(EXIT_FAILURE);

    /* Reading the file to get the number of recipes */
    while (fgets(line, len, fp) != NULL) {
        ingredientNum++;
    }

    /* Setting the ingredientsCount variable */
    ingrCatData.ingredientsCount = ingredientNum;

    /* Rewinding the file to start reading it again */
    rewind(fp);

    int tempIngredientInfoCount = 0;
    int currLine = 0;

    /* Reading the file to get the number of recipes */
    while (fgets(line, len, fp) != NULL) {
        /* Skipping the first line containing CSV metadata */
        if (currLine == 0) {
            currLine++;
            continue;
        }

        /* Splits the line variable every time we encounter a semicolon */
        char *ingredientPtr = strtok(line, ingredientDelim);
        while(ingredientPtr != NULL) {
            ingredientPtr[strcspn(ingredientPtr, "\n")] = 0;
            /* Stores the ingredient name for the given ingredient */
            if (tempIngredientInfoCount == 0) {
                strcpy(ingrCatData.ingredients[currLine - 1].name, ingredientPtr);
                tempIngredientInfoCount++;
            }
            /* Stores the amount (Grams) for the given ingredient */
            else if (tempIngredientInfoCount == 1) {
                ingrCatData.ingredients[currLine - 1].coo = atof(ingredientPtr);
                tempIngredientInfoCount++;
            }
            /* Stores the weight for the given ingredient */
            else if (tempIngredientInfoCount == 2) {
                /* Temporary varables */
                char *rest = NULL;
                char *categoryPtr;

                categoryPtr = strtok_gnu(ingredientPtr, categoryDelim, &rest);

                /* While loop for checking and indexing the categories */
                while (categoryPtr != NULL) {
                    categoryPtr[strcspn(categoryPtr, "\n")] = 0;

                    /* INSERT EXPLANATION HERE LOL XD GAMING GAMERS */
                    for (int i = 0; i < (int) strlen(categoryPtr); i++) {
                        if (categoryPtr[i] == 13) {
                            categoryPtr[i] = '\0';
                        }
                    }

                    /* Checking whether the category exists */
                    int categoryIndex = 0;
                    if (categoryNum != 0) {
                        categoryIndex = categoryExist(categoryPtr, ingrCatData.categories, categoryNum);
                    }
                    else {
                        categoryIndex = 0;
                    }

                    /* Adding data to the indvidual arrays. If-statement for setting up a new category if nessesary */
                    /* TODO Change the structure of the structs as we are atoring the same data multiple times whih is a big waste of memory */
                    if (categoryIndex != 0) {
                        ingrCatData.categories[categoryIndex].ingredientCount += 1;
                        ingrCatData.categories[categoryIndex].ingredientData[ingrCatData.categories[categoryIndex].ingredientCount] = &ingrCatData.ingredients[currLine - 1];
                    }
                    else {
                        categoryNum++;
                        strcpy(ingrCatData.categories[categoryNum - 1].categoryName, categoryPtr);
                        ingrCatData.categories[categoryNum - 1].ingredientCount = 1;
                        ingrCatData.categories[categoryNum - 1].ingredientData[0] = &ingrCatData.ingredients[currLine - 1];
                        //strcpy(loadedCategories[categoryNum - 1].ingredientData[0].ingredientName, loadedIngredients[currLine - 1].ingredientName);
                        //loadedCategories[categoryNum - 1].ingredientData[0].coo = loadedIngredients[currLine - 1].coo;
                    }

                    /* Fetching the next part of the string */
                    categoryPtr = strtok_gnu(NULL, categoryDelim, &rest);
                }
                tempIngredientInfoCount = 0;
            }
            ingredientPtr = strtok(NULL, ingredientDelim);
        }
        currLine++;
    }

    ingrCatData.categoriesCount = categoryNum;
    /* Closing the file */
    fclose(fp);

    return ingrCatData;
}

/* A function that checks if the category has already been made and allocated */
int categoryExist(char categoryName[], Category *categoryArray, int categories) {
    for (int i = 0; i < categories; i++){
        //printf("%s %s %s\n", categoryName, (strcmp(categoryName, categoryArray[i].categoryName) == 0) ? "is the same as" : "is not the same as", categoryArray[i].categoryName);
        if (strcmp(categoryName, categoryArray[i].categoryName) == 0) {
            return i;
        }
    }
    return 0;
}
