#ifndef _H_OUTPUT_
#define _H_OUTPUT_

#include "common.h"

void print_welcome(void);

void print_menu(void);

void print_book(book *temp);

void print_book_table(book_table *table);

void print_key_table(page_key_table *key_table);

void print_table_by_key_table(book_table *table, page_key_table *key_table);

#endif