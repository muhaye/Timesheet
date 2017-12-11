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
          
        printf("option %s", long_options[option_index].name);
        if (optarg) {
            regex_t regex;
            int reti;
            size_t maxGroups = 3;
            regmatch_t groupArray[maxGroups];
           
            /* Compile regular expression */
            reti = regcomp(&regex, "(r([0-9]{1,2})-([0-9]{1,2}))\\W+", 0);
            if (reti) {
                    fprintf(stderr, "Could not compile regex\n");
                    exit(1);
            }

            /* Execute regular expression */
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

            /* Free memory allocated to the pattern buffer by regcomp() */
            regfree(&regex);


        }

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
