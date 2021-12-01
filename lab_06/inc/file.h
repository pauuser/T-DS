#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

// Функция определения длины файла
int file_len(FILE *f);

// Функция поиска в файле
int file_search(FILE *f, int num, int *comp_number);

// Функция определения членства числа в массиве
int num_in_mas(int *a, int n, int num);

// Функция чтения чисел в массив из файла
int *read_mas_from_file(FILE *f, int *number);