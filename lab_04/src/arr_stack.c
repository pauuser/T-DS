#include "../inc/arr_stack.h"

int arr_stack_init(arr_stack *stack)
{
    int rc = OK;

    char **array = malloc(ARR_STACK_SIZE * sizeof(char *));
    if (array == NULL)
        rc = NO_MEMORY;
    else
    {
        stack->bottom = array;
        stack->top = array + ARR_STACK_SIZE;
        stack->ps = array;
    }

    return rc;
}


int arr_stack_push(arr_stack *stack, char *str)
{
    int rc = OK;

    char **ptr = stack->ps + 1;

    if ((void *)ptr > stack->top)
        rc = STACK_OVERFLOW;
    else
    {
        stack->ps = ptr;
        *(stack->ps) = str;
    }

    return rc;
}


char *arr_stack_pop(arr_stack *stack)
{
    char *rc = NULL;

    char **ptr = stack->ps - 1;

    if ((void *)ptr < stack->bottom)
        rc = NULL;
    else
    {
        rc = *(stack->ps);
        stack->ps = ptr;
    }

    return rc;
}


void arr_stack_print(arr_stack stack)
{
    if ((void *)stack.ps <= stack.bottom)
        printf("The stack is empty!\n");
    while ((void *)stack.ps > stack.bottom)
    {
        printf("%s \t\t-- %p\n", *(stack.ps), (void *)stack.ps);
        arr_stack_pop(&stack);
    }
}

void arr_stack_clear(arr_stack *stack)
{
    while ((void *)stack->ps > stack->bottom)
    {
        free(arr_stack_pop(stack));
    }
}