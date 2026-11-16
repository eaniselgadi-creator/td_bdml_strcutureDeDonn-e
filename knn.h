/* knn.h - Classifieur des k plus proches voisins (KNN). */
#ifndef KNN_H
#define KNN_H

#include "list.h"

/* Liste chainee des voisins, triee par distance croissante. */
typedef struct NeighborNode {
    float distance;
    int species;
    struct NeighborNode *next;
} NeighborNode;

typedef struct {
    NeighborNode *head;
    int size;
} NeighborList;

/* Fourni */
void neighbors_init(NeighborList *nl);
void neighbors_free(NeighborList *nl);

/* TODO 3.3 : insertion triee, puis on ne garde que les k plus proches. */
void neighbors_insert_sorted(NeighborList *nl, float distance, int species, int k);

/* TODO 3.4 : predit l'espece de f a partir des k plus proches voisins du train. */
int knn_predict(const List *train, const Flower *f, int k);

/* Fourni : exactitude sur le test, et matrice de confusion si show_matrix vaut 1. */
void knn_evaluate(const List *train, const List *test, int k, int show_matrix);

#endif
