#include <stdlib.h>
#include <stdio.h>

#define LIST_QUEUE_SIZE 1500

/*
Очередь в виде списка
*/
typedef struct list_node
{
    double data; // время обработки данной заявки
    struct list_node *next; // следующая заявка
} list_node;

typedef struct list_queue
{
    int count;
    list_node *pout; // первый элемент на выход
    list_node *pin; // адрес последнего элемента
} list_queue;

// Инициализвция очереди
void list_queue_init(list_queue *queue);

// Создание ноды списка
int create_node(list_node **node, double tmp);

// Добавление элемента в очередь
int list_queue_push(list_queue *queue, double tmp);

// Удаление элемента из очереди
int list_queue_pop(list_queue *queue, double *tmp);

// Очистка очереди
void list_queue_clean(list_queue *queue);

// Печать очереди
void list_queue_print(list_queue *queue);