#ifndef HEADER_H
# define HEADER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct player
{
    int index;
    int lose_val;
	struct player *next;
}   player;

unsigned int get_hash(int index);
player *delete_hash_table(int player_index, player **hash_table);
void print_hash_table(player **hash_table);
bool insert_hash_table(player *p, player **hash_table);
void init_hash_table(player **hash_table);
player *lookup_hash_table(int player_index, player **hash_table);

#endif
