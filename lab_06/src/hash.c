#include "../inc/hash.h"

int hash_function(int key, int m)
{
    return (abs(key) % m);
}

hash_t *hash_create(int size)
{
    hash_t *table = calloc(1, sizeof(hash_t));

    if (table != NULL)
    {
        table->size = size;
        table->array = calloc(size, sizeof(node_t *));

        if (table->array == NULL)
        {
            free(table);
            table = NULL;
        }
    }

    return table;
}

void hash_free(hash_t *table)
{
    if (table != NULL)
    {
        for (int i = 0; i < table->size; i++)
        {
            node_t *cur_node = table->array[i];

            while (cur_node != NULL)
            {
                node_t *to_delete = cur_node;
                cur_node = cur_node->next;
                free(to_delete);
            }
        }
        free(table);
    }
}

node_t *create_node(int num)
{
    node_t *node = malloc(sizeof(node_t));

    if (node != NULL)
    {
        node->data = num;
        node->next = NULL;
    }

    return node;
}

void hash_add(hash_t *table, int num)
{
    //printf("%d\n", num);
    if (table == NULL || table->size < 1 || table->array == NULL)
        printf("No table yet!\n");
    else
    {
        // ячейка массива, куда вставлять
        node_t *to_ins = table->array[hash_function(num, table->size)];

        if (to_ins == NULL)
        {
            table->array[hash_function(num, table->size)] = create_node(num);
            //printf("Success!\n");
        }
        else
        {
            int exists = 0;
            if (to_ins->data == num)
                    exists = 1;

            while(to_ins->next != NULL)
            {
                if (to_ins->data == num)
                    exists = 1;
                to_ins = to_ins->next;
            }

            if (exists == 0 && to_ins && to_ins->data != num)
            {
                to_ins->next = create_node(num);
                /*
                if (to_ins->next != NULL)
                    printf("Success!\n");
                else
                    printf("No memory!\n");
                */
            }
            /*
            else
                printf("This element already exists!\n", num);
            */
        }
    }
}

void hash_delete(hash_t *table, int num)
{
    if (table == NULL)
        printf("No table!\n");
    else
    {
        int stop = 0;
        node_t *cur = (table->array)[hash_function(num, table->size)];

        if (cur != NULL && cur->data == num)
        {
            (table->array)[hash_function(num, table->size)] = cur->next;
            free(cur);
            stop = 1;
        }

        while (cur && cur->next && stop == 0)
        {
            if (cur->next->data == num)
            {
                node_t *to_delete = cur->next;
                cur->next = to_delete->next;
                free(to_delete);

                stop = 1;
            }
            cur = cur->next;
        }

        if (stop == 0)
            printf("No such element!\n");
        else
            printf("Success!\n");
    }
}

void hash_restructure(hash_t **table)
{
    if (!table || !(*table) || (*table)->size < 1)
        printf("No table yet!\n");
    else
    {
        int tried = 0;
        int initial_collisions = hash_count_collisions(*table);

        do
        {
            tried += 1;

            int new_size = closest_prime((*table)->size + (*table)->size / 6);

            hash_t *new = hash_create(new_size);

            for (int i = 0; i < (*table)->size; i++)
            {
                node_t *cur_node = (*table)->array[i];

                while (cur_node != NULL)
                {
                    node_t *to_free = cur_node;
                    hash_add(new, cur_node->data);
                    cur_node = cur_node->next;

                    free(to_free);
                }
            }
            free(*table);
            *table = new;
        }
        while (hash_count_collisions(*table) >= initial_collisions);
    }
}

int hash_search(hash_t *table, int num, int *comp_number)
{
    int found = 0;
    *comp_number = 0;

    if (table == NULL)
        printf("No table!\n");
    else
    {
        int stop = 0;
        node_t *cur = (table->array)[hash_function(num, table->size)];

        while (cur && stop == 0)
        {
            *comp_number += 1;
            if (cur->data == num)
            {
                found = 1;
                stop = 1;
            }
            cur = cur->next;
        }
    }

    return found;
}

void hash_read(hash_t *table)
{
    if (table == NULL)
        printf("No table!\n");
    else
    {
        printf("index\tdata\n");
        for (int i = 0; i < table->size; i++)
        {
            node_t *cur = (table->array)[i];
            printf("%d\t", i);
            list_read(cur);
            printf("\n");
        }
        int collisions = hash_count_collisions(table);
        printf("Number of collisions: %d\n", collisions);
    }
}

void list_read(node_t *start)
{
    while (start != NULL)
    {
        printf("-> %d ", start->data);
        start = start->next;
    }
}

int is_prime(int n)
{
    int prime = 1;

    if (n % 2 != 0 && n > 2)
    {
        for (int i = 3; i < n / 2 + 1 && prime == 1; i++)
            if (n % i == 0)
                prime = 0;
    }
    else
        prime = 0;
    
    return prime;
}

int closest_prime(int n)
{
    int closest = n;

    if (is_prime(n) != 1)
    {
        while (is_prime(closest) == 0)
            closest += 1;
    }

    return closest;        
}

int read_file_to_hash(hash_t **table, FILE *f)
{
    int rc = OK;
    int n = file_len(f);
    hash_free(*table);

    if (n < 1)
        rc = NO_FILE;
    else
    {
        rewind(f);

        int size = closest_prime((int)(0.72 * (double)n));

        *table = hash_create(size);

        int num = 0;
        while (!feof(f) && fscanf(f, "%d", &num) == 1)
        {
            hash_add(*table, num);
        }

        if (*table != NULL)
            rc = OK;
        else
            rc = NO_MEMORY;
        
        rewind(f);
    }

    return rc;
}

int hash_count_collisions(hash_t *table)
{
    int collisions = 0;
    for (int i = 0; i < table->size; i++)
    {
        node_t *start = (table->array)[i];
        
        while (start != NULL)
        {
            start = start->next;

            if (start != NULL)
                collisions++;
        }
    }

    return collisions;
}