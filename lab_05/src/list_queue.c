#include <stdlib.h>
#include <stdio.h>

#include "../inc/list_queue.h"
#include "../inc/errors.h"

/*
Инициализация очереди
*/
void list_queue_init(list_queue *queue)
{
    queue->count = 0;
    queue->pout = NULL;
    queue->pin = NULL;
}

/*
Создание ноды списка
*/
int create_node(list_node **node, double tmp)
{
    int rc = OK;

    *node = malloc(sizeof(list_node));

    if (node == NULL)
        rc = NO_MEMORY;
    else
    {
        (*node)->data = tmp;
        (*node)->next = NULL;
    }

    return rc;
}

/*
Добавление элемента в очередь
*/
int list_queue_push(list_queue *queue, double tmp, free_mem *mem)
{
    int rc = OK;

    if (queue->count == LIST_QUEUE_SIZE)
        rc = OVERFLOW;
    else
    {
        list_node *new = NULL;
        if (create_node(&new, tmp) == OK)
        {
            if (queue->pin == NULL)
            {
                queue->pin = new;
                queue->pout = new;
            }
            else
            {
                queue->pin->next = new;
                queue->pin = new;
            }

            free_mem_del(mem, (size_t) new);

            queue->count++;
        }
        else
            rc = NO_MEMORY;
    }

    return rc;
}

/*
Удаление элемента из очереди
*/
int list_queue_pop(list_queue *queue, double *tmp, free_mem *mem)
{
    int rc = OK;

    if (queue->count < 1)
        rc = EMPTY_Q;
    else
    {
        queue->count = queue->count - 1;
        *tmp = queue->pout->data;

        list_node *to_free = queue->pout;
        free_mem_add(mem, (size_t) to_free);
        
        queue->pout = to_free->next;

        if (queue->pout == NULL)
            queue->pin = NULL;

        free(to_free);
    }

    return rc;
}

/*
Очистка очереди
*/
void list_queue_clean(list_queue *queue, free_mem *mem)
{
    double tmp;

    while (queue->count != 0)
    {
        list_queue_pop(queue, &tmp, mem);
    }

    queue->pin = NULL;
    queue->pout = NULL;
}

/*
Печать очереди
*/
void list_queue_print(list_queue *queue, free_mem *mem)
{
    if (queue->count == 0)
        printf("Queue is empty!\n");
    else
    {
        int n = queue->count;
        double tmp;

        for (int i = 0; i < n; i++)
        {
            list_queue_pop(queue, &tmp, mem);
            list_queue_push(queue, tmp, mem);

            printf("<- %.2f ", tmp);
        }
        printf("<-\n");
    }
}

/*
Инциализация списка свободных адресов
*/
void free_mem_init(free_mem *mem)
{
    mem->data = 0;
    mem->next = NULL;
}

/*
Добавление адреса в список свободных адресов
*/
int free_mem_add(free_mem *mem, size_t add)
{
    int rc = OK;

    free_mem *tmp = malloc(sizeof(free_mem));
    if (tmp == NULL)
        rc = NO_MEMORY;
    else
    {
        tmp->data = add;
        tmp->next = NULL;
    }

    while (rc == OK && mem->next != NULL)
        mem = mem->next;
    
    if (rc == OK)
        mem->next = tmp;

    return rc;
}

/*
Удаление адреса из списка свободных адресов
*/
void free_mem_del(free_mem *mem, size_t del)
{
    while (mem->next != NULL && mem->next->data != del)
        mem = mem->next;
    
    if (mem->next != NULL && mem->next->data == del)
    {
        free_mem *to_free = mem->next;
        mem->next = to_free->next;

        free(to_free);
    }
    else if (mem->next == NULL && mem->data == del)
        free(mem);
}

/*
Вывод массива свободных адресов
*/
void free_mem_print(free_mem *mem)
{
    printf("Free addresses:\n");
    while (mem != NULL)
    {
        if (mem->data != 0)
            printf("%llx\n", (long long)mem->data);
        mem = mem->next;
    }
}
