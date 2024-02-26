#include "header.h"

void print_hash_table(player **hash_table)
{
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        if (hash_table[i] == NULL)
            printf ("\t%i\t-----\n", i);
        else
		{
			printf ("\t%i: ", i);
			player *tmp = hash_table[i];
			while (tmp != NULL)
			{
				printf("\t%i - ", tmp->index);
				tmp = tmp->next;
			}
			printf("\n");
		}
    }
}
