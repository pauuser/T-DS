#include "../inc/file.h"

int file_len(FILE *f)
{
    int len = 0;
    int n = 0, rc = 0;

    while (f != NULL && !feof(f) && (rc = fscanf(f, "%d", &n)))
        len += 1;
    
    if ((rc == 0 && len > 0) || f == NULL)
        len = 0;
    else
    {
        rewind(f);
        
        int n = 0, read = 0;
        int *a = malloc(len * sizeof(int));

        while (f != NULL && !feof(f) && (rc = fscanf(f, "%d", &read)))
        {
            if (num_in_mas(a, n, read) == 0)
            {
                n++;
                a[n - 1] = read;
            }
        }
        rewind(f);
        len = n;
        free(a);
    }
    return len;
}

int file_search(FILE *f, int num, int *comp_number)
{
    int found = 0;
    if (f == NULL)
        printf("No file yet!\n");
    else
    {
        rewind(f);
        *comp_number = 0;

        int n = 0, stop = 0;

        while (stop == 0 && !feof(f) && fscanf(f, "%d", &n) == 1)
        {
            *comp_number += 1;
            if (n == num)
            {
                stop = 1;
                found = 1;
            }
        }
    }

    return found;
}

int num_in_mas(int *a, int n, int num)
{
    int in_mas = 0;

    for (int i = 0; i < n; i++)
    {
        if (a[i] == num)
            in_mas = 1;
    }

    return in_mas;
}

int *read_mas_from_file(FILE *f, int *number)
{
    int n = file_len(f), rc = 0, read = 0;
    rewind(f);
    int *a = malloc(n * sizeof(int));
    int i = 0;

    while (f != NULL && !feof(f) && (rc = fscanf(f, "%d", &read)))
        a[i++] = read;
    
    *number = n;

    rewind(f);

    return a;
}