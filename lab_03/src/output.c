#include "output.h"

void print_full_matr(long double **a, long long m, long long n)
{
    for (long long i = 0; i < m; i++)
    {
        for (long long j = 0; j < n; j++)
            printf("%-5.2Lf\t", a[i][j]);
        printf("\n");
    }
}

void print_csr_matrix(csr_matrix *mtr)
{
    ll nz = mtr->nz;
    printf("nz = %-7lld\n", nz);
    printf("num\t");
    for (ll i = 0; i < nz; i++)
        printf("%-7lld\t", i);
    printf("\nval\t");
    for (ll i = 0; i < nz; i++)
        printf("%-5.2Lf\t", (mtr->a)[i]);
    printf("\nj  \t");
    for (ll i = 0; i < nz; i++)
        printf("%-7lld\t", (mtr->ja)[i]);
    printf("\ni  \t");
    ptr_list *cur = &(mtr->ia);
    do
    {
        printf("%lld\t", cur->i);
        cur = cur->next;
    } 
    while (cur != NULL);
    printf("\n");
}

void print_full_from_csr(csr_matrix *a, ll m, ll n)
{
    ptr_list *cur_a = &(a->ia);
    ll k = cur_a->i;

    for (ll i = 0; i < m; i++)
    {
        ll next_a = cur_a->next->i;
        for (ll j = 0; j < n; j++)
        {
            if (k >= next_a)
                printf("%-5.2f\t", 0.0);
            else if (a->ja[k] != j)
                printf("%-5.2f\t", 0.0);
            else
                printf("%-5.2Lf\t", a->a[k++]);
        }
        printf("\n");
        cur_a = cur_a->next;
    }
}