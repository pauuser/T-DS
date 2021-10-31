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
int create_node(list_node **node, float tmp)
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
int list_queue_push(list_queue *queue, float tmp)
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
int list_queue_pop(list_queue *queue, float *tmp)
{
    int rc = OK;

    if (queue->count == 0)
        rc = EMPTY_Q;
    else
    {
        *tmp = queue->pout->data;
        list_node *to_free = queue->pout;

        queue->pout = to_free->next;
        queue->count--;

        free(to_free);
    }

    return rc;
}

/*
Очистка очереди
*/
void list_queue_clean(list_queue *queue)
{
    float tmp;

    while (queue->count != 0)
    {
        list_queue_pop(queue, &tmp);
    }

    queue->pin = NULL;
    queue->pout = NULL;
}

/*
Печать очереди
*/
void list_queue_print(list_queue *queue)
{
    if (queue->count == 0)
        printf("Queue is empty!\n");
    else
    {
        int n = queue->count;
        float tmp;

        for (int i = 0; i < n; i++)
        {
            list_queue_pop(queue, &tmp);
            list_queue_push(queue, tmp);

            printf("<- %.2f ", tmp);
        }
        printf("<-\n");
    }
}