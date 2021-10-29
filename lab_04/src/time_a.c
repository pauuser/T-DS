#include "../inc/time_a.h"

#include "time.h"
#include "string.h"

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

void time_output()
{
    arr_stack arr;
    arr_stack_init(&arr);

    list_stack *list;
    list_stack_init(&list);

    free_mem mem;
    free_mem_init(&mem);

    FILE *f = fopen("./src/data/10.txt", "r");
    int64_t s1, e1, s2, e2;

    both_fill_file(f, &arr, &list, &mem);

    char *a = malloc(3 * sizeof(char));
    a[0] = 'a';
    a[1] = 'b';
    a[2] = '\0';

    int arr_1 = 0;
    int list_1 = 0;

    for (int i = 0; i < 1000; i++)
    {
        s1 = tick();
        arr_stack_push(&arr, a);
        e1 = tick();

        arr_1 += (int)(e1 - s1);

        s2 = tick();
        list_stack_push(&list, a, &mem);
        e2 = tick();

        list_1 += (int)(e2 - s2);
    }

    printf("PUSH:\n");
    printf("num\t\tarr\t\tlist\n");
    printf("10\t%10d\t %10d\n", (int)arr_1 / 1000, (int)list_1 / 1000);

    while ((void *)arr.ps > arr.bottom)
        arr_stack_pop(&arr);
    while (list->index != 0)
        list_stack_pop(&list, &mem);
    
    fclose(f);

    f = fopen("./src/data/100.txt", "r");

    both_fill_file(f, &arr, &list, &mem);
    a = malloc(3 * sizeof(char));
    a[0] = 'a';
    a[1] = 'b';
    a[2] = '\0';

    arr_1 = 0;
    list_1 = 0;

    for (int i = 0; i < 1000; i++)
    {
        s1 = tick();
        arr_stack_push(&arr, a);
        e1 = tick();

        arr_1 += (int)(e1 - s1);

        s2 = tick();
        list_stack_push(&list, a, &mem);
        e2 = tick();

        list_1 += (int)(e2 - s2);
    }

    printf("100\t%10d\t %10d\n", (int)arr_1 / 1000, (int)list_1 / 10000);
        
    while ((void *)arr.ps > arr.bottom)
        arr_stack_pop(&arr);
    while (list->index != 0)
        list_stack_pop(&list, &mem);
    
    fclose(f);

    f = fopen("./src/data/1000.txt", "r");

    both_fill_file(f, &arr, &list, &mem);
    a = malloc(3 * sizeof(char));
    a[0] = 'a';
    a[1] = 'b';
    a[2] = '\0';

    arr_1 = 0;
    list_1 = 0;

    for (int i = 0; i < 1000; i++)
    {
        s1 = tick();
        arr_stack_push(&arr, a);
        e1 = tick();

        arr_1 += (int)(e1 - s1);

        s2 = tick();
        list_stack_push(&list, a, &mem);
        e2 = tick();

        list_1 += (int)(e2 - s2);
    }

    printf("1000\t%10d\t %10d\n", (int)arr_1 / 1000, (int)list_1 / 1000);
        
    while ((void *)arr.ps > arr.bottom)
        arr_stack_pop(&arr);
    while (list->index != 0)
        list_stack_pop(&list, &mem);
    
    fclose(f);

    // POP

    f = fopen("./src/data/10.txt", "r");

    both_fill_file(f, &arr, &list, &mem);

    arr_1 = 0;
    list_1 = 0;

    for (int i = 0; i < 1000; i++)
    {
        s1 = tick();
        arr_stack_pop(&arr);
        e1 = tick();

        arr_1 += (int)(e1 - s1);

        s2 = tick();
        list_stack_pop(&list, &mem);
        e2 = tick();

        list_1 += (int)(e2 - s2);
    }

    printf("POP:\n");
    printf("num\t\tarr\t\tlist\n");
    printf("10\t%10d\t %10d\n", (int)arr_1 / 1000, (int)list_1 / 1000);

    while ((void *)arr.ps > arr.bottom)
        arr_stack_pop(&arr);
    while (list->index != 0)
        list_stack_pop(&list, &mem);
    
    fclose(f);

    f = fopen("./src/data/100.txt", "r");

    both_fill_file(f, &arr, &list, &mem);

    arr_1 = 0;
    list_1 = 0;

    for (int i = 0; i < 1000; i++)
    {
        s1 = tick();
        arr_stack_pop(&arr);
        e1 = tick();

        arr_1 += (int)(e1 - s1);

        s2 = tick();
        list_stack_pop(&list, &mem);
        e2 = tick();

        list_1 += (int)(e2 - s2);
    }

    printf("100\t%10d\t %10d\n", (int)arr_1 / 1000, (int)list_1 / 1000);
        
    while ((void *)arr.ps > arr.bottom)
        arr_stack_pop(&arr);
    while (list->index != 0)
        list_stack_pop(&list, &mem);
    
    fclose(f);

    f = fopen("./src/data/1000.txt", "r");

    both_fill_file(f, &arr, &list, &mem);

    arr_1 = 0;
    list_1 = 0;

    for (int i = 0; i < 1000; i++)
    {
        s1 = tick();
        arr_stack_pop(&arr);
        e1 = tick();

        arr_1 += (int)(e1 - s1);

        s2 = tick();
        list_stack_pop(&list, &mem);
        e2 = tick();

        list_1 += (int)(e2 - s2);
    }

    printf("1000\t%10d\t %10d\n", (int)arr_1 / 1000, (int)list_1 / 1000);
        
    while ((void *)arr.ps > arr.bottom)
        arr_stack_pop(&arr);
    while (list->index != 0)
        list_stack_pop(&list, &mem);
    
    fclose(f);

    // storage

    f = fopen("./src/data/10.txt", "r");

    both_fill_file(f, &arr, &list, &mem);

    arr_1 = 0;
    list_1 = 0;

    while (list->index != 0)
    {
        list_stack_pop(&list, &mem);
        list_1 += sizeof(list_stack);
    }

    arr_1 += 2 * sizeof(void *) + ARR_STACK_SIZE * sizeof(char *);

    printf("STORAGE:\n");
    printf("num\t\tarr\t\tlist\n");
    printf("10\t%10d\t %10d\n", (int)arr_1,  (int)list_1);
    
    fclose(f);

    f = fopen("./src/data/100.txt", "r");

    both_fill_file(f, &arr, &list, &mem);

    arr_1 = 0;
    list_1 = 0;

    while (list->index != 0)
    {
        list_stack_pop(&list, &mem);
        list_1 += sizeof(list_stack);
    }

    arr_1 += 2 * sizeof(void *) + ARR_STACK_SIZE * sizeof(char *);

    printf("100\t%10d\t %10d\n", (int)arr_1, (int)list_1);
    
    fclose(f);

    f = fopen("./src/data/1000.txt", "r");

    both_fill_file(f, &arr, &list, &mem);

    arr_1 = 0;
    list_1 = 0;


    while (list->index != 0)
    {
        list_stack_pop(&list, &mem);
        list_1 += sizeof(list_stack);
    }

    arr_1 += 2 * sizeof(void *) + ARR_STACK_SIZE * sizeof(char *);

    printf("1000\t%10d\t %10d\n", (int)arr_1, (int)list_1);

    rewind(f);

    both_fill_file(f, &arr, &list, &mem);

    rewind(f);

    both_fill_file(f, &arr, &list, &mem);

    arr_1 = 0;
    list_1 = 0;

    //printf("%ld %ld\n", sizeof(int) + sizeof(struct list_stack *) + sizeof(char *), sizeof(list_stack));

    while (list->index != 0)
    {
        list_stack_pop(&list, &mem);
        list_1 += sizeof(list_stack);
    }

    arr_1 += 2 * sizeof(void *) + ARR_STACK_SIZE * sizeof(char *);

    printf("2000\t%10d\t %10d\n", (int)arr_1, (int)list_1);
    
    fclose(f);
}

void both_fill_file(FILE *f, arr_stack *arr, list_stack **ls, free_mem *mem)
{
    int n = 0;
    int rc = fscanf(f, "%d", &n);

    if (rc != 1)
        clean_stdin();

    if (n <= 0 || rc != 1)
        printf("Must be a positive number!\n");
    else
    {
        int i = 0, rc;
        do
        {       
            char *word = malloc((MAX_WORD_LEN + 1) * sizeof(char));

            fscanf(f, "%s", word);

            rc = arr_stack_push(arr, word);
            rc = list_stack_push(ls, word, mem);
            if (rc == STACK_OVERFLOW)
                i = n;
            else
                i++;
        }
        while (i < n);
    }
}