#ifndef __H_IO__
#define __H_IO__

#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

#define MAX_FILE_NAME_LEN 255

void print_welcome();

void print_menu();

void clean_stdin();

void input_file_name(FILE **f);

void read_file_to_bst(bst_node_t **bst, FILE *f);

#endif