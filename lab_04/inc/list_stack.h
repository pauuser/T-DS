#ifndef __H_LIST_STACK__
#define __H_LIST_STACK__

#include "common.h"

#define OK               0
#define LIST_STACK_SIZE  100

typedef struct list_stack
{
    int index;
    char *data;
    struct list_stack *prev;
} list_stack;

typedef struct free_mem
{
    size_t data;
    struct free_mem *next;
} free_mem;

int list_stack_init(list_stack **stack);

int list_stack_push(list_stack **stack, char *str, free_mem *mem);

char *list_stack_pop(list_stack **stack, free_mem *mem);

void list_stack_free(list_stack **stack, free_mem *mem);

void list_stack_print(list_stack *stack);

void free_mem_init(free_mem *mem);

int free_mem_add(free_mem *mem, size_t add);

void free_mem_del(free_mem *mem, size_t del);

void list_stack_clear(list_stack **stack, free_mem *mem);

void free_mem_print(free_mem *mem);

#endif 