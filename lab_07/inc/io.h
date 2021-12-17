#ifndef __H_IO__
#define __H_IO__

#include <stdio.h>
#include "graph.h"

// Функция ввода графа с клавиатуры
graph_t *input_graph(void);

// Функция очистки потока ввода
void clean_stdin();

// Функция перевода графа в формат dot
void graph_to_dot(graph_t *tree, void *param);

// Функция экспорта графа в dot
void graph_export_to_dot(FILE *f, const char *tree_name, graph_t *graph);

// Функция вывода графа в dot
void graph_output_dot(graph_t *graph);

// Функция печати приветственного сообщения
void print_welcome();

// Функция печати меню
void print_menu();

#endif