#include <stdio.h>

#include "../inc/time_func.h"
#include "../inc/arr_queue.h"
#include "../inc/errors.h"
#include "../inc/list_queue.h"
#include "../inc/process.h"

int main(void)
{
    setbuf(stdout, NULL);
    srand(time(NULL));

    int rc = OK;

    arr_process_modeling(1000, 1.0, 5.0, 0.0, 3.0, 0.0, 4.0, 0.0, 1.0);
    
    return rc;
}