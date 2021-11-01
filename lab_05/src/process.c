#include "../inc/process.h"
#include "../inc/arr_queue.h"
#include "../inc/handler.h"
#include "../inc/time_func.h"
#include "../inc/errors.h"

int arr_process_modeling(int requests_num, 
                            double min_t1, double max_t1, 
                                double min_t2, double max_t2,
                                    double min_pr1, double max_pr1,
                                        double min_pr2, double max_pr2)
{
    arr_queue queue1 = { 0 };
    arr_queue_init(&queue1);

    arr_queue queue2 = { 0 };
    arr_queue_init(&queue2);

    handler handler = { 0 };
    handler_init(&handler);

    double time_step = 0.01;
    double cur_time = 0.0;

    long sum_len1 = 0;
    long sum_len2 = 0;

    double next_request1 = rtime(min_t1, max_t1);
    double next_request2 = rtime(min_t2, max_t2);

    int rc = OK;

    while (handler.type1_processed != requests_num)
    {
        // пополнение первой очереди
        if (fabs(next_request1 - cur_time) < EPS)
        {
            next_request1 += rtime(min_t1, max_t1);
            rc = arr_queue_push(&queue1, rtime(min_pr1, max_pr1));

            if (rc != OK)
            {
                printf("The queue is full!\n");
                break;
            }
        }
        
        // пополнение второй очереди
        if (fabs(next_request2 - cur_time) < EPS)
        {
            next_request2 += rtime(min_t2, max_t2);
            rc = arr_queue_push(&queue2, rtime(min_pr2, max_pr2));

            if (rc != OK)
            {
                printf("The queue is full!\n");
                break;
            }
        }

        // если очередь пустая - добавляем время простоя
        if ((queue1.count == 0) && (queue2.count == 0) && (handler.in_process = NONE))
            handler.time_standby += time_step;
        
        else if (fabs(handler.time_finish - cur_time) < EPS)
            handler.
        
        // добавление в обработчик элемента первой очереди
        if (queue1.count != 0 && handler.in_process == NONE)
        {
            double process_time = 0.0;
            arr_queue_pop(&queue1, &process_time);
            handler_add(&handler, ONE, cur_time, process_time);
        }
    }
}