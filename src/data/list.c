#include "malloc.h"
#include "stdarg.h"
#include "math.h"

#include "list.h"

const unsigned int PAGE_SIZE = 32;

void __resize_list(list_t *list, int n_page)
{
    unsigned int fixed_size = (list->pages + n_page) * PAGE_SIZE;
    switch (list->type)
    {
    case typ_integer:
        list->data = (union list_type *)realloc(list->data, fixed_size * sizeof(int));
        break;
    case typ_unsigned_integer:
        list->data = (union list_type *)realloc(list->data, fixed_size * sizeof(unsigned int));
        break;
    case typ_float:
        list->data = (union list_type *)realloc(list->data, fixed_size * sizeof(double));
        break;
    case typ_double:
        list->data = (union list_type *)realloc(list->data, fixed_size * sizeof(double));
        break;
    case typ_bool:
        list->data = (union list_type *)realloc(list->data, fixed_size * sizeof(int));
        break;
    case typ_string:
        list->data = (union list_type *)realloc(list->data, fixed_size * sizeof(char *));
        break;
    case typ_ptr:
        list->data = (union list_type *)realloc(list->data, fixed_size * sizeof(void *));
        break;
    }
    list->pages += n_page;
}

list_t *list_init(enum type_enum type)
{
    list_t *list = calloc(1, sizeof(list_t));
    list->type = type;
    pthread_mutex_init(&list->mutex, NULL);
    list->length = 0;
    list->pages = 1;

    switch (list->type)
    {
    case typ_integer:
        list->data = malloc(PAGE_SIZE * sizeof(int));
        break;
    case typ_unsigned_integer:
        list->data = malloc(PAGE_SIZE * sizeof(unsigned int));
        break;
    case typ_float:
        list->data = malloc(PAGE_SIZE * sizeof(double));
        break;
    case typ_double:
        list->data = malloc(PAGE_SIZE * sizeof(double));
        break;
    case typ_bool:
        list->data = malloc(PAGE_SIZE * sizeof(bool));
        break;
    case typ_string:
        list->data = malloc(PAGE_SIZE * sizeof(char *));
        break;
    case typ_ptr:
        list->data = malloc(PAGE_SIZE * sizeof(void *));
        break;
    }
    return list;
}

void list_append(list_t *list, ...)
{
    pthread_mutex_lock(&list->mutex);
    va_list args;
    va_start(args, list);
    union list_type data;

    switch (list->type)
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
    va_end(args);

    if (list->length + 1 > list->pages * PAGE_SIZE)
    {
        __resize_list(list, 1);
    }

    list->data[list->length] = data;
    list->length++;
    pthread_mutex_unlock(&list->mutex);
}

void list_free(list_t *list)
{
    if (list->type == typ_string)
    {
        for (int i = 0; i < list->length; i++)
        {
            free(list->data[i].t_str);
        }
    }
    pthread_mutex_destroy(&list->mutex);
    free(list->data);
    free(list);
}

union list_type *list_at(list_t *list, unsigned int index)
{
    if (index >= list->length)
    {
        return NULL;
    }
    return &list->data[index];
}

void list_remove_at(list_t *list, unsigned int index)
{
    pthread_mutex_lock(&list->mutex);
    if (index >= list->length)
    {
        pthread_mutex_unlock(&list->mutex);
        return;
    }

    if (list->type == typ_string)
    {
        free(list_at(list, index)->t_str);
    }

    if (index != list->length - 1)
    {
        for (int i = index; i < list->length - 1; i++)
        {
            list->data[i] = list->data[i + 1];
        }
    }

    unsigned int next_belongs = floor((list->length - 1) / PAGE_SIZE);
    if (next_belongs < list->pages - 1)
    {
        __resize_list(list, -1);
    }
    list->length--;
    pthread_mutex_unlock(&list->mutex);
}