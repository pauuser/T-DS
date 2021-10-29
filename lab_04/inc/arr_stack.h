#ifndef __H_ARR_STACK__
#define __H_ARR_STACK__

#include "common.h"

#define ARR_STACK_SIZE      3000

typedef struct arr_stack_t
{
    void *top;
    void *bottom;
    char **ps;
} arr_stack;

// инициализация стека - массива
int arr_stack_init(arr_stack *stack);

// добавление элемента в стек - массив
int arr_stack_push(arr_stack *stack, char *str);

// извлечение элемента из стека - массив
char *arr_stack_pop(arr_stack *stack);

// вывод стека - массива
void arr_stack_print(arr_stack stack);

// очитска стека - массива
void arr_stack_clear(arr_stack *stack);

#endif