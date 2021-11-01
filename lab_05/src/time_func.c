#include "../inc/time_func.h"

double rtime(double left, double right)
{
    double a = (right - left) * ((double)rand() / (double)RAND_MAX) + left;
    return (double)((int)(a * 1000)) / 1000;
}