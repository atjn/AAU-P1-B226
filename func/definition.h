#define RECIPES_LOCATION "data/recipes.csv"
#define MAX_RECIPE_NAME 128
#define MAX_INGREDIENTS 64
#define MAX_INGREDIENT_NAME 16

typedef struct {
   char ingredientName[MAX_INGREDIENT_NAME];
   unsigned short amount;
   unsigned short weight;
} Ingredient;

typedef struct {
   char recipeName[MAX_RECIPE_NAME];
   Ingredient ingredients[MAX_INGREDIENTS];
   unsigned short ingredientCount;
} Recipe;
