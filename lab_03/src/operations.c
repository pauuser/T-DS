#include "operations.h"

ll count_non_zero(ld **a, ll m, ll n)
{
    int nz = 0;
    for (ll i = 0; i < m; i++)
        for (ll j = 0; j < n; j++)
            if (a[i][j] != 0)
                nz += 1;
    
    return nz;
}

csr_matrix transfer_full_to_csr(ld **a, ll *m, ll *n)
{
    csr_matrix mtr;
    ll nz = count_non_zero(a, *m, *n);
    mtr.nz = nz;
    mtr.a = calloc(nz, sizeof(ld));
    mtr.ja = calloc(nz, sizeof(ll));
    mtr.ia.i = -1;
    mtr.ia.next = NULL;

    ptr_list *cur_list = &(mtr.ia);

    ll nz_i = 0;

    if (mtr.a != NULL && mtr.ja != NULL)
    {
        for (ll i = 0; i < *m; i++)
        {
            cur_list->i = nz_i;
            for (ll j = 0; j < *n; j++)
            {
                if (a[i][j] != 0)
                {
                    mtr.a[nz_i] = a[i][j];
                    mtr.ja[nz_i++] = j;
                }
            }
            cur_list->next = calloc(1, sizeof(ptr_list));
            cur_list = cur_list->next;
        }
        cur_list->i = nz_i;
        cur_list->next = NULL;
    }
    return mtr;
}

int csr_matrices_match(csr_matrix *a, csr_matrix *b, ll m)
{
    int val = YES;
    if (a->nz != b->nz)
        val = NO;
    for (ll i = 0; i < a->nz && val == YES; i++)
    {
        if ((a->a)[i] != (b->a)[i])
            val = NO;
        if (a->ja[i] != (b->ja[i]))
            val = NO;
    }
    ptr_list *one = &(a->ia);
    ptr_list *two = &(b->ia);
    for (ll i = 0; i < m && val == YES; i++)
    {
        if (one->i != two->i)
            val = NO;
        one = one->next;
        two = two->next;
    }

    return val;
}