#include "common.h"
#include "correct_check.h"
#include "input.h"
#include "division.h"
#include "output.h"

int main(void)
{
    int ret_code = OK;

    setbuf(stdout, NULL);
    welcome_print();

    long_num real_num, int_num;
    int rcf = input_float(&real_num);
    int rci = input_integer(&int_num);
    if (rci == OK && rcf == OK)
    {
        if (mantissa_of_zeroes(real_num.mantissa) == 0)
            printf("\nRESULT: +0.0E+0\n");
        else
        {
        long_num result = divide_float_by_int(&real_num, &int_num);
        reformat_long_num(&result);
        if (abs(result.exp) > MAX_POWER)
            ret_code = NUM_OVERFLOW;
        else
            printf("\nRESULT: %c%sE%+d\n", result.sign_mant, result.mantissa, result.exp);
        }
    }
    else
        ret_code = (rcf == OK ? rci : rcf);
    print_error(ret_code);
    return ret_code;
}
