#include "common.h"
#include "correct_check.h"
#include "input.h"
#include "division.h"
#include "output.h"

void welcome_print(void)
{
    printf("This programme divedes large numbers.\n");
    printf("The first number must be float, and the second one should be integer\n\n");
    printf("The rules for inputing the numbers are as follows:\n");
    printf("1 - float number can be either in floating point format or exponential form.\n");
    printf("2 - floating point format allows putting the dot in anywhere you want, but\n");
    printf("\t it must be only one dot (or no dot at all)\n");
    printf("3 - exponential form must be written in <+->m.nЕ<+->K format, where\n");
    printf("\t m is mantissa and n is power. Putting signs is mandatory!\n");
    printf("\t the max size of (m + n) is 30, and the max power size is 5.\n");
    printf("4 - number must include only signs, numbers and 'E' symbol. No other\n");
    printf("\t symbol is allowed to be placed in the number.\n\n");
    printf("Uncompliance with the rules leads to errors.\n");
}

void print_error(int rc)
{
    if (rc == INVALID_INPUT)
        printf("Invalid input\n");
    else if (rc == TOO_BIG_FLOATING)
        printf("Too big floating number!\n");
    else if (rc == TOO_BIG_INT)
        printf("Too big integer number!\n");
    else if (rc == NO_DATA)
        printf("No data! Try again!\n");
    else if (rc == DIV_BY_ZERO)
        printf("Division by zero is prohibited!\n");
    else if (rc == NUM_OVERFLOW)
        printf("Machine Zero Reached!\n");
}
