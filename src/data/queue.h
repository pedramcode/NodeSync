#ifndef QUEUE_H
#define QUEUE_H

#include "pthread.h"

#include "node.h"

/// @brief Queue data structure
typedef struct
{
    node_t *front;
    node_t *rear;
    pthread_mutex_t mutex;
    unsigned int size;
} queue_t;

/// @brief Initializses a new queue
/// @return Pointer to queue
queue_t *queue_init();

/// @brief Enqueue a node into queue
/// @param queue Pointer of queue
/// @param node Pointer of node
void queue_enqueue(queue_t *queue, node_t *node);

/// @brief Dequeue node from queue
/// @param queue Pointer to queue
/// @return Pointer to enqueued node
node_t *queue_dequeue(queue_t *queue);

/// @brief Frees a queue
/// @param queue Pointer to queue
void queue_free(queue_t *queue);

#endif