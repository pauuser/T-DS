#ifndef __H_ARR_QUEUE__
#define __H_ARR_QUEUE__

#include <stdlib.h>
#include <stdio.h>

#define ARR_QUEUE_SIZE  1500

/*
Кольцевая очередь в виде массива
*/
typedef struct arr_queue
{
    int pin; // указатель на начало
    int pout; // указатель на конец
    int size; // размер массива
    int count; // количество элементов в очереди
    double *arr; // массив, элементы коротого - время прихода
} arr_queue;


// Инициализация очереди
int arr_queue_init(arr_queue *queue);

// Добавление элемента в конец очереди
int arr_queue_push(arr_queue *queue, double come_time);

// Удаление элемента из очереди
int arr_queue_pop(arr_queue *queue, double *ret_time);

// Освобождение памяти под очередь
void arr_queue_free(arr_queue *queue);

// Очистка очереди
void arr_queue_clean(arr_queue *queue);

// Печать очереди
void arr_queue_print(arr_queue *queue);

#endif