#ifndef H_CMN_FUNC
#define H_CMH_FUNC

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MANTISSA_SIZE 32
#define E_SIZE 5
#define MAX_STR_SIZE MANTISSA_SIZE + E_SIZE + 3
#define MAX_POWER 99999

#define OK 0
#define INVALID_INPUT -1
#define TOO_BIG_FLOATING -2
#define TOO_BIG_INT -3
#define NO_DATA -4
#define DIV_BY_ZERO -5

#define INVALID_FORMAT -1
#define NUM_OVERFLOW -6

#define YES 1
#define NO 0

#define ASCII_NUM_DIFF 48

struct long_num
{
    char sign_mant;
    char mantissa[MANTISSA_SIZE + 1];
    int exp;
};

typedef struct long_num long_num;

#endif
