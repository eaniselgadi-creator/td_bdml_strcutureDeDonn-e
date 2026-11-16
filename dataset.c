/* dataset.c - Chargement, nettoyage, statistiques et split du dataset. */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dataset.h"

/* ---------- Partie 1 : ingestion (fourni) ---------- */

int dataset_load_csv(const char *filename, List *list)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror(filename);
        return 0;
    }
    char line[256];
    int count = 0;
    if (fgets(line, sizeof line, fp) == NULL) {     /* saute la ligne d'en-tete */
        fclose(fp);
        return 0;
    }
    while (fgets(line, sizeof line, fp) != NULL) {
        Flower f;
        if (sscanf(line, "%f,%f,%f,%f,%d", &f.features[0], &f.features[1],
                   &f.features[2], &f.features[3], &f.species) == 5) {
            if (list_push_back(list, f))
                count++;
        }
    }
    fclose(fp);
    return count;
}

/* ---------- Partie 2 : nettoyage et statistiques ---------- */

/* TODO 2.2 : supprimer (et liberer) tous les noeuds dont la fleur est invalide
 * (utilisez flower_is_valid). Trois cas pieges : le noeud supprime est la tete,
 * c'est le dernier (tail doit reculer !), ou deux invalides se suivent.
 * Retourne le nombre de noeuds supprimes. */
int dataset_remove_invalid(List *list)
{
    int removed = 0;
    Node *prev = NULL;
    Node *curr = list->head;

    while (curr != NULL) {
        if (!flower_is_valid(&curr->flower)) {
            Node *to_delete = curr;

            /* 1. raccrocher le reste de la liste */
            if (prev == NULL)
                list->head = curr->next;    /* on supprime la tete */
            else
                prev->next = curr->next;    /* prev saute par-dessus curr */

            /* 2. si on supprime le dernier noeud, tail recule sur prev */
            if (curr == list->tail)
                list->tail = prev;

            /* 3. avancer curr, liberer, mettre a jour size */
            curr = curr->next;
            free(to_delete);
            list->size--;
            removed++;
            /* prev ne bouge pas ! */
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    return removed;
}

/* TODO 2.3 : min, max, moyenne et ecart-type de la colonne column (0 a 3).
 * Premier parcours : min, max et somme. Second parcours : somme des
 * (x - moyenne)^2, puis std_dev = sqrtf(cette somme / size).
 * Liste vide : renvoyer la structure remplie de 0. */
Stats dataset_compute_stats(const List *list, int column)
{
    Stats s = { 0.0f, 0.0f, 0.0f, 0.0f };
    if (list->head == NULL)
        return s;

    float sum = 0.0f;
    s.min = list->head->flower.features[column];
    s.max = s.min;

    for (Node *curr = list->head; curr != NULL; curr = curr->next) {
        float x = curr->flower.features[column];
        if (x < s.min) s.min = x;
        if (x > s.max) s.max = x;
        sum += x;}

    s.mean = sum / list->size;
    float sq_sum = 0.0f;
    for (Node *curr = list->head; curr != NULL; curr = curr->next) {
        float diff = curr->flower.features[column] - s.mean;
        sq_sum += diff * diff;
    }
    s.std_dev = sqrtf(sq_sum / list->size);
    return s;
}
/* TODO 2.4 : counts[s] doit contenir le nombre de fleurs d'espece s. */
void dataset_count_species(const List *list, int counts[NB_SPECIES])
{
    for (int s = 0; s < NB_SPECIES; s++)
        counts[s] = 0;

    for (Node *curr = list->head; curr != NULL; curr = curr->next)
        counts[curr->flower.species]++;
}
void dataset_print_stats(const List *list)
{
    printf("  %-14s %6s %6s %8s %10s\n", "colonne", "min", "max", "moyenne", "ecart-type");
    for (int c = 0; c < NB_FEATURES; c++) {
        Stats s = dataset_compute_stats(list, c);
        printf("  %-14s %6.2f %6.2f %8.2f %10.2f\n", FEATURE_NAMES[c],
               s.min, s.max, s.mean, s.std_dev);
    }
}

void dataset_print_distribution(const char *title, const List *list)
{
    int counts[NB_SPECIES];
    dataset_count_species(list, counts);
    printf("  %-6s : %3d fleurs (", title, list->size);
    for (int s = 0; s < NB_SPECIES; s++)
        printf("%s %d%s", SPECIES_NAMES[s], counts[s], s < NB_SPECIES - 1 ? ", " : ")\n");
}

/* ---------- Partie 3 : split train/test ---------- */

/* TODO 3.1 : parcourir source et copier chaque fleur dans train ou test en
 * conservant l'ordre : la fleur numero i (en partant de 0) va dans test si
 * i % 5 == 4, sinon dans train. Utilisez list_push_back. */
void dataset_train_test_split(const List *source, List *train, List *test)
{
    int i = 0;
    for (Node *n = source->head; n != NULL; n = n->next, i++) {
        if (i % 5 == 4)
            list_push_back(test, n->flower);
        else
            list_push_back(train, n->flower);
    }
}