#include "../inc/process.h"
#include "../inc/arr_queue.h"
#include "../inc/list_queue.h"
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

    double time_step = 0.0001;
    double cur_time = 0.0;

    long long sum_len1 = 0;
    long long sum_len2 = 0;

    double sum_time_in_line1 = 0;
    double sum_time_in_line2 = 0;

    double next_request1 = rtime(min_t1, max_t1);
    double next_request2 = rtime(min_t2, max_t2);

    double sum_process_handler1 = 0.0;
    double sum_process_handler2 = 0.0;

    double sum_in_time1 = 0.0;
    double sum_in_time2 = 0.0;

    int last_printed = 50;

    int rc = OK;

    while (!(handler.type1_processed >= requests_num))
    {
        sum_len1 += queue1.count;
        sum_len2 += queue2.count;

        // пополнение первой очереди
        if (fabs(next_request1 - cur_time) < EPS)
        {
            next_request1 += rtime(min_t1, max_t1);
            rc = arr_queue_push(&queue1, cur_time);

            if (rc != OK)
            {
                printf("The queue is full!\n");
                continue;
            }

            sum_in_time1 += next_request1 - cur_time;
        }
        
        // пополнение второй очереди
        if (fabs(next_request2 - cur_time) < EPS)
        {
            next_request2 += rtime(min_t2, max_t2);
            rc = arr_queue_push(&queue2, cur_time);

            if (rc != OK)
            {
                printf("The queue is full!\n");
                continue;
            }

            sum_in_time2 += next_request2 - cur_time;
        }

        // если очередь пустая - добавляем время простоя
        if ((queue1.count == 0) && (queue2.count == 0) && (handler.in_process == NONE))
            handler.time_standby += time_step;
        // обработчик освободился
        else if (fabs(handler.time_finish - cur_time) < EPS)
        {
            handler.in_process = NONE;
            if (handler.type1_processed % 100 < 5 && last_printed < handler.type1_processed)
            {
                // каждые 100 запросов первого типа - печать
                printf("========================================\n");
                printf("PROCESSED : %d requests from Queue 1!\n", handler.type1_processed);

                printf("Queue 1:\n");
                printf("Average queue len: %f\n", (((double) sum_len1) / (cur_time * 10000)));
                printf("Current queue len: %d\n", queue1.count);
                printf("Requests in:  %d\n", handler.type1_processed + queue1.count);
                printf("Requests out: %d\n", handler.type1_processed);
                printf("Average time in queue: %f\n\n", sum_time_in_line1 / handler.type1_processed);

                printf("Queue 2:\n");
                printf("Average queue len: %f\n", ((double) sum_len2 / (cur_time * 10000)));
                printf("Current queue len: %d\n", queue2.count);
                printf("Requests in:  %d\n", handler.type2_processed + queue2.count);
                printf("Requests out: %d\n", handler.type2_processed);
                printf("Average time in queue: %f\n\n", sum_time_in_line2 / handler.type2_processed);

                last_printed = handler.type1_processed + 50;
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
            handler_add(&handler, TWO, cur_time, process_time);

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

    double expected = 0.0;

    printf("RESULTS CHECK:\n\n");

    printf("Queue 1:\n");
    printf("[IN]:\n");
    expected = 0.5 * (max_t1 + min_t1) * requests_num;
    printf("Expected time : %f\n", expected);
    printf("Real time     : %f\n", sum_in_time1);
    printf("Difference    : %.2f%%\n", fabs(expected - sum_in_time1) / expected * 100);
    printf("[OUT]:\n");
    expected = 0.5 * (max_pr1 + min_pr1) * requests_num;
    printf("Expected time : %f\n", expected);
    printf("Real time     : %f\n", sum_process_handler1);
    printf("Difference    : %.2f%%\n\n", fabs(expected - sum_process_handler1) / expected * 100);

    printf("Queue 2:\n");
    printf("[IN]:\n");
    expected = 0.5 * (max_t2 + min_t2) * (handler.type2_processed + queue2.count);
    printf("Expected time : %f\n", expected);
    printf("Real time     : %f\n", sum_in_time2);
    printf("Difference    : %.2f%%\n", fabs(expected - sum_in_time2) / expected * 100);
    printf("[OUT]:\n");
    expected = 0.5 * (max_pr2 + min_pr2) * handler.type2_processed;
    printf("Expected time : %f\n", expected);
    printf("Real time     : %f\n", sum_process_handler2);
    printf("Difference    : %.2f%%\n", fabs(expected - sum_process_handler2) / expected * 100);

    arr_queue_clean(&queue1);
    arr_queue_clean(&queue2);

    arr_queue_free(&queue1);
    arr_queue_free(&queue2);

    return 0;
}

int list_process_modeling(int requests_num, 
                            double min_t1, double max_t1, 
                                double min_t2, double max_t2,
                                    double min_pr1, double max_pr1,
                                        double min_pr2, double max_pr2)
{
    list_queue queue1 = { 0 };
    list_queue_init(&queue1);

    list_queue queue2 = { 0 };
    list_queue_init(&queue2);

    handler handler = { 0 };
    handler_init(&handler);

    double time_step = 0.0001;
    double cur_time = 0.0;

    long long sum_len1 = 0;
    long long sum_len2 = 0;

    double sum_time_in_line1 = 0;
    double sum_time_in_line2 = 0;

    double next_request1 = rtime(min_t1, max_t1);
    double next_request2 = rtime(min_t2, max_t2);

    double sum_process_handler1 = 0.0;
    double sum_process_handler2 = 0.0;

    double sum_in_time1 = 0.0;
    double sum_in_time2 = 0.0;

    int last_printed = 50;

    int rc = OK;

    while (!(handler.type1_processed >= requests_num))
    {
        //printf("%d %d\n", handler.type1_processed, queue1.count);
        //list_queue_print(&queue1);
        sum_len1 += queue1.count;
        sum_len2 += queue2.count;

        // пополнение первой очереди
        if (fabs(next_request1 - cur_time) < EPS)
        {
            next_request1 += rtime(min_t1, max_t1);
            rc = list_queue_push(&queue1, cur_time);

            if (rc != OK)
            {
                printf("The queue is full!\n");
                continue;
            }

            sum_in_time1 += next_request1 - cur_time;
        }
        
        // пополнение второй очереди
        if (fabs(next_request2 - cur_time) < EPS)
        {
            next_request2 += rtime(min_t2, max_t2);
            rc = list_queue_push(&queue2, cur_time);

            if (rc != OK)
            {
                printf("The queue is full!\n");
                continue;
            }

            sum_in_time2 += next_request2 - cur_time;
        }

        // если очередь пустая - добавляем время простоя
        if ((queue1.count == 0) && (queue2.count == 0) && (handler.in_process == NONE))
            handler.time_standby += time_step;
        // обработчик освободился
        else if (fabs(handler.time_finish - cur_time) < EPS)
        {
            handler.in_process = NONE;
            if (handler.type1_processed % 100 < 5 && last_printed < handler.type1_processed)
            {
                // каждые 100 запросов первого типа - печать
                printf("========================================\n");
                printf("PROCESSED : %d requests from Queue 1!\n", handler.type1_processed);

                printf("Queue 1:\n");
                printf("Average queue len: %f\n", (((double) sum_len1) / (cur_time * 10000)));
                printf("Current queue len: %d\n", queue1.count);
                printf("Requests in:  %d\n", handler.type1_processed + queue1.count);
                printf("Requests out: %d\n", handler.type1_processed);
                printf("Average time in queue: %f\n\n", sum_time_in_line1 / handler.type1_processed);

                printf("Queue 2:\n");
                printf("Average queue len: %f\n", ((double) sum_len2 / (cur_time * 10000)));
                printf("Current queue len: %d\n", queue2.count);
                printf("Requests in:  %d\n", handler.type2_processed + queue2.count);
                printf("Requests out: %d\n", handler.type2_processed);
                printf("Average time in queue: %f\n\n", sum_time_in_line2 / handler.type2_processed);

                last_printed = handler.type1_processed + 50;
            }
        } 
        
        // добавление в обработчик элемента первой очереди
        if (queue1.count != 0 && handler.in_process == NONE)
        {
            double come_time = 0.0;
            list_queue_pop(&queue1, &come_time);

            double process_time = rtime(min_pr1, max_pr1);
            handler_add(&handler, ONE, cur_time, process_time);

            sum_time_in_line1 += cur_time - come_time;
            sum_process_handler1 += process_time;
        }
        // добавление в обработчик элемента второй очереди
        else if (queue2.count != 0 && handler.in_process == NONE)
        {
            double come_time = 0.0;
            list_queue_pop(&queue2, &come_time);

            double process_time = rtime(min_pr2, max_pr2);
            handler_add(&handler, TWO, cur_time, process_time);

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

    double expected = 0.0;

    printf("RESULTS CHECK:\n\n");

    printf("Queue 1:\n");
    printf("[IN]:\n");
    expected = 0.5 * (max_t1 + min_t1) * requests_num;
    printf("Expected time : %f\n", expected);
    printf("Real time     : %f\n", sum_in_time1);
    printf("Difference    : %.2f%%\n", fabs(expected - sum_in_time1) / expected * 100);
    printf("[OUT]:\n");
    expected = 0.5 * (max_pr1 + min_pr1) * requests_num;
    printf("Expected time : %f\n", expected);
    printf("Real time     : %f\n", sum_process_handler1);
    printf("Difference    : %.2f%%\n\n", fabs(expected - sum_process_handler1) / expected * 100);

    printf("Queue 2:\n");
    printf("[IN]:\n");
    expected = 0.5 * (max_t2 + min_t2) * (handler.type2_processed + queue2.count);
    printf("Expected time : %f\n", expected);
    printf("Real time     : %f\n", sum_in_time2);
    printf("Difference    : %.2f%%\n", fabs(expected - sum_in_time2) / expected * 100);
    printf("[OUT]:\n");
    expected = 0.5 * (max_pr2 + min_pr2) * handler.type2_processed;
    printf("Expected time : %f\n", expected);
    printf("Real time     : %f\n", sum_process_handler2);
    printf("Difference    : %.2f%%\n", fabs(expected - sum_process_handler2) / expected * 100);

    list_queue_clean(&queue1);
    list_queue_clean(&queue2);

    return 0;
}
