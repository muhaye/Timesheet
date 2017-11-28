#include <stdio.h>
#include <stdlib.h>     /* atoi */
#include <time.h>

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
                1, 
                current_year, 
                tm.tm_mon, 
                LastDay(tm.tm_mon, current_year)
                );

    return 0;
}
