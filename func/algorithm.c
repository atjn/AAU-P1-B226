#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

#include "utilities.h"
#include "../lib/CuTest-AAU/CuTest.h"

// Function to calculate and return alternative recipes
// The function takes the recipe, recipelist, and the parameter alternativeRecipes
// in with the alternative recipes will be returned. The func also takes the ingredient list and its length.
void makeListOfAlternativeRecipes(int recipeIndex, Recipe recipes[], Recipe alternativeRecipes[], IngredientData ingredients[], const int ingrNum, Category categories[], const int categoriesLength){
    //TODO: make targets auto generatet based on RECIPES_IN_ALTERNATIVES_LIST
    //This list of targets is how many percent less co2 *100 the recipe should emit for each respective recipe in the list.
    const float targets[] = {0.20, 0.40, 0.90};
    Recipe *originalRecipe = &recipes[recipeIndex];

    const float originalRecipeCoo = calculateRecipeCoo(originalRecipe, ingredients, ingrNum);

    // Get this respective ingredientcategory from the original recipe
    // also makes a list of the indexes of ingredients in each category list
    // the list of indexes is used to loop through every single combination of recipes
    int ingredientIndexes[originalRecipe->ingredientCount];
    Category* ingredientCategories[originalRecipe->ingredientCount];
    for (int i = 0; i < originalRecipe->ingredientCount; i++){
        const int categoryIndex = getCategoryIndex(originalRecipe->ingredients[i].ingredientCategory, categories, categoriesLength);
        ingredientCategories[i] = &categories[categoryIndex];
        ingredientIndexes[i] = 0;
    }

    // This keeps track of the best combination of ingredients for each respective targets
    IngredientData* bestIngredients[RECIPES_IN_ALTERNATIVES_LIST][originalRecipe->ingredientCount];
    float bestIngredientScores[RECIPES_IN_ALTERNATIVES_LIST];
    for (int i = 0; i < RECIPES_IN_ALTERNATIVES_LIST; i++) {
        bestIngredientScores[i] = 100;
    }

    bool lastTest = false;
    do
    {
        // If all recipe indexes are at the end of the list, then end this while loop
        // we end it because we have been through all combinations
        lastTest = true;
        for(int i = 0; i < originalRecipe->ingredientCount; i++) {
            if (ingredientIndexes[i] != ingredientCategories[i]->ingredientCount-1){
                lastTest = false;
                continue;
            }

        }

        // Increase ingredient indexes
        int indexToIncrease = originalRecipe->ingredientCount-1;
        do
        {
            ingredientIndexes[indexToIncrease]++;
            if(ingredientIndexes[indexToIncrease] >= ingredientCategories[indexToIncrease]->ingredientCount){
                    ingredientIndexes[indexToIncrease] = 0;
            }

            indexToIncrease--;
        }while(indexToIncrease >= 0 && ingredientIndexes[indexToIncrease + 1] == 0);

        // Calculate the co2 foodprint of the given combination of ingredients
        // the ratio is the percentage-wise difference in co2 emision between the new and orginal recipe.
        float coo = 0;
        for(int i = 0; i < originalRecipe->ingredientCount; i++){
            coo += (ingredientCategories[i]->ingredientData[ingredientIndexes[i]]->coo*originalRecipe->ingredients[i].amount)/1000;
        }
        const float ratio = 1 - coo / originalRecipeCoo;

        // Calculate a score for the ingredients combination
        // if the score is better than any other score for a given target,
        // then save it as the best option for now
        for (int t = 0; t < RECIPES_IN_ALTERNATIVES_LIST ; t++){
            const float score = fabs(ratio-targets[t]);

            if(score < bestIngredientScores[t]){

                bool noDuplicatedIngredients = true;
                for(int i = 0; i < originalRecipe->ingredientCount; i++){
                    for(int j = 0; j < originalRecipe->ingredientCount; j++){
                        if(i != j && strcmp(ingredientCategories[i]->ingredientData[ingredientIndexes[i]]->name, ingredientCategories[j]->ingredientData[ingredientIndexes[j]]->name) == 0){
                            noDuplicatedIngredients = false;
                        }
                    }
                }

                if(noDuplicatedIngredients){
                    bestIngredientScores[t] = score;
                    for (int i = 0; i < originalRecipe->ingredientCount; i++){
                        bestIngredients[t][i] = ingredientCategories[i]->ingredientData[ingredientIndexes[i]];
                    }
                }
            }
        }
    }while(!lastTest);

    // Generate the final recipe structs that are needed to print the recipe to the user.
    for (int t = 0; t < RECIPES_IN_ALTERNATIVES_LIST; t++)
    {
        strcpy(alternativeRecipes[t].name, originalRecipe->name);
        alternativeRecipes[t].ingredientCount = originalRecipe->ingredientCount;
        for(int i = 0; i < originalRecipe->ingredientCount; i++){
            strcpy(alternativeRecipes[t].ingredients[i].name, bestIngredients[t][i]->name);
            strcpy(alternativeRecipes[t].ingredients[i].ingredientCategory, originalRecipe->ingredients[i].ingredientCategory);
            alternativeRecipes[t].ingredients[i].amount = originalRecipe->ingredients[i].amount;
        }
    }
}
