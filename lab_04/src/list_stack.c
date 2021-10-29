#include "../inc/list_stack.h"

int list_stack_init(list_stack **stack)
{
    int rc = OK;

    *stack = calloc(1, sizeof(list_stack));
    if (stack == NULL)
        rc = NO_MEMORY;
    else
    {
        (*stack)->index = 0;
        (*stack)->data = NULL;
        (*stack)->prev = NULL;
    }
    
    return rc;
}


int list_stack_push(list_stack **stack, char *str, free_mem *mem)
{
    int rc = OK;

    if ((*stack)->index == LIST_STACK_SIZE)
        rc = STACK_OVERFLOW;
    else
    {
        list_stack *new_node = calloc(1, sizeof(list_stack));

        if (new_node == NULL)
            rc = NO_MEMORY;
        else
        {
            new_node->index = (*stack)->index + 1;
            new_node->data = str;
            new_node->prev = *stack;

            free_mem_del(mem, (size_t) new_node);

            *stack = new_node;
        }
    }

    return rc;
}


char *list_stack_pop(list_stack **stack, free_mem *mem)
{
    char *rc;

    if ((*stack)->index == 0)
        rc = NULL;
    else
    {
        rc = (*stack)->data;
        list_stack *prev = (*stack)->prev;

        free_mem_add(mem, (size_t) *stack);

        free(*stack);
        *stack = prev;
    }

    return rc;
}

void list_stack_free(list_stack **stack, free_mem *mem)
{
    while ((*stack)->index != 0)
        list_stack_pop(stack, mem);

    free(*stack);
}

void list_stack_print(list_stack *stack)
{
    if (stack->index == 0)
        printf("The stack is empty!\n");
    while (stack->index != 0)
    {
        printf("%s \t\t-- %p\n", stack->data, (void *) stack);
        stack = stack->prev;
    }    
}

void list_stack_clear(list_stack **stack, free_mem *mem)
{
    while ((*stack)->index != 0)
    {
        free(list_stack_pop(stack, mem));
    }
}

void free_mem_init(free_mem *mem)
{
    mem->data = 0;
    mem->next = NULL;
}

int free_mem_add(free_mem *mem, size_t add)
{
    int rc = OK;

    free_mem *tmp = malloc(sizeof(free_mem));
    if (tmp == NULL)
        rc = NO_MEMORY;
    else
    {
        tmp->data = add;
        tmp->next = NULL;
    }

    while (rc == OK && mem->next != NULL)
        mem = mem->next;
    
    if (rc == OK)
        mem->next = tmp;

    return rc;
}

void free_mem_del(free_mem *mem, size_t del)
{
    while (mem->next != NULL && mem->next->data != del)
        mem = mem->next;
    
    if (mem->next != NULL && mem->next->data == del)
    {
        free_mem *to_free = mem->next;
        mem->next = to_free->next;

        free(to_free);
    }
    else if (mem->next == NULL && mem->data == del)
        free(mem);
}

void free_mem_print(free_mem *mem)
{
    printf("Free addresses:\n");
    if (mem->data == 0)
        printf("No free addresses yet!\n");
    while (mem != NULL)
    {
        if (mem->data != 0)
            printf("%llx\n", (long long)mem->data);
        mem = mem->next;
    }
}
