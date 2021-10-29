#ifndef __H_LIST_STACK__
#define __H_LIST_STACK__

#include "common.h"

#define OK               0
#define LIST_STACK_SIZE  3000

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

// инициалиация стека - списка
int list_stack_init(list_stack **stack);

// добавление элемента в стек - список
int list_stack_push(list_stack **stack, char *str, free_mem *mem);

// извлечение элемента из стека - списка
char *list_stack_pop(list_stack **stack, free_mem *mem);

// освобождение памяти стека - списка
void list_stack_free(list_stack **stack, free_mem *mem);

// печать стека - списка
void list_stack_print(list_stack *stack);

// инициализия списка свободных областей
void free_mem_init(free_mem *mem);

// добавление адреса в список свободных адресов
int free_mem_add(free_mem *mem, size_t add);

// удаление адреса из списка свободных адресов при его наличии
void free_mem_del(free_mem *mem, size_t del);

// очистка стека - списка
void list_stack_clear(list_stack **stack, free_mem *mem);

// вывод списка свободных адресов
void free_mem_print(free_mem *mem);

#endif 