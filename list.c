/* list.c - Liste simplement chainee de fleurs, avec head et tail. */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void list_init(List *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void list_free(List *list)
{
    Node *curr = list->head;
    while (curr != NULL) {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
    list_init(list);
}

void list_preview(const List *list, int n)
{
    int i = 0;
    for (Node *curr = list->head; curr != NULL && i < n; curr = curr->next, i++) {
        printf("  ligne %d : ", i + 1);
        flower_print(&curr->flower);
    }
    if (list->tail != NULL) {
        printf("  tail     : ");
        flower_print(&list->tail->flower);
    }
}

/* TODO 1.1 : ajouter une copie de f en FIN de liste, en O(1) grace a tail.
 *   - liste vide (tail == NULL) : le nouveau noeud devient head ET tail ;
 *   - sinon : on l'accroche derriere tail, puis il devient le nouveau tail.
 * Ne pas oublier node->next = NULL et size++. */
int list_push_back(List *list, Flower f)
{
    Node *node = malloc(sizeof(Node));
    if (node == NULL)
        return 0;               /* allocation échouée : liste inchangée */

    node->flower = f;           /* copie de la fleur */
    node->next = NULL;          /* le nouveau nœud est le dernier */

    if (list->tail == NULL) {   /* liste vide : head ET tail */
        list->head = node;
        list->tail = node;
    } else {                    /* sinon : derrière tail */
        list->tail->next = node;
        list->tail = node;
    }
    list->size++;
    return 1;
}
