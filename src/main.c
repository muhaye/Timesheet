#include <stdio.h>
#include <string.h> 
#include <stdlib.h>    /* for exit */
#include <unistd.h>
#include <getopt.h>
#include <regex.h>
#include "main.h"
#include "timesheet.h"
#include "init.h"

int main(int argc, char **argv) {
    int c;
    int digit_optind = 0;

    int err;
    regex_t preg;
    const char *str_regex = "r([0-3]?[0-9]{1})-([0-3]?[0-9]{1})";

    while (1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
            {"add",     required_argument, 0, 'r'},
            {"init",    no_argument,       0, 'i'},
            {"delete",  required_argument, 0,  0 },
            {"verbose", no_argument,       0,  0 },
            {"list",    required_argument, 0, 'c'},
            {"file",    required_argument, 0,  0 },
            {0,         0,                 0,  0 }
        };

        c = getopt_long(argc, argv, "abc:d:012",
                long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
            case 'r':

                printf(" with arg %s\n", optarg);
                const char *str_request = optarg; 

                err = regcomp (&preg, str_regex, REG_EXTENDED);
                if (err == 0)
                {
                    int match;
                    size_t nmatch = 0;
                    regmatch_t *pmatch = NULL;

                    nmatch = preg.re_nsub + 1 ;
                    pmatch = malloc (sizeof (*pmatch) * nmatch);
                    if (pmatch)
                    {
                        match = regexec (&preg, str_request, nmatch, pmatch, 0);

                        regfree (&preg);

                        if (match == 0)
                        {
                            int from;
                            int to; 
                            char *word[nmatch];
                            int start[nmatch]; 
                            int end[nmatch];
                            size_t size[nmatch];
                            printf("nmatch %i\n", nmatch);

                            for (int i = 0; i < nmatch; i++) {
                                char day[5];
                                start[i]= pmatch[i].rm_so;
                                end[i] = pmatch[i].rm_eo;
                                size[i] = end[i] - start[i];

                                if ( i > 0 )    {
                                    sprintf(day, "%.*s", 
                                            size[i],
                                            &str_request[start[i]]);

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
                                        &str_request[start[i]]);
                            }

                            const int day_off[20] = { 15, 17, 18, 19, 20, 21, 22, 25, 26, 27, END_OF_INTS };
                            timesheet_with_dayoff(from, to, day_off);

                        }
                        else if (match == REG_NOMATCH)
                        {
                            printf ("%s n\'est pas une adresse internet valide\n", str_request);
                        }

                        else
                        {
                            char *text;
                            size_t size;

                            size = regerror (err, &preg, NULL, 0);
                            text = malloc (sizeof (*text) * size);
                            if (text)
                            {
                                regerror (err, &preg, text, size);
                                fprintf (stderr, "%s\n", text);
                                free (text);
                            }
                            else
                            {
                                fprintf (stderr, "Memoire insuffisante\n");
                                exit (EXIT_FAILURE);
                            }
                        }
                    }
                    else
                    {
                        fprintf (stderr, "Memoire insuffisante\n");
                        exit (EXIT_FAILURE);
                    }
                }

                printf("option %s", long_options[option_index].name);
                /*
                   if (optarg) {
                   regex_t regex;

                   int reti;
                   size_t maxGroups = 3;
                   regmatch_t groupArray[maxGroups];

                // Compile regular expression /
                reti = regcomp(&regex, "(r([0-9]{1,2})-([0-9]{1,2}))\\W+", 0);
                if (reti) {
                fprintf(stderr, "Could not compile regex\n");
                exit(1);
                }

                // Execute regular expression /
                reti = regexec(&regex, optarg, maxGroups, groupArray, 0);
                if (!reti) {
                char from[2];
                char to[2];

                sprintf(from,"%.*s", 0, 
                groupArray[1].rm_eo - groupArray[1].rm_so, 
                optarg + 1);
                printf("add start at %s ", from );
                }
                else if (reti == REG_NOMATCH) {
                printf("option %s is not valid", optarg);
                }
                else {
                regerror(reti, &regex, optarg, sizeof(optarg));
                fprintf(stderr, "Regex match failed: %s\n", optarg);
                exit(1);
                }

                // Free memory allocated to the pattern buffer by regcomp() /
                regfree(&regex);


                }
                 */

                printf("\n");

                break;
            case 0:
                printf("option %s", long_options[option_index].name);
                if (optarg)
                    printf(" with arg %s", optarg);
                printf("\n");

                const int day_off[2] = { 13, END_OF_INTS };
                timesheet_with_dayoff(1, 30, day_off);

                break;
            case 'i':
                // Create working directory if it does not exits	
                init_working_dir();
                break;
            case '0':
            case '1':
            case '2':
                if (digit_optind != 0 && digit_optind != this_option_optind)
                    printf("digits occur in two different argv-elements.\n");
                digit_optind = this_option_optind;
                printf("option %c\n", c);
                break;

            case 'a':
                printf("option a\n");
                break;

            case 'b':
                printf("option b\n");
                break;

            case 'c':
                printf("option c with value '%s'\n", optarg);
                break;

            case 'd':
                printf("option d with value '%s'\n", optarg);
                break;

            case '?':
                break;

            default:
                printf("?? getopt returned character code 0%o ??\n", c);
        }
    }

    if (optind < argc) {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }

    exit(EXIT_SUCCESS);
}
