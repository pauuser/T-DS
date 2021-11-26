#include <stdio.h>
#include <stdlib.h>

#include "../inc/io.h"
#include "../inc/bst.h"
#include "../inc/graph.h"

int main(void)
{
    setbuf(stdout, NULL);
    print_welcome();

    int choice = -1;
    FILE *f = NULL;

    bst_node_t *bst = NULL;

    while (choice != 0)
    {
        print_menu();

        if (scanf("%d", &choice) != 1)
        {
            printf("Wrong input!\n");
            clean_stdin();
        }
        else if (choice == 1)
        {
           input_file_name(&f); 
        }
        else if (choice == 2)
        {
            if (f == NULL)
                printf("No file!\n");
            else
            {
                read_file_to_bst(&bst, f);
                FILE *f = fopen("my_test.txt", "w");
                bst_traverse(bst, bst_node_print, f, "in");
                bst_output_dot_graph(bst);
            }
        }
        else if (choice == 3)
        {

        }
        else if (choice == 4)
        {

        }
        else if (choice == 5)
        {

        }
        else if (choice == 6)
        {

        }
        else if (choice != 0)
        {
            printf("Wrong input!\n");
        }
    }
}
