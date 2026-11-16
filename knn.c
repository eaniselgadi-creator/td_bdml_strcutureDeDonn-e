/* knn.c - Classifieur des k plus proches voisins (KNN). */
#include <stdio.h>
#include <stdlib.h>
#include "knn.h"

void neighbors_init(NeighborList *nl)
{
    nl->head = NULL;
    nl->size = 0;
}

void neighbors_free(NeighborList *nl)
{
    NeighborNode *curr = nl->head;
    while (curr != NULL) {
        NeighborNode *next = curr->next;
        free(curr);
        curr = next;
    }
    neighbors_init(nl);
}

/* TODO 3.3 : inserer le voisin (distance, species) a sa place pour que la liste
 * reste triee par distance croissante. Ensuite, si la liste contient plus de k
 * voisins, liberer le dernier : on ne garde que les k plus proches. */
void neighbors_insert_sorted(NeighborList *nl, float distance, int species, int k)
{
    NeighborNode *node = malloc(sizeof(NeighborNode));
    if (node == NULL)
        return;

    node->distance = distance;
    node->species = species;

    if (nl->head == NULL || distance < nl->head->distance) {
        node->next = nl->head;
        nl->head = node;
    } else {
        NeighborNode *prev = nl->head;
        while (prev->next != NULL && prev->next->distance <= distance)
            prev = prev->next;
        node->next = prev->next;
        prev->next = node;
    }
    nl->size++;
    if (nl->size > k) {
        NeighborNode *last = nl->head;
        for (int i = 1; i < k; i++)
            last = last->next;
        free(last->next);
        last->next = NULL;
        nl->size = k;
    }
}
/* TODO 3.4 : predire l'espece de f :
 *   1. pour chaque fleur du train, inserer (flower_distance, espece) dans
 *      une NeighborList initialisee avec neighbors_init ;
 *   2. compter les votes par espece parmi les k voisins (int votes[NB_SPECIES]) ;
 *   3. liberer la liste (neighbors_free) et renvoyer l'espece la plus votee
 *      (en cas d'egalite, la plus petite espece l'emporte). */
int knn_predict(const List *train, const Flower *f, int k)
{
    NeighborList nl;
    neighbors_init(&nl);
    for (Node *n = train->head; n != NULL; n = n->next) {
        float d = flower_distance(f, &n->flower);
        neighbors_insert_sorted(&nl, d, n->flower.species, k);
    }
    int votes[NB_SPECIES] = { 0 };
    for (NeighborNode *v = nl.head; v != NULL; v = v->next)
        votes[v->species]++;

    neighbors_free(&nl);
    int best = 0;
    for (int s = 1; s < NB_SPECIES; s++) {
        if (votes[s] > votes[best])
            best = s;
    }
    return best;
}

void knn_evaluate(const List *train, const List *test, int k, int show_matrix)
{
    int matrix[NB_SPECIES][NB_SPECIES] = { { 0 } };     /* [vraie][predite] */
    int correct = 0;
    for (Node *curr = test->head; curr != NULL; curr = curr->next) {
        int p = knn_predict(train, &curr->flower, k);
        if (p < 0 || p >= NB_SPECIES)
            continue;
        matrix[curr->flower.species][p]++;
        if (p == curr->flower.species)
            correct++;
    }
    float accuracy = test->size > 0 ? 100.0f * correct / test->size : 0.0f;
    printf("  k = %2d : %2d / %2d bien classees  -> exactitude %5.1f %%\n",
           k, correct, test->size, accuracy);
    if (show_matrix) {
        printf("\n  Matrice de confusion (k = %d) - lignes : vraie espece, colonnes : prediction\n", k);
        printf("  %-12s", "");
        for (int s = 0; s < NB_SPECIES; s++)
            printf("%11s", SPECIES_NAMES[s]);
        printf("\n");
        for (int t = 0; t < NB_SPECIES; t++) {
            printf("  %-12s", SPECIES_NAMES[t]);
            for (int p = 0; p < NB_SPECIES; p++)
                printf("%11d", matrix[t][p]);
            printf("\n");
        }
    }
}
