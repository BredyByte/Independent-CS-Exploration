#include "header.h"

bool insert_hash_table(player *p, player **hash_table)
{
    if (p == NULL)
        return (false);
    int index = get_hash(p->index);
	p->next = hash_table[index];
	hash_table[index] = p;
    return (true);
}
