#include "../inc/time_func.h"

float rtime(int left, int right)
{
    return (right - left) * ((float)rand() / (float)RAND_MAX) + left;
}