/* stack.h - Pile (LIFO) de caracteres. */
#ifndef STACK_H
#define STACK_H

typedef struct StackNode {
    char value;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;     /* sommet de la pile (NULL si vide) */
    int size;
} Stack;

void stack_init(Stack *s);
int  stack_is_empty(const Stack *s);
void stack_push(Stack *s, char value);   /* empile                              */
char stack_pop(Stack *s);                /* depile et renvoie le sommet         */
char stack_peek(const Stack *s);         /* renvoie le sommet sans le retirer   */
void stack_free(Stack *s);

/* stack_pop et stack_peek ne doivent pas etre appeles sur une pile vide. */

#endif
