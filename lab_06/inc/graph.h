#ifndef __H_GRAPH__
#define __H_GRAPH__

#include <stdio.h>
#include "bst.h"

void bst_to_dot(bst_node_t *tree, void *param);

void bst_export_to_dot(FILE *f, const char *tree_name,
                                       bst_node_t *tree);

void bst_output_dot_graph(bst_node_t *bst);

#endif