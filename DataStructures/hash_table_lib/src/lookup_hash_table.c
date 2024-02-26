#include "header.h"

player *lookup_hash_table(int player_index, player **hash_table)
{
    int hash_index = get_hash(player_index);
	player *tmp = hash_table[hash_index];
	while (tmp != NULL && tmp->index != player_index)
	{
		tmp = tmp->next;
	}
	return (tmp);
}
