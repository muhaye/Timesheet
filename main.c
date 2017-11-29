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
    char *header[2] = {"Day", "Hours"};
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


void printHeaderValue(Table table) {
    char *header[2] = {"Day", "Hours"};
    // print headers;
    printf("%c%10s%c%10s%c\n", 
            table.sep_v, 
            header[0], 
            table.sep_v, 
            header[1], 
            table.sep_v
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
    printHeaderValue(table);
    printHeaderLine(table);
    printValue(table);
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
        Day_hours dh  =  { day = day, .hours = hours } ;
        d_hours[i] =  dh ;
    }

    return d_hours;
}


int LastDay (int iMonth, int iYear)
{
    struct tm when;
    time_t lastday;

    // Set up current month
    when.tm_hour = 0;
    when.tm_min = 0;
    when.tm_sec = 0;
    when.tm_mday = 1;

    // Next month 0=Jan
    if (iMonth == 12)
    {
        when.tm_mon = 0;
        when.tm_year = iYear - 1900 + 1;
    }
    else
    {
        when.tm_mon = iMonth;
        when.tm_year = iYear - 1900;
    }
    // Get the first day of the next month
    lastday = mktime (&when);

    // Subtract 1 day
    lastday -= 86400;

    // Convert back to date and time
    when = *localtime (&lastday);

    return when.tm_mday;
} 


int main(int argc, char *argv[]) {
    // printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
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
                LastDay(tm.tm_mon, current_year)
                );

    Day_hours *dh = day_hours(FROM, TO, tm.tm_mon, current_year);
    int total = TO - FROM; 
    Day_hours dh_last = dh[total];
    printf("total days for %d => %.1f \n", dh_last.day, dh_last.hours );
    int i;
    for(i = 0; i <total; i++ ) { 
        printf("TXT1: %9.9d TXT2 %9.9f  \n", dh[i].day, dh[i].hours );
    }


    Table table = {
        .sep_v     = '|',
        .joint     = '+',
        .col_with  = 10,
        .day_hours = dh,
        .total =  total
    }; 

    printTable(table);
    return 0;
}
