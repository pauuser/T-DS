#include "../inc/io.h"
#include <unistd.h>
#include <limits.h>

void print_welcome()
{
    printf("Welcome! This programme perfoms operations on:\n");
    printf("- Binary Search Trees\n");
    printf("- AVL Trees\n");
    printf("- Hash tables\n");
    printf("- Files\n");
    printf("Follow the instructions provided by the menu.\n");
}

void print_menu()
{
    printf("\n+--------------------------------------------------------+\n");
    printf("| Choose your option!                                    |\n");
    printf("|                                                        |\n");
    printf("| 1  - Input file name                                   |\n");
    printf("|                                                        |\n");
    printf("| 2  - Build Binary Search Tree (BST) based on the file  |\n");
    printf("| 3  - Add node to BST                                   |\n");
    printf("| 4  - Delete node in BST                                |\n");
    printf("| 5  - View BST Graph                                    |\n");
    printf("|                                                        |\n");
    printf("| 6  - Balance BST - Build AVL Tree                      |\n");
    printf("| 7  - Add node to AVL Tree                              |\n");
    printf("| 8  - Delete node in AVL Tree                           |\n");
    printf("| 9  - View AVL Graph                                    |\n");
    printf("|                                                        |\n");
    printf("| 10 - Input maximum number of comparisons               |\n");
    printf("| 11 - Build hash table based on the file                |\n");
    printf("| 12 - View hash table                                   |\n");
    printf("| 13 - Add element to hash table                         |\n");
    printf("| 14 - Delete element from hash table                    |\n");
    printf("|                                                        |\n");
    printf("| 15 - Search data in BST                                |\n");
    printf("| 16 - Search data in AVL                                |\n");
    printf("| 17 - Search data in Hash table                         |\n");
    printf("| 18 - Search data in file                               |\n");
    printf("| 19 - Compare time and memory efficiency                |\n");
    printf("|                                                        |\n");
    printf("| 0 - Exit                                               |\n");
    printf("+--------------------------------------------------------+\n");
    printf("\nYour choice: ");
}

void clean_stdin()
{
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void input_file_name(FILE **f)
{
    printf("Currently you have ");

    if (*f == NULL)
        printf("no files.\n");
    else
        printf("a file!\n");

    printf("Please, input path to your new file.\n");
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("Current working directory: %s\n", cwd);
    
    char filename[MAX_FILE_NAME_LEN + 1];

    printf("Your input: ");
    scanf("%s", filename);

    FILE *tmp = fopen(filename, "r");

    if (tmp == NULL)
        printf("No file!");
    else
    {
        if (*f != NULL)
            fclose(*f);
        *f = tmp;
    }
}

int read_file_to_bst(bst_node_t **bst, FILE *f)
{
    int rc = OK;
    int n = 0;
    int cur_num = 0;

    if (f == NULL)
        rc = NO_FILE;
    else if (bst != NULL)
    {
        bst_free_tree(*bst);
        *bst = NULL;

        while (!feof(f) && fscanf(f, "%d", &cur_num) == 1)
        {
            bst_node_t *tmp = bst_create_node(cur_num);
            *bst = bst_add_node(*bst, tmp);

            if (tmp != NULL)
                n += 1;
        }

        if (n != 0)
            rc = OK;
        else
            rc = NO_FILE;
        
        rewind(f);
    }
    else
        rc = WRONG_ARGS;
    
    return rc;
}