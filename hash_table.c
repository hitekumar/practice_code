#include <stdio.h>

struct hash_node_t  
{
    unsigned int key;
    int data;
    struct hash_node_t *next;
};

struct hash_t
{
    struct hash_node_t *array;
    unsigned int size;
};


int hash_init(struct hash_t *hash, unsigned int size)
{
    int ret = 0;
    struct hash_node_t *node;
    struct hash_node_t *end;
    
    if (hash == NULL || size == 0)
    {
        return -1;
    }    
    hash->size = size;
    hash->array = NULL;
    
    hash->array = malloc(size * sizeof(struct hash_node_t)); 

    for(i = 0; i < size;i++)
    {
        hash->array[i]->key = 0;
        hash->array[i]->data = 0;
    }

    return ret;
}
    
int get_hash_index(struct hash_t *h, unsigned int key)
{
    return (key % h->size)
}

