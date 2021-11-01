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

    double sum_time_in_line1 = 0;
    double sum_time_in_line2 = 0;

    double next_request1 = rtime(min_t1, max_t1);
    double next_request2 = rtime(min_t2, max_t2);

    double sum_process_handler1 = 0.0;
    double sum_process_handler2 = 0.0;

    int rc = OK;

    while (!(handler.type1_processed == requests_num && handler.in_process != ONE))
    {
        // пополнение первой очереди
        if (fabs(next_request1 - cur_time) < EPS)
        {
            next_request1 += rtime(min_t1, max_t1);
            rc = arr_queue_push(&queue1, cur_time);

            if (rc != OK)
            {
                printf("The queue is full!\n");
                break;
            }

            sum_len1++;
        }
        
        // пополнение второй очереди
        if (fabs(next_request2 - cur_time) < EPS)
        {
            next_request2 += rtime(min_t2, max_t2);
            rc = arr_queue_push(&queue2, cur_time);

            if (rc != OK)
            {
                printf("The queue is full!\n");
                break;
            }

            sum_len2++;
        }

        // если очередь пустая - добавляем время простоя
        if ((queue1.count == 0) && (queue2.count == 0) && (handler.in_process = NONE))
            handler.time_standby += time_step;
        
        // обработчик освободился
        else if (fabs(handler.time_finish - cur_time) < EPS)
        {
            handler.in_process = NONE;
            if (handler.type1_processed % 100 == 0)
            {
                printf("========================================\n");
                printf("PROCESSED : %d requests from Queue 1!\n", queue1.count);

                printf("Queue 1:\n");
                printf("Average queue len: %d\n", (int) ((double) sum_len1 / (cur_time * 100)));
                printf("Current queue len: %d\n", queue1.count);
                printf("Requests in:  %d\n", handler.type1_processed + queue1.count);
                printf("Requests out: %d\n", handler.type1_processed);
                printf("Average time in queue: %f\n", sum_time_in_line1 / handler.type1_processed);

                printf("Queue 2:\n");
                printf("Average queue len: %d\n", (int) ((double) sum_len2 / (cur_time * 100)));
                printf("Current queue len: %d\n", queue2.count);
                printf("Requests in:  %d\n", handler.type2_processed + queue2.count);
                printf("Requests out: %d\n", handler.type2_processed);
                printf("Average time in queue: %f\n\n", sum_time_in_line2 / handler.type2_processed);
            }
        }    
        
        // добавление в обработчик элемента первой очереди
        if (queue1.count != 0 && handler.in_process == NONE)
        {
            double come_time = 0.0;
            arr_queue_pop(&queue1, &come_time);

            double process_time = rtime(min_pr1, max_pr1);
            handler_add(&handler, ONE, cur_time, process_time);

            sum_time_in_line1 += cur_time - come_time;
            sum_process_handler1 += process_time;
        }
        // добавление в обработчик элемента второй очереди
        else if (queue2.count != 0 && handler.in_process == NONE)
        {
            double come_time = 0.0;
            arr_queue_pop(&queue2, &come_time);

            double process_time = rtime(min_pr2, max_pr2);
            handler_add(&handler, ONE, cur_time, process_time);

            sum_time_in_line2 += cur_time - come_time;
            sum_process_handler2 += process_time;
        }

        cur_time += time_step;
    }

    printf("=======================================\n");
    printf("FINISH!\n");
    printf("Overall time: %f\n", cur_time);
    printf("Handler standby: %f\n\n", handler.time_standby);

    printf("Queue 1:\n");
    printf("Requests in:  %d\n", handler.type1_processed + queue1.count);
    printf("Requests out: %d\n\n", handler.type1_processed);

    printf("Queue 2:\n");
    printf("Requests in:  %d\n", handler.type2_processed + queue2.count);
    printf("Requests out: %d\n\n", handler.type2_processed);

    printf("TOTAL:\n");
    printf("Requests in:  %d\n", handler.type2_processed + queue2.count + handler.type1_processed + queue1.count);
    printf("Requests out: %d\n\n", handler.type1_processed + handler.type2_processed);

    printf("RESULTS CHECK:\n");
    printf("Queue 1:\n");
    printf("[IN]:\n");
    printf("Expected time : %f\n", 0.5 * (max_t1 + min_t1) * requests_num);
    printf("Real time     : %f\n", );
    printf("[OUT]:\n");
    printf("Expected time : %f\n", 0.5 * (max_pr1 + min_pr2) * requests_num);
    printf("Real time     : %f\n", sum_process_1);


}