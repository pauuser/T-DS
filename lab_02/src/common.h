#ifndef _H_COMMON_
#define _H_COMMON_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/time.h>

#define OK 0
#define INVALID_MENU_NUM -1
#define WRONG_FILE_NAME -2
#define BROKEN_FILE -3
#define ALREADY_HAVE_INPUT -4
#define NO_BOOKS -5

#define MAX_FIELD_LEN 20
#define MAX_BOOKS_NUM 100
#define MAX_STR_LEN 20
#define MAX_FIELDS_NUM 8
#define MAX_LINE_LEN 500 // досчитать

#define YES 1
#define NO 0
#define ASCII_NUM_DIFF 48

typedef enum { TECHNICAL, FICTION, CHILDREN } book_t;

typedef enum { NOVEL, PLAY, FICTION_POETRY } fiction_info_t;

typedef enum { FAIRYTAILS, CHILDREN_POETRY } children_info_t;

typedef enum { STATE, TRANSLATED } tech_pub_t;

typedef struct
{
	char area[MAX_FIELD_LEN + 1];
    tech_pub_t type;
    short int year;
} tech_info_t;

typedef struct
{
	char name[MAX_FIELD_LEN + 1];
	char title[MAX_FIELD_LEN + 1];
	char publisher[MAX_FIELD_LEN + 1];
	int pages;
	book_t type;
	union spec_u
    {
        tech_info_t tech_info;
        fiction_info_t fiction_info;
        children_info_t children_info;
    } spec;
} book;

typedef struct
{
    book data[MAX_BOOKS_NUM];
    short int quantity;
} book_table;

typedef struct
{
    short int n;
    /* | 0 - old | 1 - new | 2 - value | */
    short int pages[MAX_BOOKS_NUM][3];
} page_key_table;

#endif