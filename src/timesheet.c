#include <stdio.h>
#include <stdlib.h>     /* atoi */
#include <time.h>
#include "print_table.h"
#include "last_day.h"
#include "pdf_printer.h"
#include "timesheet.h"

Day_hours* day_hours(int from, int to, int month, int year, int day_off) {
    Day_hours *d_hours;
    int total = (to +1)  - from;
    d_hours = malloc( total * sizeof(Day_hours));

    int i;
    for (i = 0 ; i < total ; i++) {
        int day = i + from;
        float hours = is_weekend(day, month, year) ? ( day_off != day ? 7.5 : 0.0 ) :  0.0;
        Day_hours dh  =  { .day = day, .hours = hours } ;
        d_hours[i] =  dh ;
    }

    return d_hours;
}

int timesheet(int from, int to) {
    int day_off[0];
    return timesheet_with_dayoff(from, to, day_off);
}

int timesheet_with_dayoff(int from, int to,  int *day_off_array) {
    int day_off  = 0;

    time_t t     = time(NULL);
    struct tm tm = *localtime(&t); // now

    int current_year = tm.tm_year + 1900;

    printf("Timesheet for %d-%d-%d  -> %d-%d-%d  \n", 
                current_year, 
                tm.tm_mon, 
                from, 
                current_year, 
                tm.tm_mon, 
                last_day(tm.tm_mon, current_year));

    Day_hours *dh      = day_hours(from, to, tm.tm_mon, current_year, day_off);
    int total          = (to + 1) - from;

    Table table = {
        .sep_v     = '|',
        .joint     = '+',
        .col_with  = 10,
        .day_hours = dh,
        .total =  total
    }; 

    printTable(table);
    printTotal(table);
    pdf_printer(table);
    return 0;
}
