#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

#include "utilities.h"
#include "../lib/CuTest-AAU/CuTest.h"

float calculateRecipeCoo(Recipe *recipe, IngredientData *ingredients, int ingrNum);
float calculateIngrCoo(Ingredient ingredient, IngredientData *ingredients, int ingrNum);

// Function to calculate and return alternative recipes
// The function takes the recipe, recipelist, and the parameter alternativeRecipes
// in with the alternative recipes will be returned. The func also takes the ingredient list and its length.
void makeListOfAlternativeRecipes(int recipeIndex, Recipe recipes[], Recipe alternativeRecipes[], IngredientData ingredients[], const int ingrNum, Category categories[], const int categoriesLength){
    //TODO: make targets auto generatet based on RECIPES_IN_ALTERNATIVES_LIST
    const float targets[] = {0.20, 0.40, 0.90};
    Recipe *originalRecipe = &recipes[recipeIndex];
    int ingredientIndexes[originalRecipe->ingredientCount];
    Category* ingredientCategories[originalRecipe->ingredientCount];
    bool lastTest = false;

    const float originalRecipeCoo = calculateRecipeCoo(originalRecipe, ingredients, ingrNum);

    for (int i = 0; i < originalRecipe->ingredientCount; i++){
        const int categoryIndex = getCategoryIndex(originalRecipe->ingredients[i].ingredientCategory, categories, categoriesLength);
        ingredientCategories[i] = &categories[categoryIndex];
        ingredientIndexes[i] = 0;
    }

    IngredientData* bestIngredients[RECIPES_IN_ALTERNATIVES_LIST][originalRecipe->ingredientCount];
    float bestIngredientScores[RECIPES_IN_ALTERNATIVES_LIST];

    for (int i = 0; i < RECIPES_IN_ALTERNATIVES_LIST-1; i++) {
        bestIngredientScores[i] = 100;
    }

    do
    {
        lastTest = true;
        for(int i = 0; i < originalRecipe->ingredientCount; i++) {
            if (ingredientIndexes[i] != ingredientCategories[i]->ingredientCount-1){
                lastTest = false;
                continue;
            }

        }
         int indexToIncrease = originalRecipe->ingredientCount-1;
        do
        {
            ingredientIndexes[indexToIncrease]++;
            if(ingredientIndexes[indexToIncrease] >= ingredientCategories[indexToIncrease]->ingredientCount){
                    ingredientIndexes[indexToIncrease] = 0;
            }

            indexToIncrease--;
        }while(indexToIncrease >= 0 && ingredientIndexes[indexToIncrease + 1] == 0);

        float coo = 0;
        for(int i = 0; i < originalRecipe->ingredientCount; i++){

            coo += ingredientCategories[i]->ingredientData[ingredientIndexes[i]]->coo*originalRecipe->ingredients[i].amount/1000;
        }
        const float ratio = coo / originalRecipeCoo;

        for (int t = 0; t < RECIPES_IN_ALTERNATIVES_LIST ; t++){
            const float target = targets[t];
            const float score = fabs(ratio-target);

            if(score < bestIngredientScores[t]){
                bestIngredientScores[t] = score;

                for (int i = 0; i < originalRecipe->ingredientCount; i++){
                    printf("dette er lig med:%s\n",ingredientCategories[i]->ingredientData[ingredientIndexes[i]]->name);
                    bestIngredients[t][i] = ingredientCategories[i]->ingredientData[ingredientIndexes[i]];
                }
            }
        }
    }while(!lastTest);

    for (int t = 0; t < RECIPES_IN_ALTERNATIVES_LIST; t++)
    {
        printf("\n%d\n",t);

        strcpy(alternativeRecipes[t].name, originalRecipe->name);
        alternativeRecipes[t].ingredientCount = originalRecipe->ingredientCount;
        for(int i = 0; i < originalRecipe->ingredientCount; i++){
            strcpy(alternativeRecipes[t].ingredients[i].name, bestIngredients[t][i]->name);
        }
    }
}

/**
 * Calculating the total COO emission of a given recipe
 * TODO: change the structure of the Ingredient struct to include
 * a pointer to the corresponding IngredientData struct
 */
float calculateRecipeCoo(Recipe *recipe, IngredientData *ingredients, int ingrNum) {
    float tempCOO = 0;
    for (int i = 0; i < recipe->ingredientCount; i++) {
        for (int j = 0; j < ingrNum; j++) {
            if (strcmp(recipe->ingredients[i].name, ingredients[j].name) == 0) {
                tempCOO += ingredients[j].coo * (recipe->ingredients[i].amount/1000);
                break;
            }
        }
    }
    return tempCOO;
}

/**
 * Returns the total COO emission of a given ingredient
 * TODO: change the structure of the Ingredient struct to include
 * a pointer to the corresponding IngredientData struct
 */
float getIngrCoo(Ingredient *ingredient, IngredientData *ingredients, int ingrNum) {
    float tempCoo = 0;
    for (int j = 0; j < ingrNum; j++) {
        if (strcmp(ingredient->name, ingredients[j].name) == 0) {
            tempCoo = ingredients[j].coo;
        }
    }
    return tempCoo;
}
