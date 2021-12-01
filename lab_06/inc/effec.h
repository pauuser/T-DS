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

void collision_comparison();

void search_with_time(hash_t **table, int max_comp);

void measure_time();

void measure_time_10();

void measure_memory();

#endif