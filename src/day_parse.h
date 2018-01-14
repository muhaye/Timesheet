#ifndef DAY_PARSE_H 
#define DAY_PARSE_H

typedef
struct {
    int from;
    int to;
} Days_range; 

Days_range day_parse(const char *pattern, int *error);

char** str_split(char* a_str, const char a_delim);

#endif
