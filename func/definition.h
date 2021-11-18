#define RECIPES_LOCATION "data/recipes.csv"
#define INGREDIENT_DATA_LOCATION "data/ingredientData.csv"
#define MAX_RECIPE_NAME 128
#define MAX_INGREDIENTS 128
#define MAX_INGREDIENT_NAME 128
#define MAX_CATEGORY_NAME 128

typedef struct {
   char ingredientName[MAX_INGREDIENT_NAME];
   float amount;
   unsigned short weight;
} Ingredient;

typedef struct {
   char recipeName[MAX_RECIPE_NAME];
   Ingredient ingredients[MAX_INGREDIENTS];
   unsigned short ingredientCount;
} Recipe;

typedef struct {
   char ingredientName[MAX_INGREDIENT_NAME];
   float coo;
} IngredientData;

typedef struct {
   char categoryName[MAX_CATEGORY_NAME];
   IngredientData ingredientData[MAX_INGREDIENTS];
   unsigned short ingredientCount;
} Category;
