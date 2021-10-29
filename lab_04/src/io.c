#include "../inc/io.h"

void clean_stdin()
{
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void arr_stack_fill(arr_stack *arr)
{
    printf("Number of words : ");

    int n = 0;
    int rc = scanf("%d", &n);

    if (rc != 1)
        clean_stdin();

    if (n <= 0 || rc != 1)
        printf("Must be a positive number!\n");
    else
    {
        int i = 0, rc;
        do
        {       
            rc = arr_stack_add(arr);
            if (rc == STACK_OVERFLOW)
                i = n;
            else
                i++;
        }
        while (i < n);
    }
    
}

int arr_stack_add(arr_stack *arr)
{
    char *word = malloc((MAX_WORD_LEN + 1) * sizeof(char));

    printf("Input stack element : ");
    scanf("%s", word);

    int rc = arr_stack_push(arr, word);
    
    if (rc == STACK_OVERFLOW)
        printf("Error : Stack is full!\n");

    return rc;
}

void list_stack_fill(list_stack **ls, free_mem *mem)
{
    printf("Number of words : ");

    int n = 0;
    int rc = scanf("%d", &n);

    if (rc != 1)
        clean_stdin();

    if (n <= 0 || rc != 1)
        printf("Must be a positive number!\n");
    else
    {
        int i = 0, rc;
        do
        {       
            rc = list_stack_add(ls, mem);
            if (rc == STACK_OVERFLOW)
                i = n;
            else
                i++;
        }
        while (i < n);
    }
    
}

void both_stack_fill(arr_stack *arr, list_stack **ls, free_mem *mem)
{
    printf("Number of words : ");

    int n = 0;
    int rc = scanf("%d", &n);

    if (rc != 1)
        clean_stdin();

    if (n <= 0 || rc != 1)
        printf("Must be a positive number!\n");
    else
    {
        int i = 0, rc;
        do
        {       
            char *word = malloc((MAX_WORD_LEN + 1) * sizeof(char));

            printf("Input stack element : ");
            scanf("%s", word);

            rc = arr_stack_push(arr, word);
            rc = list_stack_push(ls, word, mem);
            if (rc == STACK_OVERFLOW)
                i = n;
            else
                i++;
        }
        while (i < n);
    }
}

int list_stack_add(list_stack **ls, free_mem *mem)
{
    char *word = malloc((MAX_WORD_LEN + 1) * sizeof(char));

    printf("Input stack element : ");
    scanf("%s", word);

    int rc = list_stack_push(ls, word, mem);
    
    
    if (rc == STACK_OVERFLOW)
        printf("Error : Stack is full!\n");

    return rc;
}

void print_welcome()
{
    printf("Welcome! This programme performs operations with stack.\n");
    printf("To use if follow the menu commands and enter only what\n");
    printf("you are asked for!\n");
    printf("Elements of the stack are WORDS! - meaning no spaces.\n");
}

void print_menu()
{
    printf("\n");
    printf("+-------------------------------------------------------+\n");
    printf("| Choose your option!                                   |\n");
    printf("|                                                       |\n");
    printf("| Using array stack:                                    |\n");
    printf("| 1 - Input elements                                    |\n");
    printf("| 2 - Add an element                                    |\n");
    printf("| 3 - Pop an element                                    |\n");
    printf("| 4 - Print the stack                                   |\n");
    printf("| 5 - Clear the stack                                   |\n");
    printf("|                                                       |\n");
    printf("| Using list stack:                                     |\n");
    printf("| 6 - Input elements                                    |\n");
    printf("| 7 - Add an element                                    |\n");
    printf("| 8 - Pop an element                                    |\n");
    printf("| 9 - Print the stack                                   |\n");
    printf("| 10 - Clear the stack                                  |\n");
    printf("| 11 - Print free addresses                             |\n");
    printf("|                                                       |\n");
    printf("| The given problem:                                    |\n");
    printf("| 12 - Print reversed words in reversed order + metrics |\n");
    printf("|                                                       |\n");
    printf("| Analysis:                                             |\n");
    printf("| 13 - Output time comparison                           |\n");
    printf("+-------------------------------------------------------+\n");
    printf("\nYour choice: ");
}