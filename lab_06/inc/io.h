#ifndef __H_IO__
#define __H_IO__

#include <stdio.h>
#include <stdlib.h>

#include "bst.h"
#include "errors.h"

#define MAX_FILE_NAME_LEN 255

// Вывод приветственного сообщения
void print_welcome();

// Вывод меню
void print_menu();

// Функция очистки ввода
void clean_stdin();

// Функция чтения имени файла
void input_file_name(FILE **f);

// Функция чтения файла в структуру ДДП
int read_file_to_bst(bst_node_t **bst, FILE *f);

#endif