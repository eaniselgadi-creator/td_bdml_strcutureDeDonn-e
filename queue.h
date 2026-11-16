/* queue.h - File (FIFO) de reels, implementee avec head et tail. */
#ifndef QUEUE_H
#define QUEUE_H

typedef struct QueueNode {
    float value;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *head;    /* on retire ici (dequeue) */
    QueueNode *tail;    /* on ajoute ici (enqueue) */
    int size;
} Queue;

void  queue_init(Queue *q);
int   queue_is_empty(const Queue *q);
void  queue_enqueue(Queue *q, float value);   /* ajoute en fin de file          */
float queue_dequeue(Queue *q);                /* retire et renvoie le plus ancien */
float queue_peek(const Queue *q);             /* renvoie le plus ancien sans le retirer */
void  queue_free(Queue *q);

/* queue_dequeue et queue_peek ne doivent pas etre appeles sur une file vide. */

#endif
