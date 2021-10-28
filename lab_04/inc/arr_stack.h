#ifndef __H_ARR_STACK__
#define __H_ARR_STACK__

#include "common.h"

#define ARR_STACK_SIZE      10

typedef struct arr_stack_t
{
    void *top;
    void *bottom;
    char **ps;
} arr_stack;

int arr_stack_init(arr_stack *stack);

int arr_stack_push(arr_stack *stack, char *str);

char *arr_stack_pop(arr_stack *stack);

void arr_stack_print(arr_stack stack);

void arr_stack_clear(arr_stack *stack);

#endif