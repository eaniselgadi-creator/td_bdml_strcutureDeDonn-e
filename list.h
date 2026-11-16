/* list.h - Liste simplement chainee de fleurs, avec head et tail. */
#ifndef LIST_H
#define LIST_H

#include "flower.h"

typedef struct Node {
    Flower flower;
    struct Node *next;
} Node;

typedef struct {
    Node *head;     /* premier noeud (NULL si la liste est vide) */
    Node *tail;     /* dernier noeud (NULL si la liste est vide) */
    int size;       /* nombre de noeuds                          */
} List;

/* Fourni */
void list_init(List *list);
void list_free(List *list);
void list_preview(const List *list, int n);   /* n premieres fleurs + tail */

/* TODO 1.1 : ajoute une copie de f en fin de liste, en O(1).
 * Retourne 1 si l'ajout a reussi, 0 si malloc a echoue. */
int list_push_back(List *list, Flower f);

#endif
