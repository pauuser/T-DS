#ifndef __H_TIME__
#define __H_TIME__

#include <stdlib.h>
#include <inttypes.h>
#include <sys/time.h>

#include "common.h"
#include "list_stack.h"
#include "arr_stack.h"
#include "io.h"

void compare_time();

int64_t tick(void);

void both_fill_file(FILE *f, arr_stack *arr, list_stack **ls, free_mem *mem);

void time_output();

#endif