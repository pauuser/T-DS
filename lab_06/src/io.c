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
    printf("\n+-------------------------------------------------------+\n");
    printf("| Choose your option!                                   |\n");
    printf("|                                                       |\n");
    printf("| 1 - Input file name                                   |\n");
    printf("| 2 - Build Binary Search Tree (BST) based on the file  |\n");
    printf("| 3 - Balance BST - Build AVL Tree                      |\n");
    printf("| 4 - Build hash table based on the file                |\n");
    printf("| 5 - Search data in BST, AVL, Hash Table and File      |\n");
    printf("| 6 - Compare time and memory efficiency                |\n");
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

void input_file_name(FILE **f)
{
    printf("Currently you have ");

    if (*f == NULL)
        printf("no files.");
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

void read_file_to_bst(bst_node_t **bst, FILE *f)
{
    int cur_num = 0;
    while (!feof(f) && fscanf(f, "%d", &cur_num) == 1)
    {
        printf("%d : \n", cur_num);
        bst_node_t *tmp = bst_create_node(cur_num);
        *bst = bst_add_node(*bst, tmp);
    }
}