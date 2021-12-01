#ifndef __H_EFFEC__
#define __H_EFFEC__

#include <inttypes.h>
#include <sys/time.h>

#include "hash.h"
#include "io.h"
#include "avl.h"
#include "bst.h"
#include "file.h"

#include "errors.h"

// Функция сравнения времени при разном числе коллизий
void collision_comparison();

// Функция поиска в хеш-таблице с выводом времени
void search_with_time(hash_t **table, int max_comp);

// Функция вывода временной характеристики
void measure_time();

// Функция, выполняющая временные замеры
void measure_time_10();

// Функция измерения числа затраченной памяти
void measure_memory();

#endif