#ifndef BTREE_H
#define BTREE_H

#include "stdint.h"
#include "stdbool.h"

#include "enums.h"

/// @brief B-Tree node structure
typedef struct btree_node_struct
{
    enum comparable_type_enum type;
    union btree_type
    {
        int t_integer;
        unsigned int t_unsigned_integer;
        float t_float;
        double t_double;
        bool t_bool;
    } *keys;
    uint32_t current_key;
    uint32_t max_keys;
    struct btree_node_struct **children;
};

typedef struct btree_node_struct btree_node_t;

/// @brief Initializes a new b-tree node
/// @param type Type of node (enum type_enum)
/// @param max_keys Number of max keys in a node
/// @return Pointer of btree_node_t
btree_node_t *btree_init(enum comparable_type_enum type, uint32_t max_keys);

/// @brief Frees a b-tree node
/// @param btree Pointer to btree_node_t
void btree_free(btree_node_t *btree);

#endif