#include "../lib/CuTest-AAU/CuTest.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Using semicolons instead of commas (Thanks Microsoft) */
void readFile() {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    int lineNumber = 0;
    

    fp = fopen("data/recipes.csv", "r");
    if (fp == NULL) exit(EXIT_FAILURE);

    fclose(fp);
    if (line) free(line);
}
