#ifndef __H_IO__
#define __H_IO__

#include <stdio.h>
#include "graph.h"

graph_t *input_graph(void);

void clean_stdin();

void graph_to_dot(graph_t *tree, void *param);

void graph_export_to_dot(FILE *f, const char *tree_name, graph_t *graph);

void graph_output_dot(graph_t *graph);

void print_welcome();

void print_menu();

#endif