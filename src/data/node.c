#include "string.h"
#include "malloc.h"
#include "stdarg.h"

#include "node.h"

node_t *node_init(enum type_enum type, ...)
{
    node_t *node = calloc(1, sizeof(node_t));
    if (node == NULL)
    {
        // Unable to allocate;
        return NULL;
    }

    va_list args;
    va_start(args, type);

    node->type = type;
    union node_type data;
    switch (type)
    {
    case typ_integer:
        data.t_integer = va_arg(args, int);
        break;
    case typ_unsigned_integer:
        data.t_unsigned_integer = va_arg(args, unsigned int);
        break;
    case typ_float:
        data.t_float = va_arg(args, double);
        break;
    case typ_double:
        data.t_double = va_arg(args, double);
        break;
    case typ_bool:
        data.t_bool = va_arg(args, int) != 0;
        break;
    case typ_string:
        data.t_str = va_arg(args, char *);
        break;
    case typ_ptr:
        data.t_ptr = va_arg(args, void *);
        break;
    }
    node->data = data;
    node->next = NULL;
    va_end(args);
    return node;
}

void node_free(node_t *node)
{
    if (node->type == typ_string)
    {
        free(node->data.t_str);
    }
    free(node);
}