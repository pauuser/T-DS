#ifndef __H_AVL__
#define __H_AVL__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bst.h"
#include "errors.h"

typedef struct avl_node_t avl_node_t;

struct avl_node_t
{
    int num;
    avl_node_t *left;
    avl_node_t *right;
    int height;
};

avl_node_t *avl_create_node(int num);

avl_node_t *avl_add_node(avl_node_t *head, avl_node_t *node);

avl_node_t *avl_search_node(avl_node_t *head, int num, int *comp_number);

int avl_node_height(avl_node_t *node);

int max(int a, int b);

avl_node_t *avl_ll_rotation(avl_node_t *tree);

avl_node_t *avl_rr_rotation(avl_node_t *tree);

avl_node_t *avl_lr_rotation(avl_node_t *tree);

avl_node_t *avl_rl_rotation(avl_node_t *tree);

void avl_traverse(avl_node_t *tree, void (*f)(avl_node_t*, void*), void *arg, char *order);

void avl_node_print(avl_node_t *node, void *arg);

avl_node_t *avl_delete_node(avl_node_t *head, int num);

int get_balance(avl_node_t *head);

int avl_create_from_bst(bst_node_t *head, avl_node_t **src);

void avl_free_node(avl_node_t *node, void *arg);

void avl_free_tree(avl_node_t *head);

void add_bst_to_avl(bst_node_t *node, void *arg);

#endif