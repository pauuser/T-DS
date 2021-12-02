#ifndef _H_SORT_KEY_
#define _H_SORT_KEY_

#include "common.h"

// создание таблицы ключей
int create_page_key_table(book_table *table, page_key_table *key_table);

void open_sorted_key_table(book_table *table);

// сортировка таблицы ключей
void sort_key_table(page_key_table *key_table, int64_t *bubble_time_key, int64_t *qsort_time_key, int64_t elapsed_time);

// сравнение строк таблицы ключей
int compare_key_lines(const void *one, const void *two);

// сортировка пузырьком таблицы ключей
void bubble_sort_key_table(page_key_table *key_table);

// перестановка строк таблицы ключей
void swap_lines(page_key_table *key_table, short int line1, short int line2);

#endif