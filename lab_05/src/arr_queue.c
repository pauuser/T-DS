#include "../inc/arr_queue.h"
#include "../inc/errors.h"
#include "../inc/time_func.h"

/*
Инициализация очереди
*/
int arr_queue_init(arr_queue *queue)
{
    int rc = OK;

    float *tmp = malloc(sizeof(float) * ARR_QUEUE_SIZE);
    if (tmp == NULL)
        rc = NO_MEMORY;
    else
    {
        queue->arr = tmp;
        queue->pin = -1;
        queue->pout = 0;
        queue->count = 0;
        queue->size = ARR_QUEUE_SIZE;
    }

    return rc;
}

/*
Добавление элемента в конец очереди
*/
int arr_queue_push(arr_queue *queue, float process_time)
{
    int rc = OK;

    queue->pin = (queue->pin + 1) % ARR_QUEUE_SIZE;
    
    if (queue->pin == queue->pout && queue->count == ARR_QUEUE_SIZE)
    {
        rc = OVERFLOW;
        queue->pin = queue->pin - 1 < 0 ? queue->size - 1 : queue->pin - 1;
    }
    else
    {
        queue->count++;
        queue->arr[queue->pin] = process_time;
    }

    return rc;
}

/*
Удаление элемента из очереди
*/
int arr_queue_pop(arr_queue *queue, float *ret_time)
{
    int rc = OK;

    if (queue->count == 0)
        rc = EMPTY_Q;
    else
    {
        *ret_time = queue->arr[queue->pout];
        queue->count--;
        queue->pout = (queue->pout + 1) % ARR_QUEUE_SIZE;
    }

    return rc;
}

/*
Освобождение памяти под очередь
*/
void arr_queue_free(arr_queue *queue)
{
    free(queue->arr);
}

/*
Очистка очереди
*/
void arr_queue_clean(arr_queue *queue)
{
    queue->count = 0;
    queue->pin = -1;
    queue->pout = 0;
}

/*
Печать очереди
*/
void arr_queue_print(arr_queue *queue)
{
    if (queue->count == 0)
        printf("Queue is empty!\n");
    else
    {
        int n = queue->count;
        float tmp;
        for (int i = 0; i < n; i++)
        {
            arr_queue_pop(queue, &tmp);
            arr_queue_push(queue, tmp);

            printf("<- %.2f ", tmp);
        }
        printf("<-\n");
    }
}