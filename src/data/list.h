#ifndef LIST_H
#define LIST_H

#include "pthread.h"
#include "stdbool.h"

#include "enums.h"

/// @brief List data structure
typedef struct
{
    enum type_enum type;
    pthread_mutex_t mutex;
    union list_type
    {
        int t_integer;
        unsigned int t_unsigned_integer;
        float t_float;
        double t_double;
        bool t_bool;
        char *t_str;
        void *t_ptr;
    } *data;
    unsigned int length;
    unsigned int pages;
} list_t;

/// @brief Initializes a new list
/// @param type Generic type of list
/// @return A pointer to created list_t
list_t *list_init(enum type_enum type);

/// @brief Appends data to list
/// @param list Pointer to list
/// @param value Any value that matches the type
void list_append(list_t *list, ...);

/// @brief Frees a list
/// @param list Pointer to list
void list_free(list_t *list);

/// @brief Frees a list
/// @param list Pointer to list
/// @param index Index of item
/// @return Retunes the union type of list item
union list_type *list_at(list_t *list, unsigned int index);

/// @brief
/// @param list Pointer to list
/// @param index Index of item
void list_remove_at(list_t *list, unsigned int index);

#endif