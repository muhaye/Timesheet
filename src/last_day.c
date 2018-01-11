#include <time.h>
#include <stdbool.h>
#include "last_day.h"

/**
 * int d    = 15   ; //Day     1-31
 * int m    = 5    ; //Month   1-12`
 * int y    = 2013 ; //Year    2013` 
 */
bool is_weekend(int d, int m, int y) {
    m++;
    int week_day = (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7; 
    return  ( week_day > 0 && week_day < 6 ) ;
} 

int last_day(int i_month, int i_year) {
    struct tm when;
    time_t lastday;

    // Set up current month
    when.tm_hour = 0;
    when.tm_min = 0;
    when.tm_sec = 0;
    when.tm_mday = 1;

    // Next month 0=Jan
    if (i_month == 12) {
        when.tm_mon = 0;
        when.tm_year = i_year - 1900 + 1;
    } else {
        when.tm_mon = i_month;
        when.tm_year = i_year - 1900;
    }

    // Get the first day of the next month
    lastday = mktime (&when);

    // Subtract 1 day
    lastday -= 86400;

    // Convert back to date and time
    when = *localtime (&lastday);
    return when.tm_mday;
} 
