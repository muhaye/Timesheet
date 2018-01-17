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

    char question[][2][50] = {
        { "client", "Enter client name:"},
        { "agency_name","Enter Agency name:"},
        { "agency_address", "Enter Agency address:"},
        { "agency_location", "Enter Agency location:"},
        { "agency_postal_code", "Enter Agency postal code:"},
        { "agency_phone", "Enter Agency phone:"},
        { "contact", "Enter contact name:"},
        { "name", "Enter your name:"},
        { "note", "Enter a footer note:"}
    };

    char *answer[9];
    for (int i = 0; i < 9; i++ ) {
        printf("(%i/9) %s \n", i+1, question[i][1] );
        char* ch = malloc (100);
        scanf ("%[^\n^\r]%*c", ch);
        answer[i] = ch;
    }

    printf("Summary:\n----------\n");
    for (int i = 0; i < 9; i++ ) {
        printf("%s: %s \n", question[i][0], answer[i] );
    }
   
    printf("Save entered infos? [Y/n]"); 
    char yn; 
    scanf("%c", &yn);

}

