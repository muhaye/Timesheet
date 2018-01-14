#include <stdio.h>
#include <string.h> 
#include <stdlib.h>    /* for exit */
#include <unistd.h>
#include <regex.h>
#include <assert.h>
#include "day_parse.h"

Days_range day_parse(const char *pattern, int *error) {

    printf(" with arg %s\n", optarg);
    int err;
    regex_t preg;
    const char *str_regex = "r([0-3]?[0-9]{1})-([0-3]?[0-9]{1})";
    err = regcomp (&preg, str_regex, REG_EXTENDED);
    if (err == 0) {

        int match;
        size_t nmatch = 0;
        regmatch_t *pmatch = NULL;

        nmatch = preg.re_nsub + 1 ;
        pmatch = malloc (sizeof (*pmatch) * nmatch);
        if (pmatch) {

            match = regexec (&preg, pattern, nmatch, pmatch, 0);

            regfree (&preg);

            if (match == 0) {

                int from;
                int to; 
                char *word[nmatch];
                int start[nmatch]; 
                int end[nmatch];
                size_t size[nmatch];
                printf("nmatch %i\n", nmatch);

                for (int i = 0; i < nmatch; i++) {

                    char day[5];
                    start[i] = pmatch[i].rm_so;
                    end[i]   = pmatch[i].rm_eo;
                    size[i]  = end[i] - start[i];

                    if ( i > 0 )    {
                        sprintf(day, "%.*s", 
                                size[i],
                                &pattern[start[i]]);

                        if ( i == 1 ) 
                            from = atoi(day);
                        else if ( i == 2) 
                            to = atoi( day );
                    }

                    printf ("match: [%i-%i] %i => %.*s\n", 
                            start[i], 
                            end[i], 
                            i,
                            size[i],
                            &pattern[start[i]]);
                }

                Days_range dr = { .from = from, .to = to };

                return dr;

            } else if (match == REG_NOMATCH) {

                printf ("%s is not a valid argument", pattern);
            } else {

                char *text;
                size_t size;

                size = regerror (err, &preg, NULL, 0);
                text = malloc (sizeof (*text) * size);
                if (text) {

                    regerror (err, &preg, text, size);
                    fprintf (stderr, "%s\n", text);
                    free (text);
                } else {

                    fprintf (stderr, "Memoire insuffisante\n");
                }
            }

        } else {

            fprintf (stderr, "Memoire insuffisante\n");
        }
    }

    *error = 1;
    Days_range  dr = { .from = 0 , .to = 0 };
    return dr;
}

char** str_split(char* a_str, const char a_delim) {
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
     *        knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}
