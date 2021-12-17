#ifndef __H_KARGER__
#define __H_KARGER__

#include <math.h>
#include <time.h>

#include "../inc/graph.h"
#include "../inc/set.h"

int karger_mincut(graph_t *graph, edgelist_t **out_list);

void karger(graph_t *graph);

#endif