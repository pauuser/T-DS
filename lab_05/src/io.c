#include "../inc/io.h"

void print_welcome()
{
    printf("================= Welcome! =================\n");
    printf("This programme performs operations on queues.\n");
    printf("You can  solve the given  case, changing  the \n");
    printf("values or measure time needed for operations.\n");
    printf("The  programme has two  queues and a handler. \n");
    printf("The  requests  from  the 1st  queue are  more\n");
    printf("important so they are handled first. If there\n");
    printf("are no  requests from  the first  queue - the \n");
    printf("requests from the second queue are handled.\n");
}

void print_menu()
{
    printf("\n+-------------------------------------------------------+\n");
    printf("| Choose your option!                                   |\n");
    printf("|                                                       |\n");
    printf("| 1 - Run programme (array)                             |\n");
    printf("| 2 - Run programme (list)                              |\n");
    printf("| 3 - Change data                                       |\n");
    printf("| 4 - Measure time and efficiency                       |\n");
    printf("|                                                       |\n");
    printf("| 0 - Exit                                              |\n");
    printf("+-------------------------------------------------------+\n");
    printf("\nYour choice: ");
}

void clean_stdin()
{
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void change_data()
{
    
}