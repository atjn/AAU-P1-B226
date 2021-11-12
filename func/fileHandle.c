#include "../lib/CuTest-AAU/CuTest.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "definition.h"

#define RECIPES_LOCATION "data/recipes.csv"

/* Using semicolons instead of commas (Thanks Microsoft) */
void readFile() {
    /* Tempoary variabls for reading the recipe file */
    FILE *fp;
    char line[60];
    int len = 60;
    //char ingredientDelim[] = ";";

    /* Other variables */
    int recipesNum = -1;
    //Recipe *loadedRecipes;

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
    /*
    loadedRecipes = malloc(recipesNum * sizeof(Recipe));

    int currRecipeIndex = -1;
    int currLine = 0;
    int tempIngredientCount = 0;
    */
    /* Rewinding the file to start reading it again */
    rewind(fp);

    /* Reading the file to get the number of recipes */
    /*while ((read = getline(&line, &len, fp)) != (unsigned long) -1) {
        if (currLine > 0) {
            if (line[0] != ';') {
                currRecipeIndex++;
                tempIngredientCount = 0;

                strncpy(loadedRecipes[currRecipeIndex].recipeName, line, read - 4);
                strcat(loadedRecipes[currRecipeIndex].recipeName, "\0");
            }
            else {
	            char *ingredientPtr = strtok(line, ingredientDelim);
                while(ingredientPtr != NULL) {
                    if (strcmp(ingredientPtr, "") != 0) {
                        printf("%s\n", ingredientPtr);
                    }
		            ingredientPtr = strtok(NULL, ingredientDelim);
	            }
            }
        }
        currLine++;
    }*/

    //printf("%s\n", loadedRecipes[0].recipeName);
    //printf("%s\n", loadedRecipes[1].recipeName);
    //printf("%c\n", loadedRecipes[0].ingredients[0].ingredientName[2]);

    //free(loadedRecipes);

    printf("%d", recipesNum);

    fclose(fp);
}
