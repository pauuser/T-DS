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
           input_file_name(&f); 
        else if (choice == 2)
            read_file_to_bst(&bst, f);
        else if (choice == 3)
            bst_output_dot_graph(bst);
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
