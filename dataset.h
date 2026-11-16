/* dataset.h - Chargement, nettoyage, statistiques et split du dataset. */
#ifndef DATASET_H
#define DATASET_H

#include "list.h"

typedef struct {
    float min, max, mean, std_dev;
} Stats;

/* Fourni : charge le CSV en fin de liste, retourne le nombre de fleurs lues. */
int dataset_load_csv(const char *filename, List *list);

/* TODO 2.2 : supprime les fleurs invalides, retourne le nombre supprime. */
int dataset_remove_invalid(List *list);

/* TODO 2.3 : statistiques d'une colonne (0 a 3). */
Stats dataset_compute_stats(const List *list, int column);

/* TODO 2.4 : counts[s] = nombre de fleurs d'espece s. */
void dataset_count_species(const List *list, int counts[NB_SPECIES]);

/* Fourni : affichages. */
void dataset_print_stats(const List *list);
void dataset_print_distribution(const char *title, const List *list);

/* TODO 3.1 : decoupe source en train (80 %) et test (20 %). */
void dataset_train_test_split(const List *source, List *train, List *test);

#endif
