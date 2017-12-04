#include "last_day.h"
#include <stdio.h>
#include <stdlib.h>     /* atoi */
#include <time.h>
#include "print_table.h"
#include "pdf_printer.h"

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

    Day_hours *dh             = day_hours(FROM, TO, tm.tm_mon, current_year);
    int total                 = (TO + 1) - FROM;
    Day_hours dh_last         = dh[total];

    Table table = {
        .sep_v     = '|',
        .joint     = '+',
        .col_with  = 10,
        .day_hours = dh,
        .total =  total
    }; 

    printTable(table);
    printTotal(table);
    char *text = "Hello world";
    my_pdf_printer(text);
    return 0;
}
