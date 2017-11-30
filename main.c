#include "last_day.h"
#include <stdio.h>
#include <stdlib.h>     /* atoi */
#include <time.h>
#include <stdbool.h>

typedef struct {
    int day;
    float hours;
} Day_hours;

typedef struct {
    char sep_v   ;
    char joint   ;
    int col_with ;
    Day_hours *day_hours;
    int total;
} Table;

void printValue(Table table) {
    // print headers;
    int i;
    for(i = 0; i <table.total; i++ ) { 
        //printf("TXT1: %9.9d TXT2 %9.9f  \n", dh[i].day, dh[i].hours );
        printf("%c%10d%c%10.1f%c\n", 
                table.sep_v, 
                table.day_hours[i].day, 
                table.sep_v, 
                table.day_hours[i].hours, 
                table.sep_v
              );
    }
}

void printTotalValue(Table table) {
	// print headers;
	int sum_d = 0;
	float sum_h = 0;

	for(int i = 0; i < table.total ; i ++){
		sum_d = sum_d + table.day_hours[i].day;	
		sum_h = sum_h + table.day_hours[i].hours;	
	}

	printf("%c%10d%c%10.1f%c\n", 
			table.sep_v, 
			sum_d, 
			table.sep_v, 
			sum_h, 
			table.sep_v
		  );
}

void printHeaderValue(const char *header[2]) {
    // print headers;
    printf("%c%10s%c%10s%c\n", 
            '|', 
            header[0], 
            '|', 
            header[1], 
            '|'
          );
}

void printHeaderLine(Table table) {
    char *sep = "----------------------";
    // print headers;
    printf("%c%.*s%c%.*s%c\n", 
            table.joint, 
            table.col_with,
            sep, 
            table.joint, 
            table.col_with,
            sep, 
            table.joint
          );
}

void printTable(Table table) {
    printHeaderLine(table);
	const char *header[] = {"Day", "Hours"};
    printHeaderValue(header);
    printHeaderLine(table);
    printValue(table);
    printHeaderLine(table);
}

void printTotal(Table table) {
    printHeaderLine(table);
	const char *header[] = {"Day", "Hours"};
    printHeaderValue(header);
    printHeaderLine(table);
    printTotalValue(table);
    printHeaderLine(table);
}

bool is_weekend(int d, int m, int y) {
    int week_day = (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7; 
    return week_day < 5;
} 

Day_hours* day_hours(int from, int to, int month, int year) {
    Day_hours *d_hours;
    int total = (to +1)  - from;
    d_hours = malloc( total * sizeof(Day_hours));

    int i;
    for (i = 0 ; i < total ; i++) {
        int day = i + from;
        float hours = is_weekend(day, month, year) ? 7.5 :  0.0;
        Day_hours dh  =  { .day = day, .hours = hours } ;
        d_hours[i] =  dh ;
    }

    return d_hours;
}

int main(int argc, char *argv[]) {
    int FROM     = atoi(argv[1]);
    int TO       = atoi(argv[2]);

    time_t t     = time(NULL);
    struct tm tm = *localtime(&t); // now

    int current_year = tm.tm_year + 1900;

    printf("Timesheet for %d-%d-%d  -> %d-%d-%d  \n", 
                current_year, 
                tm.tm_mon, 
                FROM, 
                current_year, 
                tm.tm_mon, 
                last_day(tm.tm_mon, current_year)
                );

    Day_hours *dh = day_hours(FROM, TO, tm.tm_mon, current_year);
    int total = TO - FROM; 
    Day_hours dh_last = dh[total];
    printf("total days for %d => %.1f \n", dh_last.day, dh_last.hours );

    Table table = {
        .sep_v     = '|',
        .joint     = '+',
        .col_with  = 10,
        .day_hours = dh,
        .total =  total
    }; 

    printTable(table);
    printTotal(table);
    return 0;
}
