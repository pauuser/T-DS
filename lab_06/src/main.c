#include <stdio.h>
#include <stdlib.h>

#include "../inc/io.h"
#include "../inc/bst.h"
#include "../inc/graph.h"
#include "../inc/avl.h"
#include "../inc/hash.h"
#include "../inc/file.h"
#include "../inc/effec.h"

int main(void)
{
    setbuf(stdout, NULL);
    print_welcome();

    int choice = -1;
    FILE *f = NULL;

    bst_node_t *bst = NULL;

    avl_node_t *avl = NULL;

    hash_t *table = NULL;

    int max_comp = 4;

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
        {
            int rc = read_file_to_bst(&bst, f);
            if (rc != OK)
                printf("Error!\n");
            else
                printf("Success!\n");
        }
        else if (choice == 4)
        {
            if (bst == NULL)
                printf("No BST!\n");
            else
            {
                int to_delete = 0;
                printf("Input number to delete: ");
                if (scanf("%d", &to_delete) == 1)
                {
                    bst = bst_delete_node(bst, to_delete);
                    printf("If the number existed, it was deleted!\n");
                }
                else
                {
                    printf("Wrong input!\n");
                    clean_stdin();
                }
            }
        }
        else if (choice == 3)
        {
            if (bst == NULL)
                printf("No BST!\n");
            else
            {
                int to_delete = 0;
                printf("Input number to add: ");
                if (scanf("%d", &to_delete) == 1)
                {
                    bst = bst_add_node(bst, bst_create_node(to_delete));
                    printf("Success!\n");
                }
                else
                {
                    printf("Wrong input!\n");
                    clean_stdin();
                }
            }
        }
        else if (choice == 5)
            bst_output_dot_graph(bst);
        else if (choice == 6)
        {
            int rc = avl_create_from_bst(bst, &avl);
            if (rc != OK)
                printf("Error!\n");
            else
                printf("Success!\n");
        }
        else if (choice == 7)
        {
            if (avl == NULL)
                printf("No AVL Tree!\n");
            else
            {
                int to_add = 0;
                printf("Input number to add: ");
                if (scanf("%d", &to_add) == 1)
                {
                    avl = avl_add_node(avl, avl_create_node(to_add));
                    printf("Success!\n");
                }
                else
                {
                    printf("Wrong input!\n");
                    clean_stdin();
                }
            }
        }
        else if (choice == 8)
        {
            if (avl == NULL)
                printf("No AVL Tree!\n");
            else
            {
                int to_delete = 0;
                printf("Input number to delete: ");
                if (scanf("%d", &to_delete) == 1)
                {
                    avl = avl_delete_node(avl, to_delete);
                    printf("If the number existed, it was deleted!\n");
                }
                else
                {
                    printf("Wrong input!\n");
                    clean_stdin();
                }
            }
        }
        else if (choice == 9)
            avl_output_dot_graph(avl);
        else if (choice == 10)
        {
            printf("Input maximum number of comparisons [default = 4]: ");
            if (scanf("%d", &max_comp) != 1 || max_comp < 1)
            {
                printf("Wrong input!\n");
                max_comp = 4;
                clean_stdin();
            }
        }
        else if (choice == 11)
        {
            int rc = read_file_to_hash(&table, f);
            if (rc != OK)
                printf("Error!\n");
            else
                printf("Success!\n");
        }
        else if (choice == 12)
        {
            hash_read(table);
        }
        else if (choice == 14)
        {
            if (table == NULL)
                printf("No table!\n");
            else
            {
                int to_delete = 0;
                printf("Input number to delete: ");
                if (scanf("%d", &to_delete) == 1)
                    hash_delete(table, to_delete);
                else
                {
                    printf("Wrong input!\n");
                    clean_stdin();
                }
            }
        }
        else if (choice == 13)
        {
            if (table == NULL)
                printf("No table!\n");
            else
            {
                int to_add = 0;
                printf("Input number to add: ");
                if (scanf("%d", &to_add) == 1)
                {
                    hash_add(table, to_add);
                    printf("Success!\n");
                }
                else
                {
                    printf("Wrong input!\n");
                    clean_stdin();
                }
            }
        }
        else if (choice == 15)
        {
            int comp_number = 0;
            int to_search = 0;
            
            if (bst == NULL)
                printf("No tree!\n");
            else
            {
                printf("Input number to search: ");
                if (scanf("%d", &to_search) == 1)
                {
                    bst_node_t *foundling = bst_search_node(bst, to_search, &comp_number);
                    if (foundling == NULL)
                        printf("Not found!\n");
                    else
                        printf("Found!\n");
                    printf("Comparisons number : %d\n", comp_number);
                }
                else
                {
                    printf("Wrong input!\n");
                    clean_stdin();
                }
            }
        }
        else if (choice == 16)
        {
            int comp_number = 0;
            int to_search = 0;
            
            if (avl == NULL)
                printf("No tree!\n");
            else
            {
                printf("Input number to search: ");
                if (scanf("%d", &to_search) == 1)
                {
                    avl_node_t *foundling = avl_search_node(avl, to_search, &comp_number);
                    if (foundling == NULL)
                        printf("Not found!\n");
                    else
                        printf("Found!\n");
                    printf("Comparisons number : %d\n", comp_number);
                }
                else
                {
                    printf("Wrong input!\n");
                    clean_stdin();
                }
            }
        }
        else if (choice == 17)
        {
            search_with_time(&table, max_comp);
        }
        else if (choice == 18)
        {
            int comp_number = 0;
            int to_search = 0;
            
            if (f == NULL)
                printf("No file!\n");
            else
            {
                printf("Input number to search: ");
                if (scanf("%d", &to_search) == 1)
                {
                    int res = file_search(f, to_search, &comp_number);
                    if (res == 1)
                        printf("Found!\n");
                    else
                        printf("Not found!\n");
                    printf("Comparisons number : %d\n", comp_number);
                }
                else
                {
                    printf("Wrong input!\n");
                    clean_stdin();
                }
            }
        }
        else if (choice == 19)
        {
            measure_time();
            measure_memory();
            collision_comparison();
        }
        else if (choice != 0)
        {
            printf("Wrong input!\n");
        }
    }
}