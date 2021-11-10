#include "lib/CuTest-AAU/CuTest.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Using semicolons instead of commas (Thanks Microsoft) */
void readFile() {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int lineNumber = 0;
    

    fp = fopen("opskrifter.csv", "r");
    if (fp == NULL) exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        if (lineNumber != 0) {
            printf("%s", line);
        }
        lineNumber++;
    }

    fclose(fp);
    if (line) free(line);
}
