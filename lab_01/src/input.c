#include "common.h"
#include "correct_check.h"
#include "input.h"
#include "division.h"
#include "output.h"

int input_float(long_num *real_num)
{
    int ret_code = OK;

    printf("                         1                       26    31\n");
    printf("                        <------------------------|-----|<----->\n");
    printf("Input the float number: ");

    char temp_str[MAX_STR_SIZE + 2];

    fgets(temp_str, MAX_STR_SIZE + 1, stdin);
    if (strlen(temp_str) > MANTISSA_SIZE + 7)
        ret_code = TOO_BIG_FLOATING;
    else if (*temp_str == '\n')
        ret_code = NO_DATA;
    else
    {
        delete_new_str_sym(temp_str);
        int sc = check_float_string(temp_str);
        if (sc < 0)
            ret_code = sc;
        else
        {
            int exp = 0;
            char *pstart = temp_str;
            (*real_num).sign_mant = *pstart++;

            char mnt[MANTISSA_SIZE + 1];

            int i = 0;
            while (*pstart != 'E' && *pstart)
                mnt[i++] = *pstart++;
            mnt[i] = '\0';
            strcpy((*real_num).mantissa, mnt);

            (*real_num).exp = 0;
            if (*pstart == 'E')
            {
                pstart = pstart + 1;
                char sign_flag = *pstart;
                while (*(++pstart))
                    exp = exp * 10 + (*pstart - ASCII_NUM_DIFF);
                if (sign_flag == '-')
                    exp = -exp;
                (*real_num).exp = exp;
            }
        }
    }
    return ret_code;
}

int input_integer(long_num *int_num)
{
    int ret_code = OK;

    printf("                           1                            30\n");
    printf("                          <------------------------------>\n");
    printf("Input the integer number: ");

    char temp_str[MANTISSA_SIZE + 3];

    fgets(temp_str, MANTISSA_SIZE + 3, stdin);
    if (strlen(temp_str) > MANTISSA_SIZE + 2)
        ret_code = TOO_BIG_INT;
    else if (*temp_str == '\n')
        ret_code = NO_DATA;
    else
    {
        int m_size = 0;

        delete_new_str_sym(temp_str);
        int sc = check_int_string(temp_str, &m_size);
        if (sc < 0)
            ret_code = INVALID_INPUT;
        else if (m_size > 30)
            ret_code = TOO_BIG_INT;
        else
        {
            (*int_num).sign_mant = temp_str[0];
            strcpy((*int_num).mantissa, (temp_str + 1));
            (*int_num).exp = 0;
        }
    }
    if (mantissa_of_zeroes(int_num->mantissa) == 0)
        ret_code = DIV_BY_ZERO;
    return ret_code;
}
