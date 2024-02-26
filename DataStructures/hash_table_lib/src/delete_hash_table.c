#include "header.h"

player *delete_hash_table(int player_index, player **hash_table)
{
    int hash_index = get_hash(player_index);
	player *tmp = hash_table[hash_index];
	player *prev = NULL;
	while (tmp != NULL && tmp->index != player_index)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (NULL);
	if (prev == NULL)
		hash_table[hash_index] = tmp->next;
	else
		prev->next = tmp->next;
	return (tmp);
}
