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
            ll first_zero = -1;
            for (ll j = 0; j < *n; j++)
            {
                if (a[i][j] != 0)
                {
                    mtr.a[nz_i] = a[i][j];
                    mtr.ja[nz_i++] = j;
                    if (first_zero == -1)
                        first_zero = nz_i - 1;
                }
            }
            cur_list->i = first_zero;
            cur_list->next = calloc(1, sizeof(ptr_list));
            cur_list = cur_list->next;
        }
    }

    return mtr;
}