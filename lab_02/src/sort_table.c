#include "sort_table.h"
#include "output.h"
#include "sort_key.h"

void swap_books(book *one, book *two)
{
    book temp = *one;
    *one = *two;
    *two = temp;
}

void bubble_sort_table(book_table *table)
{
    int n = table->quantity;
    for (int i = 0; i < n; i++)
        for (int j = n - 2; j >= i; j--)
            if ((table->data)[j].pages > (table->data)[j + 1].pages)
                swap_books((table->data) + j, (table->data) + j + 1);
}

void sort_table_key_hub(book_table *table)
{
    page_key_table key_table = { 0 };
    int rc = create_page_key_table(table, &key_table);

    if (rc != OK)
        printf("No books yet!\n");
    else
    {
        sort_key_table(&key_table, NULL, NULL, 0);
        print_table_by_key_table(table, &key_table);
    }
}

int compare_books(const void *one, const void *two)
{
    book *book1 = (book *)one;
    book *book2 = (book *)two;
    return (book1->pages - book2->pages);
}

void sort_table_full(book_table *table, int64_t *bubble_time_table, int64_t *qsort_time_table)
{
    struct timeval tv_start, tv_stop;

    if (table->quantity < 40)
        printf("No books yet!\n");
    else
    {
        printf("Choose sorting algorythm [simple/fast]: ");
        char a[MAX_FIELD_LEN + 1];
        if (scanf("%s", a) == 1)
        {
            if (strcmp(a, "simple") == 0)
            {
                gettimeofday(&tv_start, NULL);
                bubble_sort_table(table);
                gettimeofday(&tv_stop, NULL);

                if (bubble_time_table != NULL)
                    *bubble_time_table = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
                    (tv_stop.tv_usec - tv_start.tv_usec);
            }
            else if (strcmp(a, "fast") == 0)
            {
                gettimeofday(&tv_start, NULL);
                qsort(table->data, table->quantity, sizeof(book), compare_books);
                gettimeofday(&tv_stop, NULL);

                if (qsort_time_table != NULL)
                    *qsort_time_table = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
                    (tv_stop.tv_usec - tv_start.tv_usec);
            }
            else
                printf("No such algorithm!\n");
        }
        else
            printf("Input error!\n");
    }
}
