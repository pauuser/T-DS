#include "../inc/karger.h"

/*
Функция поиска минимального разреза алгоритмом Каргера
*/
int karger_mincut(graph_t *graph, edgelist_t **out_list)
{
	int V = graph->V, E = graph->E; // Количества вершин и ребер
	edge_t *edge = graph->edge; // Массив всех граней

    // Выделяем память под массив подмножеств, в котором будем хранить
    // информацию об объединении вершин
	struct subset_t *subsets = malloc(V * sizeof(struct subset_t));

	for (int v = 0; v < V; v++)
	{
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}

	int vertices = V; // сохраняем число вершин

	while (vertices > 2)
	{
        int i = rand() % E; // номер случайного ребра
        
        // ищем в каких множествах находятся конца выбранного ребра
        int subset1 = find_parent(subsets, edge[i].src);
        int subset2 = find_parent(subsets, edge[i].dest);

        // если ребро соединяет вершины в разных множествах, удаляем его
        if (subset1 != subset2)
        {
            //printf("Contracting edge %d-%d\n", edge[i].src, edge[i].dest);
            vertices--;
            union_sets(subsets, subset1, subset2); // соединяем две вершины в одну
        }
	}

    // В конце осталось две вершины. Рёбра между ними - искомые.
	int cutedges = 0;
	for (int i = 0; i < E; i++)
	{
        // Проходим по каждому ребру и смотрим, не оно ли осталось
		int subset1 = find_parent(subsets, edge[i].src);
		int subset2 = find_parent(subsets, edge[i].dest);

		if (subset1 != subset2)
        {
            // printf("%d - %d\n", edge[i].src, edge[i].dest);
            *out_list = edgelist_add(*out_list, edge[i]);
		    cutedges++;
        }
	}

    free(subsets);

	return cutedges;
}

/*
Функция, повторяющая алгоритм Каргера некоторое число раз
для увеличения вероятности верного ответа
*/
void karger(graph_t *graph)
{
    // Настройка работы генератора случайных чисел
	srand(time(NULL));

	int n = graph->V;

	int cnt = (int)(((double)(n * n)) * (log2(n) / log2(2.71828)));

	if (graph != NULL)
	{
		// int64_t s1, e1;
		// s1 = tick();
		int min = graph->E + 1;
		edgelist_t *list = NULL;

		int cur_min = graph->E + 1;
		for (int i = 0; i < cnt; i++)
		{
			edgelist_t *tmp = NULL;
			cur_min = karger_mincut(graph, &tmp);

			if (cur_min < min)
			{
				min = cur_min;

				if (list != NULL)
					edgelist_free(list);
				list = tmp;
			}
			else
				edgelist_free(tmp);
		}
		// e1 = tick();
		printf("\nAnswer: %d\n", min);
        if (min == 0)
            printf("Graph is not well-connected");
        else
        {
		    printf("The list of edges to delete: \n");
		    edgelist_print(list);
        }
		// printf("Time of processing: %d\n", (int)(e1 - s1));

        edgelist_free(list);
	}
}