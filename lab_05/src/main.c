#include <stdio.h>

#include "../inc/time_func.h"
#include "../inc/arr_queue.h"
#include "../inc/errors.h"
#include "../inc/list_queue.h"
#include "../inc/process.h"
#include "../inc/io.h"

int main(void)
{
    setbuf(stdout, NULL);
    srand(time(NULL));

    int requests_num = 1000;

    double min_t1 = 1.0;
    double max_t1 = 5.0;

    double min_t2 = 0.0;
    double max_t2 = 3.0;

    double min_pr1 = 0.0;
    double max_pr1 = 4.0;

    double min_pr2 = 0.0;
    double max_pr2 = 1.0;

    int choice = 0;

    print_welcome();

    do
    {
        print_menu();

        int rc = scanf("%d", &choice);

        if (rc != 1)
        {
            printf("Wrong input!\n");
            clean_stdin();
        }
        else if (choice == 1)
        {
            arr_process_modeling(requests_num, min_t1, max_t1, 
                                                min_t2, max_t2, 
                                                    min_pr1, max_pr1,
                                                        min_pr2, max_pr2);
        }
        else if (choice == 2)
        {
            list_process_modeling(requests_num, min_t1, max_t1, 
                                                min_t2, max_t2, 
                                                    min_pr1, max_pr1,
                                                        min_pr2, max_pr2);
        }
        else if (choice == 3)
        {
            change_data(&requests_num, &min_t1, &max_t1, 
                                                &min_t2, &max_t2, 
                                                    &min_pr1, &max_pr1,
                                                        &min_pr2, &max_pr2);
        }
        else if (choice == 4)
        {

        }
        else if (choice != 0)
        {
            printf("Unknown command!\n");
        }
    } 
    while (choice != 0);

    return OK;
}