#include "malloc.h"

#include "queue.h"

queue_t *queue_init()
{
    queue_t *queue = malloc(sizeof(queue_t));
    if (queue == NULL)
    {
        // Unable to allocate;
        return NULL;
    }
    pthread_mutex_init(&queue->mutex, NULL);
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

void queue_enqueue(queue_t *queue, node_t *node)
{
    pthread_mutex_lock(&queue->mutex);
    queue->size++;
    if (queue->rear == NULL)
    {
        queue->rear = queue->front = node;
        pthread_mutex_unlock(&queue->mutex);
        return;
    }
    queue->rear->next = node;
    queue->rear = node;
    pthread_mutex_unlock(&queue->mutex);
}

node_t *queue_dequeue(queue_t *queue)
{
    pthread_mutex_lock(&queue->mutex);
    if (queue->front == NULL)
    {
        pthread_mutex_unlock(&queue->mutex);
        return NULL;
    }
    queue->size--;
    node_t *node = queue->front;
    queue->front = queue->front->next;
    pthread_mutex_unlock(&queue->mutex);
    return node;
}

void queue_free(queue_t *queue)
{
    pthread_mutex_destroy(&queue->mutex);
    free(queue);
}