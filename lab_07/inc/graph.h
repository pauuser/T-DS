#ifndef __H_GRAPH__
#define __H_GRAPH__

#include <stdlib.h>
#include <stdio.h>

/*
Структура ребра графа
src - начало ребра
dest - конец ребра
*/
typedef struct edge_t
{
	int src;
    int dest;
} edge_t;

/*
Структура графа
V - число вершин
E - число рёбер
*edge - массив рёбер
*/
typedef struct graph_t
{
	int V;
    int E;
	edge_t* edge;
} graph_t;

/*
Список для хранения минимального числа рёбер
*/
typedef struct edgelist_t
{
    edge_t edge;
    struct edgelist_t *next;
} edgelist_t;

// Функция создания графа
struct graph_t* create_graph(int V, int E);

edgelist_t *edgelist_node(edge_t a);

edgelist_t *edgelist_add(edgelist_t *list, edge_t a);

void edgelist_free(edgelist_t *list);

void edgelist_print(edgelist_t *list);

void graph_free(graph_t **graph);

#endif