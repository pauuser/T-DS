#ifndef __H_KARGER__
#define __H_KARGER__

#include <math.h>
#include <time.h>

#include "graph.h"
#include "set.h"
// #include "effec.h"

// Функция поиска минимального разреза алгоритмом Каргера
int karger_mincut(graph_t *graph, edgelist_t **out_list);

// Функция, повторяющая алгоритм Каргера некоторое число раз
// для увеличения вероятности верного ответа
void karger(graph_t *graph);

#endif