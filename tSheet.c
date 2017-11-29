#include <stdio.h>
#include <stdlib.h>     /* atoi */
#include <time.h>
#include <stdbool.h>

typedef struct {
    int day;
    float hours;
} Day_hours;

bool is_weekend(int d, int m, int y) {
    int week_day = (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7; 
    return week_day < 4;
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

    Day_hours dh = day_hours(FROM, TO, tm.tm_mon, current_year)[ TO - FROM ];
    printf("total days for %d => %.1f \n", dh.day, dh.hours );
 
    return 0;
}
