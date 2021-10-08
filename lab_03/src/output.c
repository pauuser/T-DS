#include "output.h"

void print_full_matr(long double **a, long long m, long long n)
{
    for (long long i = 0; i < m; i++)
    {
        for (long long j = 0; j < n; j++)
            printf("%Lf ", a[i][j]);
        printf("\n");
    }
}

void print_csr_matrix(csr_matrix *mtr)
{
    ll nz = mtr->nz;
    for (ll i = 0; i < nz; i++)
        printf("%.2Lf\t", (mtr->a)[i]);
    printf("\n");
    for (ll i = 0; i < nz; i++)
        printf("%lld\t", (mtr->ja)[i]);
    printf("\n");
    ptr_list *cur = &(mtr->ia);
    while (cur->next != NULL)
    {
        printf("%lld\t", cur->i);
        cur = cur->next;
    }
}