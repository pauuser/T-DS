#ifndef _H_INPUT_
#define _H_INPUT_

#include "common.h"
#include "output.h"

long double **create_full_matrix(long long *m, long long *n);

long double **full_matrix_non_zero(long long m, long long n);

long double **fill_init_matrix(FILE *f, long long m, long long n);

long double **init_matrix(long long m, long long n);

void free_matrix(long long **a, long long m);

#endif