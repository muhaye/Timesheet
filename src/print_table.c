#include <stdio.h>
#include "print_table.h"


#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

void printValue(Table table) {
    for(int i = 0; i <table.total; i++ ) { 
        printf("%c%5d     %c%7.1f   %c\n", 
                table.sep_v, 
                table.day_hours[i].day, 
                table.sep_v, 
                table.day_hours[i].hours, 
                table.sep_v
              );
    }
}

void printTotalValue(Table table) {
	int sum_d = 0;
	float sum_h = 0;

	for(int i = 0; i < table.total ; i ++){
		sum_d = sum_d + (table.day_hours[i].hours > 0.0 ? 1 : 0);
		sum_h = sum_h + table.day_hours[i].hours;	
	}

    char total_days[100]; 
    char total_hours[100]; 
    sprintf(total_days, "\n\t total: %5d days.\n", sum_d);
    sprintf(total_hours, "\t total: %5.1f hours.\n", sum_h);

    printf(GRN "%s" RESET, total_days);
    printf(GRN "%s" RESET, total_hours);

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
	const char *header[] = {"Day   ", "Hours   "};
    printHeaderValue(header);
    printHeaderLine(table);
    printValue(table);
    printHeaderLine(table);
}

void printTotal(Table table) {
    printTotalValue(table);
}
