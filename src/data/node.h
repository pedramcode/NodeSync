#ifndef NODE_H
#define NODE_H

#include "enums.h"
#include "stdbool.h"

/// @brief Node structure used in data structures
struct node_structure
{
    union node_type
    {
        int t_integer;
        unsigned int t_unsigned_integer;
        float t_float;
        double t_double;
        bool t_bool;
        char *t_str;
        void *t_ptr;
    } data;

    enum type_enum type;
    struct node_structure *next;
};

typedef struct node_structure node_t;

/// @brief Instantiates a new node
/// @param type Generic type of node
/// @param value Any value that matches the node type
/// @return Pointer to created node
node_t *node_init(enum type_enum type, ...);

/// @brief Frees node
/// @param node Node pointer
void node_free(node_t *node);

#endif