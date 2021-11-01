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

void change_data(int *requests_num, 
                    double *min_t1, double *max_t1, 
                        double *min_t2, double *max_t2,
                            double *min_pr1, double *max_pr1,
                                double *min_pr2, double *max_pr2)
{
    printf("Current values:\n");
    printf("1 : Number of 1st queue requests      : %d\n", *requests_num);
    printf("2 : Time of 1st queue requests input  : from %.2f to %.2f\n", *min_t1, *max_t1);
    printf("3 : Time of 2nd queue requests input  : from %.2f to %.2f\n", *min_t2, *max_t2);
    printf("4 : Time of 1st queue processing      : from %.2f to %.2f\n", *min_pr1, *max_pr1);
    printf("5 : Time of 2nd queue processing      : from %.2f to %.2f\n", *min_pr2, *max_pr2);
    printf("You want to change : ");

    int choice = 0;
    if (scanf("%d", &choice) != 1)
    {
        printf("Wrong input!\n");
        clean_stdin();
    }
    else if (choice == 1)
    {
        int n = 0;
        printf("Input number of requests [1, 1 000 000]: ");
        if ((scanf("%d", &n) != 1) || (n < 1) || (n > 1000000))
        {
            printf("Wrong input!\n");
            clean_stdin();
        }
        else
        {
            *requests_num = n;
        }
    }
    else if (choice == 2)
    {
        double a = 0.0, b = 0.0;
        printf("Input time of 1st queue requests input [0, 10 000]: ");
        if (scanf("%lf", &a) != 1 || scanf("%lf", &b) != 1 || a < 0 || b < 0 || a >= b || a > 10000 || b > 10000)
        {
            printf("Wrong input!\n");
            clean_stdin();
        }
        else
        {
            *min_t1 = a;
            *max_t1 = b;
        }
    }
    else if (choice == 3)
    {
        double a = 0.0, b = 0.0;
        printf("Input time of 2nd queue requests input [0, 10 000]: ");
        if (scanf("%lf", &a) != 1 || scanf("%lf", &b) != 1 || a < 0 || b < 0 || a >= b || a > 10000 || b > 10000)
        {
            printf("Wrong input!\n");
            clean_stdin();
        }
        else
        {
            *min_t2 = a;
            *max_t2 = b;
        }
    }
    else if (choice == 4)
    {
        double a = 0.0, b = 0.0;
        printf("Input time of 1st queue processing [0, 10 000]: ");
        if (scanf("%lf", &a) != 1 || scanf("%lf", &b) != 1 || a < 0 || b < 0 || a >= b || a > 10000 || b > 10000)
        {
            printf("Wrong input!\n");
            clean_stdin();
        }
        else
        {
            *min_pr1 = a;
            *max_pr1 = b;
        }
    }
    else if (choice == 5)
    {
        double a = 0.0, b = 0.0;
        printf("Input time of 2nd queue processing [0, 10 000]: ");
        if (scanf("%lf", &a) != 1 || scanf("%lf", &b) != 1 || a < 0 || b < 0 || a >= b || a > 10000 || b > 10000)
        {
            printf("Wrong input!\n");
            clean_stdin();
        }
        else
        {
            *min_pr2 = a;
            *max_pr2 = b;
        }
    }
}