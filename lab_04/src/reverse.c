#include "../inc/reverse.h"
#include "../inc/list_stack.h"
#include "../inc/io.h"
#include "../inc/arr_stack.h"
#include "../inc/time_a.h"

void print_reverse_words()
{
    arr_stack stack_a;
    arr_stack_init(&stack_a);

    list_stack *stack_l;
    list_stack_init(&stack_l);

    free_mem mem;
    free_mem_init(&mem);

    printf("Enter words: \n");
    both_stack_fill(&stack_a, &stack_l, &mem);

    printf("Solution via array stack:\n");
    
    while ((void *)stack_a.ps > stack_a.bottom)
    {
        char *tmp = arr_stack_pop(&stack_a);
        print_word_backwards_arr(tmp);
        printf("\n");
    }

    printf("Solution via list stack:\n");
    while (stack_l->index != 0)
    {
        char *tmp = list_stack_pop(&stack_l, &mem);
        print_word_backwards_list(tmp);
        printf("\n");

        free(tmp);
    }
}

int print_word_backwards_arr(char *word)
{
    int rc = OK;

    arr_stack stack_a;
    arr_stack_init(&stack_a);

    while (*word)
    {
        char *tmp = malloc(2 * sizeof(char));
        if (tmp == NULL)
            rc = NO_MEMORY;
        else
        {
            tmp[0] = *word;
            tmp[1] = '\0';
            arr_stack_push(&stack_a, tmp);

            tmp = NULL;
        }
        word++;
    }
    while ((void *)stack_a.ps > stack_a.bottom)
    {
        printf("%s", *(stack_a.ps));
        free(arr_stack_pop(&stack_a));
    }

    return rc;
}

int print_word_backwards_list(char *word)
{
    int rc = OK;

    list_stack *stack_l;
    list_stack_init(&stack_l);

    free_mem mem;
    free_mem_init(&mem);

    while (*word)
    {
        char *tmp = malloc(2 * sizeof(char));
        if (tmp == NULL)
            rc = NO_MEMORY;
        else
        {
            tmp[0] = *word;
            tmp[1] = '\0';
            list_stack_push(&stack_l, tmp, &mem);

            tmp = NULL;
        }
        word++;
    }

    while (stack_l->index != 0)
    {
        printf("%s", stack_l->data);
        stack_l = stack_l->prev;
    }    

    return rc;
}