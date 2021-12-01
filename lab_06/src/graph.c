#include "../inc/graph.h"

void bst_to_dot(bst_node_t *tree, void *param)
{
    FILE *f = param;

    if (tree && tree->left)
        fprintf(f, "%d -> %d;\n", tree->num, tree->left->num);
    else
    {
        if (tree->num < 0)
        {
            fprintf(f, "%d -> null_%d [style=invis];\n", tree->num, -tree->num);
            fprintf(f, "null_%d[style=invis];\n", -tree->num);
        }
        else
        {
            fprintf(f, "%d -> null%d [style=invis];\n", tree->num, tree->num);
            fprintf(f, "null%d[style=invis];\n", tree->num);
        }
    }

    if (tree && tree->right)
        fprintf(f, "%d -> %d;\n", tree->num, tree->right->num);
    else
    {
        if (tree->num < 0)
        {
            fprintf(f, "%d -> null_%d [style=invis];\n", tree->num, -tree->num);
            fprintf(f, "null_%d[style=invis];\n", -tree->num);
        }
        else
        {
            fprintf(f, "%d -> null%d [style=invis];\n", tree->num, tree->num);
            fprintf(f, "null%d[style=invis];\n", tree->num);
        }
    }
}

void bst_export_to_dot(FILE *f, const char *tree_name,
                                       bst_node_t *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);

    bst_traverse(tree, bst_to_dot, f, "in");

    fprintf(f, "}\n");
}

void bst_output_dot_graph(bst_node_t *bst)
{
    if (bst == NULL)
        printf("No tree yet!\n");
    else
    {
        FILE *file = fopen("graph.gv", "w");

        bst_export_to_dot(file, "BST", bst);

        fclose(file);

        system("./build_graph.sh");
        system("start \"1.png\"");
    }
}

void avl_to_dot(avl_node_t *tree, void *param)
{
    FILE *f = param;

    if (tree && tree->left)
        fprintf(f, "%d -> %d;\n", tree->num, tree->left->num);
    else
    {
        if (tree->num < 0)
        {
            fprintf(f, "%d -> null_%d [style=invis];\n", tree->num, -tree->num);
            fprintf(f, "null_%d[style=invis];\n", -tree->num);
        }
        else
        {
            fprintf(f, "%d -> null%d [style=invis];\n", tree->num, tree->num);
            fprintf(f, "null%d[style=invis];\n", tree->num);
        }
    }

    if (tree && tree->right)
        fprintf(f, "%d -> %d;\n", tree->num, tree->right->num);
    else
    {
        if (tree->num < 0)
        {
            fprintf(f, "%d -> null_%d [style=invis];\n", tree->num, -tree->num);
            fprintf(f, "null_%d[style=invis];\n", -tree->num);
        }
        else
        {
            fprintf(f, "%d -> null%d [style=invis];\n", tree->num, tree->num);
            fprintf(f, "null%d[style=invis];\n", tree->num);
        }
    }
}

void avl_export_to_dot(FILE *f, const char *tree_name,
                                       avl_node_t *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);

    avl_traverse(tree, avl_to_dot, f, "pre");

    fprintf(f, "}\n");
}

void avl_output_dot_graph(avl_node_t *avl)
{
    if (avl == NULL)
        printf("No tree yet!\n");
    else
    {
        FILE *file = fopen("graph.gv", "w");

        avl_export_to_dot(file, "AVL", avl);

        fclose(file);

        system("./build_graph.sh");
        system("start \"1.png\"");
    }
}
