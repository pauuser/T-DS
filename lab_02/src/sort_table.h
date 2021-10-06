#ifndef _H_SORT_TABLE_
#define _H_SORT_TABLE_

#include "common.h"

void sort_table_full(book_table *table, int64_t *bubble_time_table, int64_t *qsort_time_key);

int compare_books(const void *one, const void *two);

void bubble_sort_table(book_table *table);

void swap_books(book *one, book *two);

void sort_table_key_hub(book_table *table);

#endif