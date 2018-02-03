#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_README.h"

const char *READMEFile = "README.md";

void rEADME_file_content() {

    FILE *infile;
    char line_buffer[BUFSIZ];
    char line_number;

    infile = fopen(READMEFile, "r");
    if (!infile) {
        printf("Couldn't open file %s for reading.\n", READMEFile);
        return ;
    }

    line_number = 0;
    while (fgets(line_buffer, sizeof(line_buffer), infile)) {
        ++line_number;

        printf(" %s", line_buffer);
    }
}

