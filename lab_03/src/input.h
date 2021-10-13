#ifndef _H_INPUT_
#define _H_INPUT_

#include "common.h"
#include "output.h"

long double **create_full_matrix(long long *m, long long *n);

long double **full_matrix_non_zero(long long m, long long n);

long double **fill_init_matrix(FILE *f, long long m, long long n);

long double **init_matrix(long long m, long long n);

void free_matrix(ld **a, long long m);

void free_csr_matrix(csr_matrix *a);

void read_needless_syms();

void init_csr_matrix(csr_matrix *a);

void input_matrices(ld ***a, ld ***b, csr_matrix *a_csr, csr_matrix *b_csr, ll *m_a, ll *n_a, ll *m_b, ll *n_b);

#endif