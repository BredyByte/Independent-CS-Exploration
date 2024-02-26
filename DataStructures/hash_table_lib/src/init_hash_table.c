#include "header.h"

void init_hash_table(player **hash_table)
{
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }
}
