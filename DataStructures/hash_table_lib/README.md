# 🗃️ Hash Tables 🗃️


## Description

Hash tables are a type of data structure in which the address or the index value of the data element is generated from a hash function, ```get_hash``` in my case. That makes accessing the data faster as the index value behaves as a key for the data value. In other words Hash table stores key-value pairs but the key is generated through a hashing function.

This repository is a simple example, it's main purpose is to show how hash tables work and how to implement them in C. You could change, add, rewrite and modificate the functions depends
on your needs.

Here is an example of get_hash fucntion for strings:
```
unsigned int get_hash(const char* str)
{
    unsigned int hash = 0;
    size_t length = strlen(str);

    for (size_t i = 0; i < length; ++i)
        hash = (hash * 31) + str[i];

    return (hash % TABLE_SIZE);
}
```

## Example of using

For test you could execute ```make test``` command in the root of repository, it will compile all files and create executable file ```test```. Then you could execute ```./test``` command and see the result.

## Hash_table implemented library [uthash.h](https://troydhanson.github.io/uthash/)
### Example code
```
#include "uthash.h"

typedef struct {
	int key;
	UT_hash_handle hh;
} hash_table;

hash_table *hash = NULL, *elem, *tmp;

bool containsDuplicate(int* nums, int numsSize)
{
    if (numsSize == 1)
        return (false);
    int res = 0;
    for (int i = 0; i < numsSize; i++)
    {
        HASH_FIND_INT(hash, &nums[i], elem);
        if (!elem)
        {
            elem = malloc(sizeof(hash_table));
            elem->key = nums[i];
            HASH_ADD_INT(hash, key, elem);
        }
        else
        {
            res = 1; 
            break;
        }
    }

    HASH_ITER(hh, hash, elem, tmp) {
        HASH_DEL(hash, elem); free(elem);
    }
    return (res);
}
