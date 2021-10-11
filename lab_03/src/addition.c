#include "addition.h"
#include "output.h"

ld **add_normal_matrices(ld **a, ld **b, ll m, ll n)
{
    ld **res = init_matrix(m, n);
    for (ll i = 0; i < m; i++)
        for (ll j = 0; j < n; j++)
            res[i][j] = a[i][j] + b[i][j];
    
    return res;
}

csr_matrix add_csr_matrices(csr_matrix *a, csr_matrix *b, ll m)
{
    csr_matrix res;
    ll nz = 0;
    res.a = calloc(a->nz + b->nz, sizeof(ld));
    res.ja = calloc(a->nz + b->nz, sizeof(ll));
    res.ia.i = 0;
    res.ia.next = NULL;

    ptr_list *cur_list = &(res.ia);

    ptr_list *cur_a = &(a->ia);
    ptr_list *cur_b = &(b->ia);

    ll k = cur_a->i;
    ll p = cur_b->i;

    for (ll t = 0; t < m; t++)
    {
        cur_list->i = nz;

        ll next_a = cur_a->next->i;
        ll next_b = cur_b->next->i;

        while (cur_a->next != NULL && cur_b->next != NULL && (k < next_a || p < next_b))
        {
            if (k < next_a && p < next_b && a->ja[k] == b->ja[p])
            {
                res.a[nz] = a->a[k] + b->a[p];
                res.ja[nz] = a->ja[k];
                k++;
                p++;
            }
            else if (k < next_a && (p >= next_b || a->ja[k] < b->ja[p]))
            {
                res.a[nz] = a->a[k];
                res.ja[nz] = a->ja[k];
                k++;
            }
            else
            {
                res.a[nz] = b->a[p];
                res.ja[nz] = b->ja[p];
                p++;
            }
            nz++;
        }
        cur_list->next = calloc(1, sizeof(ptr_list));
        cur_list = cur_list->next;
        cur_a = cur_a->next;
        cur_b = cur_b->next;
    }

    cur_list->i = nz;
    cur_list->next = NULL;
    res.nz = nz;

    return res;
}