#include "malloc.h"

#include "stack.h"

stack_t *stack_init()
{
    stack_t *stack = malloc(sizeof(stack_t));
    if (stack == NULL)
    {
        // Unable to allocate;
        return NULL;
    }
    pthread_mutex_init(&stack->mutex, NULL);
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void stack_push(stack_t *stack, node_t *node)
{
    pthread_mutex_lock(&stack->mutex);
    stack->size++;
    if (stack->top == NULL)
    {
        stack->top = node;
        pthread_mutex_unlock(&stack->mutex);
        return;
    }
    node_t *current = stack->top;
    while (1)
    {
        if (current->next == NULL)
        {
            break;
        }
        current = current->next;
    }
    current->next = node;
    current = node;

    pthread_mutex_unlock(&stack->mutex);
}

node_t *stack_pop(stack_t *stack)
{
    pthread_mutex_lock(&stack->mutex);
    if (stack->top == NULL)
    {
        pthread_mutex_unlock(&stack->mutex);
        return NULL;
    }
    stack->size--;
    node_t *top = stack->top;
    stack->top = stack->top->next;
    pthread_mutex_unlock(&stack->mutex);
    return top;
}

void stack_free(stack_t *stack)
{
    pthread_mutex_destroy(&stack->mutex);
    free(stack);
}