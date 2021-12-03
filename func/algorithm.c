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

    const float accuracy = optimize ? 0.10 : 0.0;
    const float maxTime = optimize ? 2 : 5400;

    bool canSatisfyTarget = true;
    Recipe *originalRecipe = &recipes[recipeIndex];
    const float originalRecipeCoo = calculateRecipeCoo(originalRecipe, ingredients, ingrNum);

    // Generate list of targets
    // A target is how many percent co2 (compared to the original recipe) the alternative recipe should emit.
    float targets[RECIPES_IN_ALTERNATIVES_LIST];
    for(int t = 0; t < RECIPES_IN_ALTERNATIVES_LIST; t++){
        targets[t] = (float)(t+1) / (RECIPES_IN_ALTERNATIVES_LIST+1);
    }

    // Gets the respective ingredientcategories from the original recipe
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

    // This keeps track of the best combination of ingredients for each respective target
    // It is used if it is not possible to satisfy the target - then the closest match (stored here) is used instead
    IngredientData* bestIngredients[RECIPES_IN_ALTERNATIVES_LIST][originalRecipe->ingredientCount];
    float bestIngredientScores[RECIPES_IN_ALTERNATIVES_LIST];
    for (int i = 0; i < RECIPES_IN_ALTERNATIVES_LIST; i++) {
        bestIngredientScores[i] = 100;
    }

    for (int t = 0; t < RECIPES_IN_ALTERNATIVES_LIST; t++){

        scopeIngredientIndexes(ingredientMaxIndexes, ingredientMinIndexes, ingredientStartIndexes, originalRecipe, originalRecipeCoo, ingredientCategories, targets[t], accuracy, &canSatisfyTarget, t, optimize);

        if(DEBUG){
            printf("\n\nNew target: %1.2lf\nCan satisfy target: %s", targets[t], canSatisfyTarget ? "yes" : "no");
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
            // if the ratio hits within the specified target, then save that recipe and quit immediately
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

        }while(!triedAllCombinations && !foundMatchingIngredients && (canSatisfyTarget || !foundValidIngredients || (double)(clock()-start) < (maxTime/RECIPES_IN_ALTERNATIVES_LIST)*CLOCKS_PER_SEC));

        //TODO: This output seems to be buffered and printed in larger batches, but that defeats the purpose of showing the user exactly how far the algorithm is
        if(!optimize) printf(" %.0lf%%", (double)((t+1)*100) / RECIPES_IN_ALTERNATIVES_LIST);

        if(DEBUG) printf("Finished in %3.2lfs, max allowed was %3.2lfs\n\n", (double)(clock()-start)/CLOCKS_PER_SEC, maxTime/RECIPES_IN_ALTERNATIVES_LIST);

        // This fails if the algorithm was not able to find even one possible recipe candidate
        // This usually happens when there are too many ingredients with the same category and/or too few options available in the category
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

/**
 * @brief checks if a list of ingredients contains duplicate ingredients
 *
 * @param ingredientCategories
 * @param ingredientIndexes
 * @param ingredientCount
 * @return true
 * @return false
 */
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

/**
 * @brief uses a less intensive algorithm to remove ingredients that would never be able to satisfy the given target, before the main algorithm us run
 *
 * @param ingredientMaxIndexes - will return the max ingredient index that the main algorithm should check
 * @param ingredientMinIndexes - will return the minimum ingredient index that the main algorithm should check
 * @param ingredientStartIndexes - will return the recommended ingredient start index for the main algorithm (speculative)
 * @param originalRecipe
 * @param originalRecipeCoo
 * @param ingredientCategories
 * @param target
 * @param accuracy
 * @param targetCanBeSatisfied - will return whether or not it should be possible to satisfy the target
 * @param ingredientCategoryIndex
 * @param optimize
 */
void scopeIngredientIndexes(int ingredientMaxIndexes[], int ingredientMinIndexes[], int ingredientStartIndexes[], const Recipe *originalRecipe, const float originalRecipeCoo, Category *ingredientCategories[], const float target, const float accuracy, bool *targetCanBeSatisfied, const int ingredientCategoryIndex, const bool optimize){

    // Reset all indexes
    for (int c = 0; c < originalRecipe->ingredientCount; c++){
        ingredientMinIndexes[c] = 0;
        ingredientMaxIndexes[c] = ingredientCategories[c]->ingredientCount-1;
    }

    if(!optimize) return;

    // NOTE: These optimizations only work because the ingredients are sorted by Co2-emissions (least to most)

    for (int c = 0; c < originalRecipe->ingredientCount; c++){

        // Remove all ingredients that emit so little CO2, they can't possibly hit the given target
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

        // Remove all ingredients that emit so much CO2, they can't possibly hit the given target
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

        // If the min and max ingredient indexes have gone beyond each other, then it means it is impossible to hit the target
        // In that case, set the indexes up for the algorithm to quickly find something as close as possible to the target
        if(ingredientMinIndexes[c] > ingredientMaxIndexes[c]){
            const int tempMin = ingredientMinIndexes[c];
            ingredientMinIndexes[c] = ingredientMaxIndexes[c];
            ingredientMaxIndexes[c] = tempMin;
            *targetCanBeSatisfied = false;
        }else if(ingredientMinIndexes[c] == ingredientMaxIndexes[c]){
            // This is an important check, because without it, the algorithm could be forced to choose two duplicate ingredients.
            // TODO: The algorithm can still be forced to do this in extreme cases. This should be solved in a better way.
            if(ingredientMinIndexes[c] > 0){
                ingredientMinIndexes[c] -= 1;
            }else if(ingredientMaxIndexes[c] < ingredientCategories[c]->ingredientCount-1){
                ingredientMaxIndexes[c] += 1;
            }
        }

        // The optimal ingredient combination is usually comprised of ingredients that are close to the middle of their respsective lists.
        // Knowing this, ask the algorithm to start the search with the index of each ingredient 1/3 into the list.
        // If no suitable target was found in the last 2/3 of the list, then the algorithm will also check the first 1/3 of the list.
        ingredientStartIndexes[c] = floor((ingredientMaxIndexes[c] - ingredientMinIndexes[c]) /RECIPES_IN_ALTERNATIVES_LIST *ingredientCategoryIndex)  +ingredientMinIndexes[c];


    }

}
