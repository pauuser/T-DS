#include <stdio.h>
#include "../inc/common.h"
#include "../inc/arr_stack.h"
#include "../inc/list_stack.h"
#include "../inc/io.h"
#include "../inc/reverse.h"

int main(void)
{
    setbuf(stdout, NULL);

    int choice = 0;

    arr_stack stack_a;
    arr_stack_init(&stack_a);

    list_stack *stack_l;
    list_stack_init(&stack_l);

    free_mem mem;
    free_mem_init(&mem);

    print_welcome();

    do
    {

        print_menu();

        int rc = scanf("%d", &choice);

        if (rc != 1)
            clean_stdin();
        else if (choice == 1)
        {
            arr_stack_fill(&stack_a);
        }
        else if (choice == 2)
        {
            arr_stack_add(&stack_a);
        }
        else if (choice == 3)
        {
            char *rc = arr_stack_pop(&stack_a);
            if (rc == NULL)
                printf("The stack is already empty!\n");
        }
        else if (choice == 4)
        {
            arr_stack_print(stack_a);
        }
        else if (choice == 5)
        {
            arr_stack_clear(&stack_a);
        }
        else if (choice == 6)
        {
            list_stack_fill(&stack_l, &mem);
        }
        else if (choice == 7)
        {
            list_stack_add(&stack_l, &mem);
        }
        else if (choice == 8)
        {
            char *rc = list_stack_pop(&stack_l, &mem);
            if (rc == NULL)
                printf("The stack is already empty!\n");
        }
        else if (choice == 9)
        {
            list_stack_print(stack_l);
        }
        else if (choice == 10)
        {
            list_stack_clear(&stack_l, &mem);
        }
        else if (choice == 11)
        {
            free_mem_print(&mem);
        }
        else if (choice == 12)
        {
            print_reverse_words();
        }
    } 
    while (choice != 0);
    

    return 0;
}