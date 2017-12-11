#include <stdio.h>
#include "main.h"
#include "timesheet.h"

int main(int argc, char **argv) {
	const int day_off[2] = { 13, END_OF_INTS };
	timesheet_with_dayoff(1, 30, day_off);
    //timesheet(1, 25);
    return 0;
}
