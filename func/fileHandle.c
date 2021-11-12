#include "../lib/CuTest-AAU/CuTest.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "definition.h"

/* Using semicolons instead of commas (Thanks Microsoft) */
void readFile() {
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
        if (currLine > 0) {
            if (line[0] != ';') {
                currRecipeIndex++;
                tempIngredientCount = 0;

                strncpy(loadedRecipes[currRecipeIndex].recipeName, line, strlen(line) - 4);
                strcat(loadedRecipes[currRecipeIndex].recipeName, "\0");
            }
            else {
	            char *ingredientPtr = strtok(line, ingredientDelim);
                while(ingredientPtr != NULL) {
                    ingredientPtr[strcspn(ingredientPtr, "\n")] = 0;
                    if (tempIngredientInfoCount == 0) {
                        strncpy(loadedRecipes[currRecipeIndex].ingredients[tempIngredientCount].ingredientName, ingredientPtr, strlen(ingredientPtr));
                        tempIngredientInfoCount++;
                    }
                    else if (tempIngredientInfoCount == 1) {
                        loadedRecipes[currRecipeIndex].ingredients[tempIngredientCount].amount = (unsigned short) atoi(ingredientPtr);
                        tempIngredientInfoCount++;
                    }
                    else if (tempIngredientInfoCount == 2) {
                        loadedRecipes[currRecipeIndex].ingredients[tempIngredientCount].weight = (unsigned short) atoi(ingredientPtr);
                        loadedRecipes[currRecipeIndex].ingredientCount++;
                        tempIngredientInfoCount = 0;
                        tempIngredientCount++;
                    }

                    printf("%s\n", ingredientPtr);
		            ingredientPtr = strtok(NULL, ingredientDelim);
	            }
            }
        }
        currLine++;
    }

    /* For loop for checking input */
    /*
    for (int i = 0; i < 2; i++) {
        printf("%s\n", loadedRecipes[i].recipeName);
        printf("%d\n", loadedRecipes[i].ingredientCount);
        for (unsigned short j = 0; j < loadedRecipes[i].ingredientCount; j++) {
            printf("%s, %hu, %hu\n", loadedRecipes[i].ingredients[j].ingredientName,
                                     loadedRecipes[i].ingredients[j].amount,
                                     loadedRecipes[i].ingredients[j].weight);
        }
    }
    */

    /* Deallocating memory for the array and closing the file */
    free(loadedRecipes);
    fclose(fp);
}
