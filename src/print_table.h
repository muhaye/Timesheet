#ifndef PRINT_TABLE_H
#define PRINT_TABLE_H

typedef struct {
    int day;
    float hours;
} Day_hours;

typedef struct Table {
    char sep_v   ;
    char joint   ;
    int col_with ;
    Day_hours *day_hours;
    int total;
} Table;

void printValue(Table table) ;

void printTotalValue(Table table) ;

void printHeaderValue(const char *header[2]);

void printHeaderLine(Table table);

void printTable(Table table); 

void printTotal(Table table);

#endif
