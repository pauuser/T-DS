#include "../inc/graph.h"

void bst_to_dot(bst_node_t *tree, void *param)
{
    FILE *f = param;

    if (tree && tree->left)
        fprintf(f, "%d -> %d;\n", tree->num, tree->left->num);

    if (tree && tree->right)
        fprintf(f, "%d -> %d;\n", tree->num, tree->right->num);
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
    FILE *file = fopen("graph.gv", "w");

    bst_export_to_dot(file, "BST", bst);

    system("./build_graph.bat");

    fclose(file);
}
