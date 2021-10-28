#ifndef __H_IO__
#define __H_IO__

#include "../inc/common.h"
#include "../inc/list_stack.h"
#include "../inc/arr_stack.h"

void clean_stdin();

void free_mem_init(free_mem *mem);

void arr_stack_fill(arr_stack *arr);

int arr_stack_add(arr_stack *arr);

void list_stack_fill(list_stack **ls, free_mem *mem);

int list_stack_add(list_stack **ls, free_mem *mem);

void print_welcome();

void print_menu();

#endif