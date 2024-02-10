#include "malloc.h"
#include "stdarg.h"

#include "btree.h"

btree_node_t *btree_init(enum comparable_type_enum type, uint32_t max_keys)
{
    btree_node_t *btree = calloc(1, sizeof(btree_node_t));
    btree->max_keys = max_keys;
    btree->type = type;
    btree->current_keys = 0;
    btree->keys = calloc(1, 0);

    return btree;
}

void btree_free(btree_node_t *btree)
{
    free(btree->keys);
    free(btree);
}
