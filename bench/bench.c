#include "../func/definitions.h"
#include "../func/algorithm.h"
#include "../func/fileHandle.h"
#include "../func/utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define BENCH_RECIPES_LENGTH 10
#define MAX_TEST_DURATION 120
#define MIN_TEST_DURATION 10

void bench(const int length, const bool checkAccuracy){

    printf("NOTE: If the imported recipe data changes, it can have effect on the performance of this benchmark, so please only compare benches made on the same dataset.");

    //DEBUG can affect the bench performance, so it is outlawed
    assert(!DEBUG);
    srand(69420);

    int ingredientsLength, categoriesLength;
    IngredientData *ingredients = NULL;
    Category *categories = NULL;
    readIngredients(INGREDIENT_DATA_LOCATION, &ingredients, &categories, &ingredientsLength, &categoriesLength);

    Recipe recipes[BENCH_RECIPES_LENGTH];

    // Generate test recipes
    for(int r = 0; r < BENCH_RECIPES_LENGTH; r++){

        recipes[r].ingredientCount = length;

        for(int i = 0; i < length; i++){
            const IngredientData *randIngredient = &ingredients[rand() % ingredientsLength];
            strcpy(recipes[r].ingredients[i].name, randIngredient->name);
            recipes[r].ingredients[i].amount = rand() % 200;
            for(int c = 0; c < categoriesLength; c++){
                for(int d = 0; d < categories[c].ingredientCount; d++){
                    if(strcmp(categories[c].ingredientData[d]->name, randIngredient->name) == 0){
                        strcpy(recipes[r].ingredients[i].ingredientCategory, categories[c].name);
                        break;
                    }
                }
            }
        }

    }

    Recipe accurateAlternativeRecipes[BENCH_RECIPES_LENGTH][RECIPES_IN_ALTERNATIVES_LIST];

    if(checkAccuracy){
        printf("\n\nCalculating optimal Co2 emmissions for each recipe. If you have chosen a high number, this could take a loong time.\n");
        for(int r = 0; r < BENCH_RECIPES_LENGTH; r++){
            printf("\n%2i/%2i:", r+1, BENCH_RECIPES_LENGTH);
            makeListOfAlternativeRecipes(r, recipes, accurateAlternativeRecipes[r], ingredients, ingredientsLength, categories, categoriesLength, false);

        }
        printf("\n");
    }


    Recipe alternativeRecipes[BENCH_RECIPES_LENGTH][RECIPES_IN_ALTERNATIVES_LIST];

    printf("\nStarting test with recipes of length %i. It should take at most %i seconds.\n", length, MAX_TEST_DURATION);
    const clock_t start = clock();
    int runs = 0;
    while(((double)(clock()-start) < MIN_TEST_DURATION * CLOCKS_PER_SEC || runs < BENCH_RECIPES_LENGTH*2) && (double)(clock()-start) < MAX_TEST_DURATION * CLOCKS_PER_SEC){
        makeListOfAlternativeRecipes(runs % BENCH_RECIPES_LENGTH, recipes, alternativeRecipes[runs % BENCH_RECIPES_LENGTH], ingredients, ingredientsLength, categories, categoriesLength, true);
        runs++;
    }

    printf("Test done!\n\nAlgorithm ran %i times and took %.8lf seconds per recipe.\n", runs, ((double)(clock()-start) / CLOCKS_PER_SEC) / runs);


    if(checkAccuracy){

        float globalBias = 0;
        float globalAccuracy = 0;
        int testedIngredients = 0;

        for(int r = 0; r < BENCH_RECIPES_LENGTH; r++){
            for(int a = 0; a < RECIPES_IN_ALTERNATIVES_LIST; a++){
                const float bias = (calculateRecipeCoo(&alternativeRecipes[r][a], ingredients, ingredientsLength) / calculateRecipeCoo(&accurateAlternativeRecipes[r][a], ingredients, ingredientsLength)) *100;
                const float accuracy = fabs(100 - bias);
                globalBias += bias;
                globalAccuracy += accuracy;
                testedIngredients++;
            }
        }

        globalBias = (globalBias / testedIngredients) -100;
        globalAccuracy = 100- (globalAccuracy / testedIngredients);

        printf("\nAccuracy: %3.0lf%%\nBias: %3.0lf%%\n", globalAccuracy, globalBias);
    }

    printf("\n");

    free(ingredients);
    free(categories);
}

