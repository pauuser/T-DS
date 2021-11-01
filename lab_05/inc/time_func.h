#ifndef __H_TIME_FUNC__
#define __H_TIME_FUNC__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>

#include "../inc/arr_queue.h"
#include "../inc/list_queue.h"

double rtime(double left, double right);

int64_t tick(void);

void measure_time();

#endif