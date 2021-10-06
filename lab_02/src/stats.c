#include "stats.h"
#include "sort_table.h"
#include "output.h"
#include "sort_key.h"

void output_sort_stats(book_table table)
{
    struct timeval tv_start, tv_stop;
    int64_t key_creation_time = 0;

    int64_t bubble_time_key = 0, qsort_time_key = 0;
    int64_t bubble_time_table = 0, qsort_time_table = 0;

    book_table table_copy = table;

    page_key_table key_table = { 0 };

    gettimeofday(&tv_start, NULL);
    int rc = create_page_key_table(&table, &key_table);
    gettimeofday(&tv_stop, NULL);
    key_creation_time += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
    (tv_stop.tv_usec - tv_start.tv_usec);

    if (rc == OK)
    {
        page_key_table key_table_copy = key_table;

        printf("MEASURING KEY TABLE...\n");
        printf("Please type simple:\n");
        sort_key_table(&key_table, &bubble_time_key, &qsort_time_key, key_creation_time);
        printf("Please type fast:\n");
        sort_key_table(&key_table_copy, &bubble_time_key, &qsort_time_key, key_creation_time);

        printf("MEASURING FULL TABLE...\n");
        printf("Please type simple:\n");
        sort_table_full(&table, &bubble_time_table, &qsort_time_table);
        printf("Please type fast:\n");
        sort_table_full(&table_copy, &bubble_time_table, &qsort_time_table);

        printf("Efficiency results:\n");
        printf("Case       \t\tTable\t\tKey table\n");
        printf("Bubble     \t\t%lld us\t\t%lld us\n", (long long)bubble_time_table, (long long)bubble_time_key);
        printf("Qsort      \t\t%lld us\t\t%lld us\n", (long long)qsort_time_table, (long long)qsort_time_key);
        if (qsort_time_table == 0 || qsort_time_key == 0)
            printf("Not enough data for comparison yet!\n");
        else
            printf("Qsort is   \t\t%lldx faster\t\n", (long long)(qsort_time_table / bubble_time_table));
    }
    else
        printf("No data yet!\n");
}

void output_efficiency_results(book_table table)
{
    struct timeval tv_start, tv_stop;
    int64_t key_creation_time = 0;

    int64_t bubble_time_key = 0, qsort_time_key = 0;
    int64_t bubble_time_table = 0, qsort_time_table = 0;
    int table_storage = 0, key_storage = 0;

    book_table table_copy = table;

    page_key_table key_table = { 0 };

    gettimeofday(&tv_start, NULL);
    int rc = create_page_key_table(&table, &key_table);
    gettimeofday(&tv_stop, NULL);
    key_creation_time += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
    (tv_stop.tv_usec - tv_start.tv_usec);

    if (rc == OK)
    {
        page_key_table key_table_copy = key_table;

        printf("MEASURING KEY TABLE...\n");
        key_storage = sizeof(key_table.pages[0]) * key_table.n;

        printf("Please type simple:\n");
        sort_key_table(&key_table, &bubble_time_key, &qsort_time_key, key_creation_time);

        printf("Please type fast:\n");
        sort_key_table(&key_table_copy, &bubble_time_key, &qsort_time_key, key_creation_time);

        printf("MEASURING FULL TABLE...\n");
        table_storage = sizeof(table.quantity) + sizeof(table.data[0]) * table.quantity;

        printf("Please type simple:\n");
        sort_table_full(&table, &bubble_time_table, &qsort_time_table);

        printf("Please type fast:\n");
        sort_table_full(&table_copy, &bubble_time_table, &qsort_time_table);

        printf("EFFICIENCY TEST RESULTS:\n");
        printf("Case   \t\tTable\t\tKey table\n");
        printf("Bubble \t\t%lld us\t\t%lld us\n", (long long)bubble_time_table, (long long)bubble_time_key);
        printf("Qsort  \t\t%lld us\t\t%lld us\n", (long long)qsort_time_table, (long long)qsort_time_key);
        printf("Storage\t\t%d\t\t%d\n", table_storage, key_storage);
    }
    else
        printf("No data yet!\n");
}
