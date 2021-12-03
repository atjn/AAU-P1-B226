#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "utilities.h"
#include "../lib/CuTest-AAU/CuTest.h"

bool duplicatedIngredients(Category *[], const int [], const int);
void scopeIngredientIndexes(int [], int [], int [], const Recipe *, const float, Category *[], const float, const float, bool *, const int, const bool);

// Function to calculate and return alternative recipes
// The function takes the recipe, recipelist, and the parameter alternativeRecipes
// in with the alternative recipes will be returned. The func also takes the ingredient list and its length.
void makeListOfAlternativeRecipes(int recipeIndex, Recipe recipes[], Recipe alternativeRecipes[], IngredientData ingredients[], const int ingrNum, Category categories[], const int categoriesLength, const bool optimize){
;
    const float accuracy = optimize ? 0.10 : 0.0;
    const float maxTime = optimize ? 2 : 5400;
    bool targetCanBeSatisfied = true;
    Recipe *originalRecipe = &recipes[recipeIndex];

    const float originalRecipeCoo = calculateRecipeCoo(originalRecipe, ingredients, ingrNum);

    // Generate list of targets
    // A target is how many percent co2 (compared to the original recipe) the alternative recipe should emit.
    float targets[RECIPES_IN_ALTERNATIVES_LIST];
    for(int t = 0; t < RECIPES_IN_ALTERNATIVES_LIST; t++){
        targets[t] = (float)(t+1) / (RECIPES_IN_ALTERNATIVES_LIST+1);
        printf("targets %i: %lf", t, targets[t]);
    }

    // Get this respective ingredientcategory from the original recipe
    // also makes a list of the indexes of ingredients in each category list
    // the list of indexes is used to loop through every single combination of recipes
    int ingredientIndexes[originalRecipe->ingredientCount];
    int ingredientMinIndexes[originalRecipe->ingredientCount];
    int ingredientMaxIndexes[originalRecipe->ingredientCount];
    int ingredientStartIndexes[originalRecipe->ingredientCount];
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

    for (int t = 0; t < RECIPES_IN_ALTERNATIVES_LIST; t++){

        scopeIngredientIndexes(ingredientMaxIndexes, ingredientMinIndexes, ingredientStartIndexes, originalRecipe, originalRecipeCoo, ingredientCategories, targets[t], accuracy, &targetCanBeSatisfied, t, optimize);

        if(DEBUG){
            printf("\n\nNew target: %1.2lf\nCan satisfy target: %s", targets[t], targetCanBeSatisfied ? "yes" : "no");
            printf("\n\nMin:   ");
            for(int i = 0; i < originalRecipe->ingredientCount; i++){
                printf("%2i, ", ingredientMinIndexes[i]);
            }
            printf("\nStart: ");
            for(int i = 0; i < originalRecipe->ingredientCount; i++){
                printf("%2i, ", ingredientStartIndexes[i]);
            }
            printf("\nMax:   ");
            for(int i = 0; i < originalRecipe->ingredientCount; i++){
                printf("%2i, ", ingredientMaxIndexes[i]);
            }
            printf("\nAvail: ");
            for(int i = 0; i < originalRecipe->ingredientCount; i++){
                printf("%2i, ", ingredientCategories[i]->ingredientCount-1);
            }
            printf("\n");
        }

        for(int i = 0; i < originalRecipe->ingredientCount; i++){
            ingredientIndexes[i] = ingredientStartIndexes[i];
        }

        const clock_t start = clock();
        bool triedAllCombinations = false;
        bool foundMatchingIngredients = false;
        bool foundValidIngredients = false;
        do
        {

            // Increase ingredient indexes
            int indexCategoryToIncrease = originalRecipe->ingredientCount-1;
            do
            {
                ingredientIndexes[indexCategoryToIncrease]++;
                if(ingredientIndexes[indexCategoryToIncrease] > ingredientMaxIndexes[indexCategoryToIncrease]){
                        ingredientIndexes[indexCategoryToIncrease] = ingredientMinIndexes[indexCategoryToIncrease];
                }

                indexCategoryToIncrease--;
            }while(indexCategoryToIncrease >= 0 && ingredientIndexes[indexCategoryToIncrease + 1] == ingredientMinIndexes[indexCategoryToIncrease + 1]);

            // Calculate the co2 footprint of the given combination of ingredients
            // the ratio is the percentage-wise difference in co2 emision between the new and orginal recipe.
            float coo = 0;
            for(int i = 0; i < originalRecipe->ingredientCount; i++){
                coo += ingredientCategories[i]->ingredientData[ingredientIndexes[i]]->coo*originalRecipe->ingredients[i].amount;
            }
            const float ratio = (coo/1000) / originalRecipeCoo;

            // Calculate a score for the ingredients combination
            // if the score is better than any other score for a given target,
            // then save it as the best option for now
            const float score = fabs(ratio-targets[t]);

            if(score < bestIngredientScores[t] && !duplicatedIngredients(ingredientCategories, ingredientIndexes, originalRecipe->ingredientCount)){
                foundValidIngredients = true;
                bestIngredientScores[t] = score;
                for(int i = 0; i < originalRecipe->ingredientCount; i++){
                    bestIngredients[t][i] = ingredientCategories[i]->ingredientData[ingredientIndexes[i]];
                }
                if(targets[t]-accuracy <= ratio && ratio <= targets[t]+accuracy){
                    foundMatchingIngredients = true;
                }
            }

            // If all recipe indexes are at the end of the list, then end this while loop.
            // We end it because we have been through all combinations, and thus won't be able to find a better match for our target.
            triedAllCombinations = true;
            for(int i = 0; i < originalRecipe->ingredientCount; i++) {
                if(ingredientIndexes[i] != ingredientStartIndexes[i]){
                    triedAllCombinations = false;
                }
            }

        }while(!triedAllCombinations && !foundMatchingIngredients && (!foundValidIngredients || (double)(clock()-start) < (maxTime/RECIPES_IN_ALTERNATIVES_LIST)*CLOCKS_PER_SEC));

        if(!optimize) printf(" %.0lf%%", (double)((t+1)*100) / RECIPES_IN_ALTERNATIVES_LIST);
        if(DEBUG) printf("Finished in %3.2lfs, max allowed was %3.2lfs\n\n", (double)(clock()-start)/CLOCKS_PER_SEC, maxTime/RECIPES_IN_ALTERNATIVES_LIST);

        // This fails if the algorithm was not able to find even one possible recipe candidate
        assert(foundValidIngredients);

    }

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

bool duplicatedIngredients(Category *ingredientCategories[], const int ingredientIndexes[], const int ingredientCount){

    bool duplicatedIngredients = false;
    for(int i = 0; i < ingredientCount; i++){
        for(int j = 0; j < ingredientCount; j++){
            if(i != j && strcmp(ingredientCategories[i]->ingredientData[ingredientIndexes[i]]->name, ingredientCategories[j]->ingredientData[ingredientIndexes[j]]->name) == 0){
                duplicatedIngredients = true;
            }
        }
    }

    return duplicatedIngredients;
}

void scopeIngredientIndexes(int ingredientMaxIndexes[], int ingredientMinIndexes[], int ingredientStartIndexes[], const Recipe *originalRecipe, const float originalRecipeCoo, Category *ingredientCategories[], const float target, const float accuracy, bool *targetCanBeSatisfied, const int ingredientCategoryIndex, const bool optimize){

    for (int c = 0; c < originalRecipe->ingredientCount; c++){
        ingredientMinIndexes[c] = 0;
        ingredientMaxIndexes[c] = ingredientCategories[c]->ingredientCount-1;
    }

    if(!optimize) return;


    for (int c = 0; c < originalRecipe->ingredientCount; c++){

        for(int i = ingredientMinIndexes[c]; i <= ingredientMaxIndexes[c]; i++){

            float coo = ingredientCategories[c]->ingredientData[i]->coo*originalRecipe->ingredients[c].amount;
            for(int otherC = 0; otherC < originalRecipe->ingredientCount; otherC++){
                if(otherC != c) coo += ingredientCategories[otherC]->ingredientData[ingredientMaxIndexes[otherC]]->coo*originalRecipe->ingredients[otherC].amount;
            }
            const float ratio = (coo/1000) / originalRecipeCoo;
            if(target-accuracy <= ratio){
                ingredientMinIndexes[c] = i;
                break;
            }else if(i >= ingredientMaxIndexes[c]){
                ingredientMinIndexes[c] = i;
                *targetCanBeSatisfied = false;
                break;
            }

        }

        for(int i = ingredientMaxIndexes[c]; i >= ingredientMinIndexes[c]; i--){

            float coo = ingredientCategories[c]->ingredientData[i]->coo*originalRecipe->ingredients[c].amount;
            for(int otherC = 0; otherC < originalRecipe->ingredientCount; otherC++){
                if(otherC != c) coo += ingredientCategories[otherC]->ingredientData[ingredientMinIndexes[otherC]]->coo*originalRecipe->ingredients[otherC].amount;
            }
            const float ratio = (coo/1000) / originalRecipeCoo;
            if(ratio <= target+accuracy){
                ingredientMaxIndexes[c] = i;
                break;
            }else if(i <= ingredientMinIndexes[c]){
                ingredientMaxIndexes[c] = i;
                *targetCanBeSatisfied = false;
                break;
            }
        }

        if(ingredientMinIndexes[c] > ingredientMaxIndexes[c]){
            const int tempMin = ingredientMinIndexes[c];
            ingredientMinIndexes[c] = ingredientMaxIndexes[c];
            ingredientMaxIndexes[c] = tempMin;
            *targetCanBeSatisfied = false;
        }else if(ingredientMinIndexes[c] == ingredientMaxIndexes[c]){
            //this is an import check, because without it, the algorithm could be forced to choose two duplicate ingredients
            if(ingredientMinIndexes[c] > 0){
                ingredientMinIndexes[c] -= 1;
            }else if(ingredientMaxIndexes[c] < ingredientCategories[c]->ingredientCount-1){
                ingredientMaxIndexes[c] += 1;
            }
        }

        ingredientStartIndexes[c] = floor((ingredientMaxIndexes[c] - ingredientMinIndexes[c]) /RECIPES_IN_ALTERNATIVES_LIST *ingredientCategoryIndex)  +ingredientMinIndexes[c];


    }

}
