#include <time.h>
#include "last_day.h"

int last_day (int i_month, int i_year) {
    struct tm when;
    time_t lastday;

    // Set up current month
    when.tm_hour = 0;
    when.tm_min = 0;
    when.tm_sec = 0;
    when.tm_mday = 1;

    // Next month 0=Jan
    if (i_month == 12)
    {
        when.tm_mon = 0;
        when.tm_year = i_year - 1900 + 1;
    }
    else
    {
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
