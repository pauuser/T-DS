#include "common.h"

ll count_non_zero(ld **a, ll m, ll n);

csr_matrix transfer_full_to_csr(ld **a, ll *m, ll *n);

int csr_matrices_match(csr_matrix *a, csr_matrix *b, ll m);