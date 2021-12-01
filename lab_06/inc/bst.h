#ifndef __H_BST__
#define __H_BST__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "errors.h"

typedef struct bst_node_t bst_node_t;

struct bst_node_t
{
    int num;
    bst_node_t *left;
    bst_node_t *right;
};

// Функция создания вершины ДДП дерева
bst_node_t *bst_create_node(int num);

// Функция добавления вершины в ДДП
bst_node_t *bst_add_node(bst_node_t *head, bst_node_t *node);

// Функция поиска элемента в ДДП
bst_node_t *bst_search_node(bst_node_t *head, int num, int *comp_number);

// Функция обхода ДДП
void bst_traverse(bst_node_t *tree, void (*f)(bst_node_t*, void*), void *arg, char *order);

// Функция печати ноды ДДП
void bst_node_print(bst_node_t *node, void *arg);

// Функция удаление элемента из ДДП
bst_node_t *bst_delete_node(bst_node_t *head, int num);

// Функция очистки ноды ДДП
void bst_free_node(bst_node_t *node, void *arg);

// Функция освобождения памяти из под ДДП
void bst_free_tree(bst_node_t *head);

#endif