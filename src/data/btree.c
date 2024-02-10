#include "malloc.h"
#include "stdarg.h"

#include "btree.h"

btree_node_t *btree_init(enum type_enum type, uint32_t max_keys)
{
    btree_node_t *btree = calloc(1, sizeof(btree_node_t));
    btree->max_keys = max_keys;
    btree->type = type;
    btree->current_keys = 0;
    // uint32_t key_size = 0;
    // switch (type)
    // {
    // case typ_integer:
    //     key_size = sizeof(int);
    //     break;
    // case typ_unsigned_integer:
    //     key_size = sizeof(unsigned int);
    //     break;
    // case typ_float:
    //     key_size = sizeof(double);
    //     break;
    // case typ_double:
    //     key_size = sizeof(double);
    //     break;
    // case typ_bool:
    //     key_size = sizeof(int);
    //     break;
    // case typ_string:
    //     key_size = sizeof(char *);
    //     break;
    // case typ_ptr:
    //     key_size = sizeof(void *);
    //     break;
    // }
    btree->keys = calloc(1, 0);

    return btree;
}

void btree_free(btree_node_t *btree)
{
    free(btree->keys);
    free(btree);
}

void btree_insert_key(btree_node_t *btree, ...)
{
    //...
}