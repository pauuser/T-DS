#include "../inc/handler.h"

/*
Инициализация обслуживающего аппарата
*/
void handler_init(handler *handler)
{
    handler->type1_processed = 0;
    handler->type2_processed = 0;

    handler->time_standby = 0;
    handler->time_finish = 0;
    handler->in_process = NONE;
}

/*
Добавление запроса в обработчик
*/
void handler_add(handler *handler, request_t type, double cur_time, double process_time)
{
    if (type == ONE)
        handler->type1_processed += 1;
    if (type == TWO)
        handler->type2_processed += 1;
    
    if (fabs(process_time) < EPS)
        handler->in_process = type;
    else
        handler->in_process = NONE;
    
    handler->time_finish = cur_time + process_time;    
}