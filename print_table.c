#include <stdio.h>
#include "print_table.h"

void printValue(Table table) {
    for(int i = 0; i <table.total; i++ ) { 
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
