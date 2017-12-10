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
