#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "read_rc_file.h"

const char * rcfile = ".timesheetrc" ;

char *trimwhitespace(char *str)
{
    char *end;
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)  // All spaces?
        return str;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    *(end+1) = 0;

    return str;
}

struct nlist* read_rc_config() {
    struct nlist *result;
        
    char inname[100] ;
    sprintf(inname, "%s/%s", getenv("HOME"), rcfile);

    FILE *infile;
    char line_buffer[BUFSIZ]; /* BUFSIZ is defined if you include stdio.h */
    char line_number;
    char sep = '=';
    const char *ptr; 
    char *subbuff;

    infile = fopen(inname, "r");
    if (!infile) {
        printf("Couldn't open file %s for reading.\n", inname);
        return 0;
    }

    printf("Opened file %s for reading.\n", inname);

    line_number = 0;
    while (fgets(line_buffer, sizeof(line_buffer), infile)) {
        ++line_number;
        /* note that the newline is in the buffer */
        const char *ptr = strchr(line_buffer, sep);
        if(ptr) {
            int index = ptr - line_buffer;
            subbuff = (char*) malloc(index * sizeof(char));
            memcpy(subbuff, line_buffer, index);
            install(trimwhitespace(subbuff), &line_buffer[index +1] );
        }
    }

    return result;
}
