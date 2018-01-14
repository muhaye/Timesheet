#include <stdio.h>
#include <string.h> 
#include <stdlib.h>    /* for exit */
#include <unistd.h>
#include <getopt.h>
#include <regex.h>
#include "main.h"
#include "timesheet.h"
#include "init.h"
#include "day_parse.h"

int main(int argc, char **argv) {
    int c;
    int digit_optind = 0;

    while (1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
            {"init",    no_argument,       0, 'i'},
            {"work",    required_argument, 0, 'r'},
            {"off",     required_argument, 0, 'o'},
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

                printf("option %s", long_options[option_index].name);

                int error = 0;
                const char *str_request = optarg; 

                Days_range dr = day_parse(optarg, &error);
                if ( error == 1 ) {

                    fprintf (stderr, "Memoire insuffisante\n");
                    exit (EXIT_FAILURE);
                }else {

                    const int day_off[20] = { 17, 18, 19, 20, 21, 22, 25, 26, 27, END_OF_INTS };
                    timesheet_with_dayoff(dr.from, dr.to, day_off);
                }
                printf(" with arg %s", optarg);


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
