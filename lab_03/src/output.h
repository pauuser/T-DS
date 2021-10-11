#ifndef _H_OUTPUT_
#define _H_OUTPUT_

#include "common.h"

void print_full_matr(long double **a, long long m, long long n);

void print_csr_matrix(csr_matrix *mtr);

void print_full_from_csr(csr_matrix *a, ll m, ll n);

#endif