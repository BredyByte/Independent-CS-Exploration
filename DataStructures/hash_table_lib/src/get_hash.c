#include "header.h"

unsigned int get_hash(int index)
{
    unsigned int hash = 5381;

    while (index)
    {
        hash = ((hash << 5) + hash) ^ (index & 0xFF);
        index >>= 8;
    }
    return (hash % TABLE_SIZE);
}
