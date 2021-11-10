#include "../lib/CuTest-AAU/CuTest.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <definition.h>

/* Using semicolons instead of commas (Thanks Microsoft) */
void readFile() {
    FILE *fp;
    char *line = NULL;

    Ingredient abekat;

    fp = fopen("data/recipes.csv", "r");
    if (fp == NULL) exit(EXIT_FAILURE);

    fclose(fp);
    if (line) free(line);
}
