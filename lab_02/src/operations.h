#ifndef _H_OPERATIONS_
#define _H_OPERATIONS_

#include "common.h"

void add_line(book_table *table);

void delete_line(book_table *table);

int value_in_mas(char *value, char **mas, int n);

void delete_new_str_sym(char *str);

void find_tech_data_by_area(book_table *table);

#endif