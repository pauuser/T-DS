#include "../inc/time_func.h"

double rtime(int left, int right)
{
    return (right - left) * ((double)rand() / (double)RAND_MAX) + left;
}