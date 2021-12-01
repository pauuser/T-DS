#ifndef __H_HASH__
#define __H_HASH__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "file.h"
#include "errors.h"

typedef struct hash_t hash_t;

typedef struct node_t node_t;

struct hash_t
{
    int size;
    node_t **array;
};

struct node_t
{
    int data;
    node_t *next;
};

hash_t *hash_create(int size);

void hash_free(hash_t *table);

void hash_add(hash_t *table, int num);

void hash_delete(hash_t *table, int num);

void hash_restructure(hash_t **table);

int hash_search(hash_t *table, int num, int *comp_number);

int hash_function(int key, int m);

void hash_read(hash_t *table);

void list_read(node_t *start);

int read_file_to_hash(hash_t **table, FILE *f);

int is_prime(int n);

int closest_prime(int n);

int hash_count_collisions(hash_t *table);

#endif