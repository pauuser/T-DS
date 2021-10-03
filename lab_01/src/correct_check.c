#include "common.h"
#include "correct_check.h"
#include "input.h"
#include "division.h"
#include "output.h"

int check_float_string(char *str)
{
    int ret_code = OK;
    int met_e = 0;
    int met_dot = 0;
    int n = 0, m = 0;
    if (*str != '+' && *str != '-')
        ret_code = INVALID_FORMAT;
    else
    {
        char *pstart = str + 1;
        while (*pstart && ret_code == OK)
        {
            if (*pstart == 'E')
                met_e += 1;
            else if (*pstart == '.' && met_e > 0)
                ret_code = INVALID_INPUT;
            else if (*pstart == '.')
                met_dot += 1;
            else if ((*pstart == '+' || *pstart == '-') && *(pstart - 1) != 'E' && *(pstart + 1) != '\0')
                ret_code = INVALID_INPUT;
            else if ((*pstart > '9' || *pstart < '0') && *pstart != '+' && *pstart != '-')
                ret_code = INVALID_INPUT;
            else if (met_e == 0 && *pstart <= '9' && *pstart >= '0')
                m += 1;
            else if (met_e == 1)
                n += 1;
            pstart++;
        }
    }
    if (n != 0)
        n = n - 1;
    if (m == 0 && met_dot != 0)
        ret_code = INVALID_INPUT;
    else if (met_dot == 0 && m == 0 && n == 0)
        ret_code = INVALID_INPUT;
    else if (met_dot > 1 || met_e > 1)
        ret_code = INVALID_INPUT;
    else if (m > 30)
        ret_code = TOO_BIG_FLOATING;
    return ret_code;
}

int check_int_string(char *str, int *m)
{
    int ret_code = OK;
    if (*str != '+' && *str != '-')
        ret_code = INVALID_FORMAT;
    else
    {
        str++;
        while (*str && ret_code == OK)
        {
            if (*str < '0' || *str > '9')
                ret_code = INVALID_FORMAT;
            else
                *m = *m + 1;
            str++;
        }
    }
    return ret_code;
}

int mantissa_of_zeroes(char *mnt)
{
    int num_met = 0;
    while (*mnt)
    {
        if (*(mnt) != '0' && *(mnt) != '.')
            num_met += 1;
        mnt++;
    }
    return num_met;
}
