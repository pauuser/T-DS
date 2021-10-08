#include "input.h"

long double **create_full_matrix(long long *m, long long *n)
{
    printf("Input rows number: m = ");
    scanf("%lld", m);

    printf("Input columns number : n = ");
    scanf("%lld", n);

    long double **a = NULL;

    if (*n < 1 || *m < 1)
    {
        // РЕШИТЬ ПРОБЛЕМУ С ЗАЦИКЛИВАНИЕМ!
        printf("Wrong input!\n");
    }
    else
    {
        printf("Choose the input type [file / keyboard / non-zero]: ");
        char type[20];
        scanf("%s", type);
        if (strcmp(type, "file") == 0)
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
        else if (strcmp(type, "keyboard") == 0)
            a = fill_init_matrix(stdin, *m, *n);
        else if (strcmp(type, "non-zero") == 0)
            a = full_matrix_non_zero(*m, *n);
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
        long long n = 0;
        long long row = 1;
        long long column = 1;
        if (scanf("%lld", &n) == 1 && n > 0 && n <= m * n)
        {
            for (long long i = 0; i < n && row >= 0 && column >= 0; i++)
            {
                row = -1;
                printf("row i = ");
                scanf("%lld", &row);

                column = -1;
                printf("column j = ");
                scanf("%lld", &column);

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
                        printf("Wrong input!\n");
                    }
                    else
                        a[row][column] = elem;
                }
            }
        }
        else
            printf("Wrong input!\n");
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
        free(a);
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

void free_matrix(long long **a, long long m)
{
    for (int i = 0; i < m; i++)
        free(a[i]);
    free(a);
}