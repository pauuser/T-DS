#ifndef _H_INPUT_
#define _H_INPUT_

#include "common.h"

int input_data_from_file(book_table *table);

int check_file(FILE *f, int n);

int check_string(char *string);

int str_to_num(char *str);

int create_mas_of_words(char *string, char **mas, int max_number, char *delims);

int count_file_len(FILE *f);

int string_is_not_empty(char *string);

book input_line(char *line);

#endif