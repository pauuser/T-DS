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

// Функция создания ячейки АВЛ-дерева
avl_node_t *avl_create_node(int num);

// Функция добавления элемента в АВЛ-дерево
avl_node_t *avl_add_node(avl_node_t *head, avl_node_t *node);

// Функция поиска ноды в АВЛ-дереве
avl_node_t *avl_search_node(avl_node_t *head, int num, int *comp_number);

// Функция определения высоты вершины
int avl_node_height(avl_node_t *node);

// Функция максимума из двух чисел
int max(int a, int b);

// Функция левого-левого поворота
avl_node_t *avl_ll_rotation(avl_node_t *tree);

// Функция правого-правого поворота
avl_node_t *avl_rr_rotation(avl_node_t *tree);

// Функция левого-правого поворота
avl_node_t *avl_lr_rotation(avl_node_t *tree);

// Функция правого-левого поворота
avl_node_t *avl_rl_rotation(avl_node_t *tree);

// Функция обхода АВЛ-дерева
void avl_traverse(avl_node_t *tree, void (*f)(avl_node_t*, void*), void *arg, char *order);

// Функция печати вершины АВЛ-дерева
void avl_node_print(avl_node_t *node, void *arg);

// Функция удаления ноды АВЛ-дерева
avl_node_t *avl_delete_node(avl_node_t *head, int num);

// Функция, определяющая балансировку в вершине head
int get_balance(avl_node_t *head);

// Функция создания АВЛ-дерева из ДДП
int avl_create_from_bst(bst_node_t *head, avl_node_t **src);

// Функция освобождения памяти из-под вершины АВЛ-дерева
void avl_free_node(avl_node_t *node, void *arg);

// Функция очистки АВЛ-дерева
void avl_free_tree(avl_node_t *head);

// Функция добавления вершин ДДП в АВЛ-дерево
void add_bst_to_avl(bst_node_t *node, void *arg);

#endif