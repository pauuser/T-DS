#include "../inc/effec.h"

/*
Функция измерения времени в тактах
*/
int64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

void search_with_time(hash_t **table, int max_comp)
{
    int comp_number = 0;
    int to_search = 0;

    int64_t s1, e1;
    int sum;

    if (table == NULL || *table == NULL)
        printf("No table!\n");
    else
    {
        printf("Input number to search: ");
        if (scanf("%d", &to_search) == 1)
        {
            int res = 0;
            for (int i = 0; i < 10000; i++)
            {
                s1 = tick();
                res = hash_search(*table, to_search, &comp_number);
                e1 = tick();
                sum += (int)(e1 - s1);
            }

            if (res == 1)
                printf("Found!\n");
            else
                printf("Not found!\n");

            printf("Comparisons number : %d\n", comp_number);

            printf("Time : %d tacts\n", sum / 10000);
            sum = 0;

            if (comp_number > max_comp)
            {
                printf("IMPORTANT! Table will be restructured!\n");
                
                s1 = tick();
                hash_restructure(table);
                e1 = tick();

                printf("New table:\n");
                hash_read(*table);

                printf("Restructure time : %d tacts\n", (int)(e1 - s1));
                
                printf("New search:\n");
                comp_number = 0;

                for (int i = 0; i < 10000; i++)
                {
                    s1 = tick();
                    res = hash_search(*table, to_search, &comp_number);
                    e1 = tick();
                    sum += (int)(e1 - s1);
                }

                if (res == 1)
                    printf("Found!\n");
                else
                    printf("Not found!\n");

                printf("Comparisons number : %d\n", comp_number);
                printf("Time : %d tacts", sum / 10000);
            }
        }
        else
        {
            printf("Wrong input!\n");
            clean_stdin();
        }
    }
}

void measure_time()
{
    printf("=========================== SEARCH TIME ===========================\n");
    printf(" \tBST \t\tAVL \t\tHASH*\t\tFILE\n");
    printf("N\tTIME\tCOMP\tTIME\tCOMP\tTIME\tCOMP\tTIME\tCOMP\n");
    measure_time_10();
    printf("* - hash tables have less then 10%% of collisions.\n");
}

void measure_time_10()
{
    char *files[5] = { "./data/10.txt", "./data/50.txt", "./data/100.txt", "./data/500.txt", "./data/1000.txt" };
    for (int k = 0; k < 5; k++)
    {
        int n = 0;
        FILE *f = fopen(files[k], "r");
        int *a = read_mas_from_file(f, &n);

        int64_t s1, e1;
        int sum = 0, comp_number = 0, all_comp = 0;

        bst_node_t *bst = NULL;

        avl_node_t *avl = NULL;

        hash_t *table = NULL;

        read_file_to_bst(&bst, f);
        avl_create_from_bst(bst, &avl);
        read_file_to_hash(&table, f);

        while (hash_count_collisions(table) > n / 100 * 10)
        {
            hash_restructure(&table);
        }

        printf("%d\t", n);

        sum = 0;
        all_comp = 0;
        comp_number = 0;

        int sum_n = 0;
        int comp_n = 0;

        // BST
        for (int k = 0; k < 10000; k++)
        {
            sum = 0;
            all_comp = 0;
            comp_number = 0;
            for (int i = 0; i < n; i++)
            {
                s1 = tick();
                bst_search_node(bst, a[i], &comp_number);
                e1 = tick();

                all_comp += comp_number;
                comp_number = 0;

                sum += (int)(e1 - s1);
            }
            sum_n += sum / n;
            comp_n += all_comp / n;
        }
        printf("%d\t%d\t", sum_n / 10000, comp_n / 10000);
        sum = 0;
        all_comp = 0;
        comp_number = 0;
        sum_n = 0;
        comp_n = 0;

        // AVL
        for (int k = 0; k < 10000; k++)
        {
            sum = 0;
            all_comp = 0;
            comp_number = 0;
            for (int i = 0; i < n; i++)
            {
                s1 = tick();
                avl_search_node(avl, a[i], &comp_number);
                e1 = tick();

                all_comp += comp_number;
                comp_number = 0;

                sum += (int)(e1 - s1);
            }
            sum_n += sum / n;
            comp_n += all_comp / n;
        }
        printf("%d\t%d\t", sum_n / 10000, comp_n / 10000);
        sum = 0;
        all_comp = 0;
        comp_number = 0;
        sum_n = 0;
        comp_n = 0;

        // HASH
        for (int k = 0; k < 100000; k++)
        {
            sum = 0;
            all_comp = 0;
            comp_number = 0;
            for (int i = 0; i < n; i++)
            {
                s1 = tick();
                hash_search(table, a[i], &comp_number);
                e1 = tick();

                all_comp += comp_number;
                comp_number = 0;

                sum += (int)(e1 - s1);
            }
            sum_n += sum / n;
            comp_n += all_comp / n;
        }
        printf("%d\t%d\t", sum_n / 100000, comp_n / 100000);
        sum = 0;
        all_comp = 0;
        comp_number = 0;
        sum_n = 0;
        comp_n = 0;

        // FILE
        for (int i = 0; i < n; i++)
        {
            s1 = tick();
            file_search(f, a[i], &comp_number);
            e1 = tick();

            all_comp += comp_number;
            comp_number = 0;

            sum += (int)(e1 - s1);
        }
        printf("%d\t%d\t\n", sum / n, all_comp / n);
        sum = 0;
        all_comp = 0;
        comp_number = 0;

        free(a);
        a = NULL;

        bst_free_tree(bst);
        avl_free_tree(avl);
        hash_free(table);
        fclose(f);
    }
}

