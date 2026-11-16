/* stack.c - Pile (LIFO) de caracteres. */
#include <stdlib.h>
#include "stack.h"

void stack_init(Stack *s)
{
    s->top = NULL;
    s->size = 0;
}

int stack_is_empty(const Stack *s)
{
    return s->top == NULL;
}

void stack_push(Stack *s, char value)
{
    StackNode *node = malloc(sizeof *node);
    if (node == NULL)
        return;
    node->value = value;
    node->next = s->top;
    s->top = node;
    s->size++;
}

char stack_pop(Stack *s)
{
    StackNode *node = s->top;
    char value = node->value;
    s->top = node->next;
    free(node);
    s->size--;
    return value;
}

char stack_peek(const Stack *s)
{
    return s->top->value;
}

void stack_free(Stack *s)
{
    while (!stack_is_empty(s))
        stack_pop(s);
}
