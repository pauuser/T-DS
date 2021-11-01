#ifndef __H_LIST_QUEUE__
#define __H_LIST_QUEUE__

#include <stdlib.h>
#include <stdio.h>

#define LIST_QUEUE_SIZE 1500

/*
Нода списка
*/
typedef struct list_node
{
    double data; // время обработки данной заявки
    struct list_node *next; // следующая заявка
} list_node;

/*
Очередь в виде списка
*/
typedef struct list_queue
{
    int count;
    list_node *pout; // первый элемент на выход
    list_node *pin; // адрес последнего элемента
} list_queue;

/*
Список свободных адресов
*/
typedef struct free_mem
{
    size_t data;
    struct free_mem *next;
} free_mem;

// Инициализвция очереди
void list_queue_init(list_queue *queue);

// Создание ноды списка
int create_node(list_node **node, double tmp);

// Добавление элемента в очередь
int list_queue_push(list_queue *queue, double tmp, free_mem *mem);

// Удаление элемента из очереди
int list_queue_pop(list_queue *queue, double *tmp, free_mem *mem);

// Очистка очереди
void list_queue_clean(list_queue *queue, free_mem *mem);

// Печать очереди
void list_queue_print(list_queue *queue, free_mem *mem);

// Инициализия списка свободных областей
void free_mem_init(free_mem *mem);

// Добавление адреса в список свободных адресов
int free_mem_add(free_mem *mem, size_t add);

// Удаление адреса из списка свободных адресов при его наличии
void free_mem_del(free_mem *mem, size_t del);

// Вывод списка свободных адресов
void free_mem_print(free_mem *mem);

#endif