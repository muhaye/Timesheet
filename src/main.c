#include <stdio.h>
#include <string.h> 
#include <stdlib.h>    /* for exit */
#include <unistd.h>
#include <getopt.h>
#include "main.h"
#include "timesheet.h"
#include "init.h"
#include "day_parse.h"
#include "read_README.h"

static const char APP_VERSION[] = "0.1";

int main(int argc, char **argv) {
    int c;
    int digit_optind = 0;

    Days_range dr;
    int *day_off = (int [20]) { END_OF_INTS } ; 

    while (1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
            {"version", no_argument,       0, 'v'},
            {"init",    no_argument,       0, 'i'},
            {"work",    required_argument, 0, 'w'},
            {"off",     required_argument, 0, 'o'},
            {"help",    no_argument,       0, 'h'},
            {0,         0,                 0,  0 }
        };

        c = getopt_long(argc, argv, "abc:d:012",
                long_options, &option_index);

        if (c == -1) 
            break;

        switch (c) {
            case 'w':

                printf("with --work %s\n", optarg);
                
                int error = 0;
                const char *str_request = optarg; 

                dr = day_parse(optarg, &error);
                if ( error == 1 ) {

                    fprintf (stderr, "Memoire insuffisante\n");
                    exit (EXIT_FAILURE);
                }

                break;
            case 'o':

                printf("option --off %s\n", optarg);
               
                if (optarg[0] == 'r') {

                    int off_error = 0;
                    Days_range off_dr = day_parse(optarg, &off_error);
                    int j = 0; 
                    for (int i = off_dr.from;  i <= off_dr.to; i++) { 
                        day_off[j++] = i;
                    } 
                } else if (optarg[0] == 'd') {
                    char **tokens;
                    char *str_days = &optarg[1];
                    tokens = str_split(str_days, ',');

                     if (tokens) {
                         int i;
                         for (i = 0; *(tokens + i); i++) {
                             day_off[i] = atoi(*(tokens + i));
                             printf("month=[%s]\n", *(tokens + i));
                             free(*(tokens + i));
                         }
                         printf("\n");
                         free(tokens);
                     }
                } 

                break;

            case 'i':
                // Create working directory if it does not exits	
                printf("'%s'... \n Create working directory if it does not exits\n",
                        long_options[option_index].name);
                init_working_dir();
                // Prompt init question
                prompt_init();
                break;

            case 'v':
                printf("%s\n", APP_VERSION);
                break;

            case 'h':
                rEADME_file_content();
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
        rEADME_file_content();
    }else{
        if (dr.from > 0 ) {
            timesheet_with_dayoff(dr.from, dr.to, day_off);
        }
    }

    exit(EXIT_SUCCESS);
}
