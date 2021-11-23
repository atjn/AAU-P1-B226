#define RECIPES_LOCATION "data/recipes.csv"
#define INGREDIENT_DATA_LOCATION "data/ingredientData.csv"
#define MAX_RECIPE_NAME 128
#define MAX_INGREDIENTS 400
#define MAX_INGREDIENTS_RECIPE 32
#define MAX_INGREDIENTS_CATEGORY 64
#define MAX_INGREDIENT_NAME 128
#define MAX_CATEGORY_NAME 128
#define MAX_CATEGORIES 128

typedef struct {
   char name[MAX_INGREDIENT_NAME];
   float amount;
   unsigned short weight;
} Ingredient;

typedef struct {
   char name[MAX_RECIPE_NAME];
   Ingredient ingredients[MAX_INGREDIENTS_RECIPE];
   unsigned short ingredientCount;
} Recipe;

typedef struct {
   char name[MAX_INGREDIENT_NAME];
   float coo;
} IngredientData;

typedef struct {
   char categoryName[MAX_CATEGORY_NAME];
   IngredientData ingredientData[MAX_INGREDIENTS_CATEGORY];
   unsigned short ingredientCount;
} Category;

typedef struct {
   Category categories[MAX_CATEGORIES];
   unsigned short categoriesCount;
   IngredientData ingredients[MAX_INGREDIENTS];
   unsigned short ingredientsCount;
} IngredientCategory;
