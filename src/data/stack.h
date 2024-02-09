#ifndef STACK_H
#define STACK_H

#include "pthread.h"

#include "node.h"

/// @brief Stack data structure
typedef struct
{
    node_t *top;
    pthread_mutex_t mutex;
    unsigned int size;
} stack_t;

/// @brief Initializes a new stack
/// @return Pointer to stack
stack_t *stack_init();

/// @brief Pushes node into stack
/// @param stack Pointer to stack
/// @param node Pointer to node
void stack_push(stack_t *stack, node_t *node);

/// @brief Pop item from stack
/// @param stack Pointer to stack
/// @return Pointer to node
node_t *stack_pop(stack_t *stack);

/// @brief Frees stack
/// @param stack Pointer to stack
void stack_free(stack_t *stack);

#endif