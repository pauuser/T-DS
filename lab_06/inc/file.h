#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

int file_len(FILE *f);

int file_search(FILE *f, int num, int *comp_number);

int num_in_mas(int *a, int n, int num);

int *read_mas_from_file(FILE *f, int *number);