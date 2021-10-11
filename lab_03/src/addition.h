#ifndef _H_ADDITION_
#define _H_ADDITION_

#include "common.h"
#include "input.h"

ld **add_normal_matrices(ld **a, ld **b, ll m, ll n);

csr_matrix add_csr_matrices(csr_matrix *a, csr_matrix *b, ll m);

#endif