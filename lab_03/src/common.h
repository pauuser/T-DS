#ifndef _H_COMMON_
#define _H_COMMON_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OK 0

#define YES 1
#define NO 0

typedef struct ptr_list
{
    long long i;
    struct ptr_list *next;
} ptr_list;

typedef struct
{
    long long nz;
    long double *a;
    long long *ja;
    struct ptr_list ia;
} csr_matrix;

typedef long long ll;
typedef long double ld;

void print_menu();

void print_welcome();

#endif