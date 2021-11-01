#include "../inc/time_func.h"

/*
Функция случайного вещественного времени от left до right
*/
double rtime(double left, double right)
{
    double a = (right - left) * ((double)rand() / (double)RAND_MAX) + left;
    return (double)((int)(a * 1000)) / 1000;
}

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

/*
Функция сравнения по времени
*/
void measure_time()
{
    arr_queue arr_queue = { 0 };
    arr_queue_init(&arr_queue);

    list_queue list_queue = { 0 };
    list_queue_init(&list_queue);

    free_mem mem = { 0 };
    free_mem_init(&mem);

    int64_t s1, e1, s2, e2;
    int arr_1 = 0;
    int list_1 = 0;

    for (int i = 0; i < 1000; i++)
    {
        s1 = tick();
        arr_queue_push(&arr_queue, 1.0);
        e1 = tick();

        arr_1 += (int)(e1 - s1);

        s2 = tick();
        list_queue_push(&list_queue, 1.0, &mem);
        e2 = tick();

        double tmp;
        arr_queue_pop(&arr_queue, &tmp);
        list_queue_pop(&list_queue, &tmp, &mem);

        list_1 += (int)(e2 - s2);

    }

    double a = 0.0;

    printf("PUSH:\n");
    printf("AVERAGE ON 1 000:\n");
    printf("Array queue : %10d\n", (int)arr_1 / 1000);
    printf("List queue  : %10d\n", (int)list_1 / 1000);

    arr_1 = 0;
    list_1 = 0;

    arr_queue_clean(&arr_queue);
    list_queue_clean(&list_queue, &mem);

    for (int i = 0; i < 1000000; i++)
    {
        double tmp;

        s1 = tick();
        arr_queue_push(&arr_queue, 1.0);
        e1 = tick();

        arr_1 += (int)(e1 - s1);

        s2 = tick();
        list_queue_push(&list_queue, 1.0, &mem);
        e2 = tick();

        arr_queue_pop(&arr_queue, &tmp);
        list_queue_pop(&list_queue, &tmp, &mem);

        list_1 += (int)(e2 - s2);

    }

    printf("AVERAGE ON 1 000 000:\n");
    printf("Array queue : %10d\n", (int)arr_1 / 1000000);
    printf("List queue  : %10d\n\n", (int)list_1 / 1000000);

    arr_1 = 0;
    list_1 = 0;

    for (int i = 0; i < 1000; i++)
    {
        arr_queue_push(&arr_queue, 1.0);
        list_queue_push(&list_queue, 1.0, &mem);

        s1 = tick();
        arr_queue_pop(&arr_queue, &a);
        e1 = tick();

        arr_1 += (int)(e1 - s1);

        s2 = tick();
        list_queue_pop(&list_queue, &a, &mem);
        e2 = tick();

        list_1 += (int)(e2 - s2);

    }

    printf("POP:\n");
    printf("AVERAGE ON 1000:\n");
    printf("Array queue : %10d\n", (int)arr_1 / 1000);
    printf("List queue  : %10d\n", (int)list_1 / 1000);

    arr_1 = 0;
    list_1 = 0;

    for (int i = 0; i < 1000000; i++)
    {
        arr_queue_push(&arr_queue, 1.0);
        list_queue_push(&list_queue, 1.0, &mem);

        s1 = tick();
        arr_queue_pop(&arr_queue, &a);
        e1 = tick();

        arr_1 += (int)(e1 - s1);

        s2 = tick();
        list_queue_pop(&list_queue, &a, &mem);
        e2 = tick();

        list_1 += (int)(e2 - s2);

    }

    printf("AVERAGE ON 1 000 000:\n");
    printf("Array queue : %10d\n", (int)arr_1 / 1000000);
    printf("List queue  : %10d\n\n", (int)list_1 / 1000000);

    arr_queue_free(&arr_queue);
    list_queue_clean(&list_queue, &mem);

    printf("STORAGE:\n");
    printf("Elems\tArray\tList\n");

    for (int i = 10; i <= ARR_QUEUE_SIZE; i = i * 2)
    {
        printf("%5d\t%5lld\t%5lld\n", i, 4 * sizeof(int) + ARR_QUEUE_SIZE * sizeof(double),
        sizeof(int) + 2 * sizeof(list_node *) + i * sizeof(list_node));
    }
}

