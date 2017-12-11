#include <stdio.h>
#include <stdlib.h>     /* atoi */
#include <time.h>
#include "print_table.h"
#include "last_day.h"
#include "pdf_printer.h"
#include "timesheet.h"

const int END_OF_INTS = 0 ;
/*
 *
 * day_off: a zero-end array of day_offs 
 *   		ie: int day_off[5] = { 1, 5, 8,  13, 0 } ; // O is te the end of the array
 */
int is_day_off(int day, const int* day_off) {
	const int *pd = day_off;

	do{	
		if( day == *pd++ )
			return 1;
	} while(*pd); 

	return 0;
}

Day_hours* day_hours(
		int from, 
		int to, 
		int month, 
		int year, 
		const int *day_off) {

	Day_hours *d_hours;
	int total = (to +1)  - from;
	d_hours = malloc( total * sizeof(Day_hours));

    for (int i = 0 ; i < total ; i++) {
        int day = i + from;
        float hours = !is_weekend(day, month, year) || is_day_off(day, day_off) ?  0.0 : 7.5 ;
        Day_hours dh = { .day = day, .hours = hours } ;
        d_hours[i] = dh ;
    }

    return d_hours;
}

int timesheet(int from, int to) {
    int day_off[1] = { 0 }; // O is te the end of the array
    //int day_off[5] = { 1, 5, 8,  13, 0 } ; // O is te the end of the array
    return timesheet_with_dayoff(from, to, day_off);
}

int timesheet_with_dayoff(int from, int to, const int *day_off) {

    time_t t     = time(NULL);
    struct tm tm = *localtime(&t); // now

    int current_year = tm.tm_year + 1900;

    Day_hours *dh = day_hours(from, to, tm.tm_mon, current_year, day_off);

	Table table = {
		.sep_v     = '|',
		.joint     = '+',
		.col_with  = 10,
		.day_hours = dh,
		.start_time = tm,
		.total =  to + 1 - from
	}; 

    printTable(table);
    printTotal(table);
    pdf_printer(table);

    return 0;
}
