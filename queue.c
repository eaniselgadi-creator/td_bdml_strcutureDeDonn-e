/* queue.c - File (FIFO) de reels, implementee avec head et tail. */
#include <stdlib.h>
#include "queue.h"

void queue_init(Queue *q)
{
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}

int queue_is_empty(const Queue *q)
{
    return q->head == NULL;
}

void queue_enqueue(Queue *q, float value)
{
    QueueNode *node = malloc(sizeof *node);
    if (node == NULL)
        return;
    node->value = value;
    node->next = NULL;
    if (q->tail == NULL)
        q->head = node;
    else
        q->tail->next = node;
    q->tail = node;
    q->size++;
}

float queue_dequeue(Queue *q)
{
    QueueNode *node = q->head;
    float value = node->value;
    q->head = node->next;
    if (q->head == NULL)
        q->tail = NULL;
    free(node);
    q->size--;
    return value;
}

float queue_peek(const Queue *q)
{
    return q->head->value;
}

void queue_free(Queue *q)
{
    while (!queue_is_empty(q))
        queue_dequeue(q);
}
