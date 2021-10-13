#include "addition.h"
#include "output.h"
#include "operations.h"

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

void add_matrices(ld **a, ld **b, csr_matrix *a_csr, csr_matrix *b_csr, ll *m_a, ll *n_a, ll *m_b, ll *n_b)
{
    if (a != NULL && b != NULL && *m_a == *m_b && *n_a == *n_b && *m_a > 0 && *n_a > 0)
    {
        printf("How do you want to add matrices? [Full (F) / CSR (C)]: ");
        char temp[20];
        scanf("%s", temp);
        if (strcmp(temp, "F") == 0)
        {
            ld **res_normal = add_normal_matrices(a, b, *m_a, *n_a);
            if (res_normal == NULL)
                printf("Can't add!\n");
            else
            {
                char temp[20];
                printf("Do you want to see the result? [Y / N]: ");
                scanf("%s", temp);
                if (strcmp(temp, "Y") == 0)
                    print_full_matr(res_normal, *m_a, *n_a);
            }
        }
        else if (strcmp(temp, "C") == 0)
        {
            csr_matrix res_csr = add_csr_matrices(a_csr, b_csr, *m_a);
            char temp[20];

            printf("Do you want to see the result in CSR form? [Y / N]: ");
            scanf("%s", temp);
            if (strcmp(temp, "Y") == 0)
                print_csr_matrix(&res_csr);

            printf("Do you want to see the full matrix? [Y / N]: ");
            scanf("%s", temp);
            if (strcmp(temp, "Y") == 0)
                print_full_from_csr(&res_csr, *m_a, *n_a);

            printf("Do you want to check the result? [Y / N]: ");
            scanf("%s", temp);
            if (strcmp(temp, "Y") == 0)
            {
                ld **res_normal = add_normal_matrices(a, b, *m_a, *n_a);
                csr_matrix res_csr_correct = transfer_full_to_csr(res_normal, m_a, n_a);
                if (csr_matrices_match(&res_csr_correct, &res_csr, *m_a) == YES)
                    printf("Matrices match!\n");
                else
                    printf("Matrices don't match!\n");
            }
        }
        else
            printf("Unknown command!\n");
    }
    else
        printf("Wrong input! Can't add matrices!\n");
}