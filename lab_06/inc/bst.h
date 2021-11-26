#ifndef __H_BST__
#define __H_BST__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct bst_node_t bst_node_t;

struct bst_node_t
{
    int num;
    bst_node_t *left;
    bst_node_t *right;
};

bst_node_t *bst_create_node(int num);

bst_node_t *bst_add_node(bst_node_t *head, bst_node_t *node);

bst_node_t *bst_search_node(bst_node_t *head, int num);

void bst_traverse(bst_node_t *tree, void (*f)(bst_node_t*, void*), void *arg, char *order);

void bst_node_print(bst_node_t *node, void *arg);

bst_node_t *bst_delete_node(bst_node_t *head, int num);

#endif