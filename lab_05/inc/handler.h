#ifndef __H_HANDLER__
#define __H_HANDLER__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../inc/process.h"

/*
Описание типа заявок
*/
typedef enum { NONE, ONE, TWO } request_t;

/*
Описание обслуживающего аппарата
*/
typedef struct handler_t
{
    int type1_processed;
    int type2_processed;
    double time_standby;

    request_t in_process;
    double time_finish;
} handler;

// Инициализация обслуживающего аппарата
void handler_init(handler *handler);

// Добавление запроса в обработчик
void handler_add(handler *handler, request_t type, double cur_time, double process_time);

#endif