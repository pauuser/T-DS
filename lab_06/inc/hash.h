#ifndef __H_HASH__
#define __H_HASH__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "file.h"
#include "errors.h"

typedef struct hash_t hash_t;

typedef struct node_t node_t;

struct hash_t
{
    int size;
    node_t **array;
};

struct node_t
{
    int data;
    node_t *next;
};

// Функция создания хеш-таблицы
hash_t *hash_create(int size);

// Функция освобвождения памяти из под хеш-таблицы
void hash_free(hash_t *table);

// Функция добавления элемента в хеш-таблицу
void hash_add(hash_t *table, int num);

// Функция удаления элемента из хеш-таблицы
void hash_delete(hash_t *table, int num);

// Функция реструктуризации хеш-таблицы
void hash_restructure(hash_t **table);

// Функция поиска в хеш-таблице
int hash_search(hash_t *table, int num, int *comp_number);

// Хеш-функция
int hash_function(int key, int m);

// Функция просмотра хеш-таблицы
void hash_read(hash_t *table);

// Функция просмотра списка
void list_read(node_t *start);

// Функция чтения списка в хеш-таблицу
int read_file_to_hash(hash_t **table, FILE *f);

// Функция проверки числа на простоту
int is_prime(int n);

// Функция выбора ближайшего простого числа
int closest_prime(int n);

// Функция подсчёта числа коллизий в хеш-таблице
int hash_count_collisions(hash_t *table);

#endif