void measure_memory()
{
    printf("========================== MEMORY USE =============================\n");
    printf("N\tBST \tAVL \tHASH*\n");

    char *files[5] = { "./data/10.txt", "./data/50.txt", "./data/100.txt", "./data/500.txt", "./data/1000.txt" };

    for (int k = 0; k < 5; k++)
    {
        FILE *f = fopen(files[k], "r");
        int n = file_len(f);

        bst_node_t *bst = NULL;

        avl_node_t *avl = NULL;

        hash_t *table = NULL;

        read_file_to_bst(&bst, f);
        avl_create_from_bst(bst, &avl);
        read_file_to_hash(&table, f);

        while (hash_count_collisions(table) > n / 100 * 10)
        {
            hash_restructure(&table);
        }

        printf("%d\t", n);
        printf("%ld\t", n * sizeof(bst_node_t));
        printf("%ld\t", n * sizeof(avl_node_t));
        printf("%ld\t\n", table->size * sizeof(node_t *) + n * sizeof(node_t));

        bst_free_tree(bst);
        avl_free_tree(avl);
        hash_free(table);
        
        fclose(f);
    }
    printf("* - hash tables have less then 10%% of collisions.\n");
}

void collision_comparison()
{
    printf("===================== COLLISION COMPARISON ========================\n");
    printf("LEVEL\tTIME \tCOMP\tSTORAGE\n");

    int n = 0;
    FILE *f = fopen("./data/1000.txt", "r");
    int *a = read_mas_from_file(f, &n);

    hash_t *table = NULL;
    read_file_to_hash(&table, f);

    size_t s1, e1;

    int sum = 0, comp_number = 0, all_comp = 0;
    int sum_n = 0;
    int comp_n = 0;

    int restructure_time = 0;
    int restructure_n = 0;

    while (hash_count_collisions(table) > n / 100 * 2)
    {
        for (int k = 0; k < 1000; k++)
        {
            sum = 0;
            all_comp = 0;
            comp_number = 0;
            for (int i = 0; i < n; i++)
            {
                s1 = tick();
                hash_search(table, a[i], &comp_number);
                e1 = tick();

                all_comp += comp_number;
                comp_number = 0;

                sum += (int)(e1 - s1);
            }
            sum_n += sum / n;
            comp_n += all_comp / n;
        }
        printf("%d%%\t%d\t%d\t%ld\n", (int)((double)hash_count_collisions(table) / n * 100.0), 
                                       sum_n / 1000, comp_n / 1000,
                                       table->size * sizeof(node_t *) + n * sizeof(node_t));

        s1 = tick();
        hash_restructure(&table);
        e1 = tick();

        restructure_time += (int)(e1 - s1);
        restructure_n += 1;

        sum_n = 0;
        comp_n = 0;
    }
    printf("Average restructure time = %d\n", restructure_time / restructure_n);
    hash_free(table);

    fclose(f);
}