#include <stdio.h>

#include "../inc/time_func.h"
#include "../inc/arr_queue.h"
#include "../inc/errors.h"
#include "../inc/list_queue.h"

int main(void)
{
    setbuf(stdout, NULL);

    int rc = OK;

    list_queue queue; float tmp;

    list_queue_init(&queue);

    list_queue_push(&queue, 5.0);
    list_queue_push(&queue, 4.0);
    list_queue_push(&queue, 2.0);

    list_queue_pop(&queue, &tmp);

    list_queue_print(&queue);
    
    return rc;
}