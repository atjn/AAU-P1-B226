#define RECIPES_LOCATION "data/recipes.csv"
#define INGREDIENT_DATA_LOCATION "data/ingredientData.csv"
#define FILE_CELL_DELIMITER ";"
#define FILE_CATEGORY_DELIMITER "."
#define MAX_FILE_LINE_LENGTH 128
#define MAX_RECIPE_NAME 128
#define MAX_INGREDIENT_CATEGORY_NAME 128
#define MAX_INGREDIENTS 400
#define MAX_INGREDIENTS_RECIPE 32
#define MAX_INGREDIENTS_CATEGORY 128
#define MAX_INGREDIENT_NAME 128
#define MAX_CATEGORY_NAME 128
#define MAX_CATEGORIES 128
#define RECIPES_IN_ALTERNATIVES_LIST 3

typedef struct {
   char name[MAX_INGREDIENT_NAME];
   float amount;
   char ingredientCategory[MAX_INGREDIENT_CATEGORY_NAME];
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
   char name[MAX_CATEGORY_NAME];
   IngredientData *ingredientData[MAX_INGREDIENTS_CATEGORY];
   unsigned short ingredientCount;
} Category;

typedef struct {
   Category categories[MAX_CATEGORIES];
   unsigned short categoriesCount;
   IngredientData ingredients[MAX_INGREDIENTS];
   unsigned short ingredientsCount;
} IngredientCategory;
