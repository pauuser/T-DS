#include "sort_key.h"
#include "output.h"

void sort_key_table(page_key_table *key_table, int64_t *bubble_time_key, int64_t *qsort_time_key, int64_t elapsed_time)
{
    printf("Choose sorting algorythm [simple/fast]: ");
    char a[MAX_FIELD_LEN + 1];
    if (scanf("%s", a) == 1)
    {
        struct timeval tv_start, tv_stop;
        if (strcmp(a, "simple") == 0)
        {
            gettimeofday(&tv_start, NULL);
            bubble_sort_key_table(key_table);
            gettimeofday(&tv_stop, NULL);
            if (bubble_time_key != NULL)
                *bubble_time_key = elapsed_time + (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
                (tv_stop.tv_usec - tv_start.tv_usec);
        }
        else if (strcmp(a, "fast") == 0)
        {
            gettimeofday(&tv_start, NULL);
            qsort(key_table->pages, key_table->n, sizeof(short) * 3, compare_key_lines);
            gettimeofday(&tv_stop, NULL);
            if (qsort_time_key != NULL)
                *qsort_time_key = elapsed_time + (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
                (tv_stop.tv_usec - tv_start.tv_usec);
        }
        else
            printf("No such algorithm!\n");
    }
    else
        printf("Input error!\n");
}

int compare_key_lines(const void *one, const void *two)
{
    short *line1 = (short *)one;
    short *line2 = (short *)two;
    return (*(line1 + 2) - *(line2 + 2));
}

void bubble_sort_key_table(page_key_table *key_table)
{
    int n = key_table->n;
    for (int i = 0; i < n; i++)
        for (int j = n - 2; j >= i; j--)
            if ((key_table->pages)[j][2] > (key_table->pages)[j + 1][2])
                swap_lines(key_table, j, j + 1);
}

void swap_lines(page_key_table *key_table, short int line1, short int line2)
{
    short int i_new = (key_table->pages)[line1][1];
    short int pages = (key_table->pages)[line1][2];

    (key_table->pages)[line1][1] = (key_table->pages)[line2][1];
    (key_table->pages)[line1][2] = (key_table->pages)[line2][2];

    (key_table->pages)[line2][1] = i_new;
    (key_table->pages)[line2][2] = pages;
}

int create_page_key_table(book_table *table, page_key_table *key_table)
{
    int ret_code = OK;

    if (table->quantity == 0)
        ret_code = NO_BOOKS;
    else
    {
        key_table->n = table->quantity;
        for (int i = 0; i < key_table->n; i++)
        {
            (key_table->pages)[i][1] = i;
            (key_table->pages)[i][0] = i;
            (key_table->pages)[i][2] = ((table->data) +  i)->pages;
        }
    }

    return ret_code;    
}

void open_sorted_key_table(book_table *table)
{
    page_key_table key_table = { 0 };

    int rc = create_page_key_table(table, &key_table);

    if (rc != OK)
        printf("No books yet!\n");
    else
    {
        printf("The unsorted key table:\n");
        print_key_table(&key_table);

        sort_key_table(&key_table, NULL, NULL, 0);
        printf("The sorted key table:\n");
        print_key_table(&key_table);
    }
}