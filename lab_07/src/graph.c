#include "../inc/graph.h"

/*
Функция иницализации графа
Вход: V, E - число вершин и рёбер
Выход: Граф
*/
struct graph_t* create_graph(int V, int E)
{
	graph_t* graph = malloc(sizeof(graph));

    if (graph)
    {
        graph->V = V;
        graph->E = E;

        graph->edge = malloc(sizeof(edge_t) * E);

        // Неудачное выдление памяти
        if (!graph->edge)
        {
            free(graph);
            graph = NULL;
        }
    }

	return graph;
}

edgelist_t *edgelist_node(edge_t a)
{
    edgelist_t *edge = malloc(sizeof(edgelist_t));

    if (edge != NULL)
    {
        edge->edge = a;
        edge->next = NULL;
    }

    return edge;
}

edgelist_t *edgelist_add(edgelist_t *list, edge_t a)
{
    edgelist_t *edge = edgelist_node(a);

    if (list == NULL)
    {
        list = edge;
    }
    else
    {
        edgelist_t *cur = list;
        while (cur->next)
            cur = cur->next;
        
        cur->next = edge;
    }

    return list;
}

void edgelist_free(edgelist_t *list)
{
    while (list)
    {
        edgelist_t *next = list->next;

        free(list);
        list = next;
    }
}

void edgelist_print(edgelist_t *list)
{
    while (list != NULL)
    {
        printf("%d - %d\n", list->edge.src, list->edge.dest);
        list = list->next;
    }
}

void graph_free(graph_t **graph)
{
    if (graph != NULL && *graph != NULL)
    {
        free((*graph)->edge);
        free(*graph);
        *graph = NULL;
    }
}

