#define RECIPES_LOCATION "data/recipes.csv"
#define MAX_RECIPE_NAME 32
#define MAX_INGREDIENTS 64
#define MAX_INGREDIENT_NAME 16
#define MAX_CATEGORY_NAME 16

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

typedef struct {
   char ingredientName[MAX_INGREDIENT_NAME];
   float coo;
} IngredientData;

typedef struct {
   char categoryName[MAX_CATEGORY_NAME];
   IngredientData ingredientsData[MAX_INGREDIENTS];
} Category;
