#include "input.h"
#include "operations.h"
#include "random.h"

long double **create_full_matrix(long long *m, long long *n)
{
    printf("Input rows number: m = ");
    if (scanf("%lld", m) != 1)
        read_needless_syms();

    printf("Input columns number : n = ");
    if (scanf("%lld", n) != 1)
        read_needless_syms();

    long double **a = NULL;

    if (*n < 1 || *m < 1)
    {
        printf("Wrong input!\n");
    }
    else
    {
        printf("Choose the input type [file (F) / keyboard (K) / non-zeroes (N) / random (R)]: ");
        char type[20];
        scanf("%s", type);
        if (strcmp(type, "F") == 0)
        {
            printf("Input file name: ");
            char filename[20];
            scanf("%s", filename);
            FILE *f = fopen(filename, "r");
            if (f == NULL)
                printf("No file!\n");
            else
            {
                a = fill_init_matrix(f, *m, *n);
                fclose(f);
            }
        }
        else if (strcmp(type, "K") == 0)
            a = fill_init_matrix(stdin, *m, *n);
        else if (strcmp(type, "N") == 0)
            a = full_matrix_non_zero(*m, *n);
        else if (strcmp(type, "R") == 0)
        {
            printf("Input percentage of non-zero elements:\n");
            int num, rc;
            do
            {
                rc = scanf("%d", &num);
                if (rc < 0 || num > 100 || num < 1)
                {
                    printf("Wrong input!");
                    read_needless_syms();
                    rc = -1;
                }
            } 
            while (rc != 1);
            
            a = generate_rand_matrix(*m, *n, num);
        }
        else
            printf("Wrong input!\n");
    }
    return a;
}

long double **full_matrix_non_zero(long long m, long long n)
{
    long double **a = init_matrix(m, n);
    if (a != NULL)
    {
        printf("How many non-zero elements do you want to add to the matrix?\n");
        printf("Answer: ");
        long long n_nz = 0;
        long long row = 1;
        long long column = 1;
        int ch;
        if ((ch = scanf("%lld", &n_nz)) == 1 && n_nz > 0 && n_nz <= m * n)
        {
            for (long long i = 0; i < n_nz && row >= 0 && column >= 0; i++)
            {
                row = -1;
                printf("row i = ");
                if (scanf("%lld", &row) != 1)
                    read_needless_syms();

                column = -1;
                printf("column j = ");
                if (scanf("%lld", &column) != 1)
                    read_needless_syms();

                if (row < 0 || column < 0 || row >= m || column >= n)
                {
                    printf("Wrong input!\n");
                }
                else
                {
                    long double elem = 0.0;
                    printf("Input element: ");
                    if (scanf("%Lf", &elem) != 1)
                    {
                        read_needless_syms();
                        printf("Wrong input!\n");
                    }
                    else
                        a[row][column] = elem;
                }
            }
        }
        else
        {
            if (ch == 0)
                read_needless_syms();
            printf("Wrong input!\n");
        }
    }
    return a;
}

long double **fill_init_matrix(FILE *f, long long m, long long n)
{
    long double **a = init_matrix(m, n);
    short error = NO;
    for (long long i = 0; i < m && error == NO; i++)
        for (long long j = 0; j < n && error == NO; j++)
        {
            if (fscanf(f, "%Lf", a[i] + j) != 1)
                error = YES;
        }
    if (error == YES)
    {
        read_needless_syms();
        free_matrix(a, m);
        a = NULL;
    }
    return a;
}

long double **init_matrix(long long m, long long n)
{
    long double **a = calloc(m, sizeof(long double *));
    if (a != NULL)
        for (long long i = 0; i < m && a != NULL; i++)
        {
            a[i] = calloc(n, sizeof(long double));
            if (a[i] == NULL)
            {
                free(a);
                a = NULL;
            }
        }
    
    return a;
}

void free_matrix(ld **a, long long m)
{
    for (int i = 0; i < m; i++)
        free(a[i]);
    free(a);
}

void free_csr_matrix(csr_matrix *a)
{
    free(a->a);
    free(a->ja);

    ptr_list *cur = (a->ia.next);
    while (cur != NULL)
    {
        ptr_list *save = cur->next;
        free(cur);
        cur = save;
    } 
}

void read_needless_syms()
{
    char temp[20];
    scanf("%s", temp);
}

void init_csr_matrix(csr_matrix *a_csr)
{
    a_csr->a = NULL;
    a_csr->nz = 0; 
    a_csr->ja = NULL;
    a_csr->ia.i = 0;
    a_csr->ia.next = NULL;
}

void input_matrices(ld ***a, ld ***b, csr_matrix *a_csr, csr_matrix *b_csr, ll *m_a, ll *n_a, ll *m_b, ll *n_b)
{
    if (*a != NULL && *b != NULL)
    {
        printf("You alreay have matrices! Do you want to reinput them? [Y / N]: ");
        char temp[20];
        scanf("%s", temp);
        if (strcmp(temp, "Y") == 0)
        {
            free_matrix(*a, *m_a);
            free_matrix(*b, *m_b);
            free_csr_matrix(a_csr);
            free_csr_matrix(b_csr);
            *a = NULL;
            *b = NULL;
        }
    }
    if (*a == NULL)
    {
        printf("Input the first matrix: \n");
        *a = create_full_matrix(m_a, n_a);
    }
    if (*a == NULL)
    {
        printf("The first matrix was not created! You must try again!\n");
        return;
    }
    if (*b == NULL)
    {
        printf("Input the second matrix: \n");
        *b = create_full_matrix(m_b, n_b);
    }
    if (*b == NULL)
    {
        printf("The second matrix was not created! You must try again!\n");
        return;
    }
    if (a != NULL && b != NULL)
    {
        *a_csr = transfer_full_to_csr(*a, m_a, n_a);
        *b_csr = transfer_full_to_csr(*b, m_b, n_b);

        printf("Do you want to see the input?\n");
        printf("Full matrix A [Y / N]: ");
        char temp[20];
        scanf("%s", temp);
        if (strcmp(temp, "Y") == 0)
            print_full_matr(*a, *m_a, *n_a);
        
        printf("CSR matrix A [Y / N]: ");
        scanf("%s", temp);
        if (strcmp(temp, "Y") == 0)
            print_csr_matrix(a_csr);
        
        printf("Full matrix B [Y / N]: ");
        scanf("%s", temp);
        if (strcmp(temp, "Y") == 0)
            print_full_matr(*b, *m_b, *n_b);
        
        printf("CSR matrix B [Y / N]: ");
        scanf("%s", temp);
        if (strcmp(temp, "Y") == 0)
            print_csr_matrix(b_csr);
    }
}