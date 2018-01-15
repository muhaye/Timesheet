#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "init.h"

#define WORKING_DIR ".timesheet"

struct stat st = {0};

void init_working_dir() {
    char inname[100] ;
    sprintf(inname, "%s/%s", getenv("HOME"), WORKING_DIR);
	if (stat(WORKING_DIR, &st) == -1) {
		mkdir(WORKING_DIR, 0754);
	}
}


void prompt_init() {

    const int CLIENT              = 0; 
    const int AGENCY_NAME         = 1;
    const int AGENCY_ADDRESS      = 2;
    const int AGENCY_LOCATION     = 3;
    const int AGENCY_POSTAL_CODE  = 4;
    const int AGENCY_PHONE        = 5;
    const int CONTACT             = 6;
    const int NAME                = 7;
    const int NOTE                = 8;

    char *question[9];
    question[CLIENT]             = "Enter client name:";
    question[AGENCY_NAME]        = "Enter Agency name:";
    question[AGENCY_ADDRESS]     = "Enter Agency address:";
    question[AGENCY_LOCATION]    = "Enter Agency location:";
    question[AGENCY_POSTAL_CODE] = "Enter Agency postal code:";
    question[AGENCY_PHONE]       = "Enter Agency postal code:";
    question[CONTACT]            = "Enter Agency phone:";
    question[NAME]               = "Enter contact name:";
    question[NOTE]               = "Enter a footer note:";

    char *answer[9];
    for (int i = 0; i < 9; i++ ) {
        printf("question [%i] %s \n", i, question[i] );
       // scanf ("%s", answer[i] );
    }

    for (int i = 0; i < 9; i++ ) {
        //printf("answer %s \n", answer[i] );
    }
    


}

