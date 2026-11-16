/*
 * TD - Structures de donnees appliquees au Big Data & Machine Learning
 *
 * Norme       : C11
 * CLion       : ouvrir le dossier (CMakeLists.txt), puis Build et Run. Les fichiers
 *               .csv et .json sont copies automatiquement dans cmake-build-debug.
 * Terminal    : make && ./td_bdml
 *               (ou : gcc -Wall -Wextra -std=c11 *.c -o td_bdml -lm)
 *
 * Ce fichier est fourni : vous n'avez pas besoin de le modifier.
 * Les fonctions a completer sont marquees TODO dans les autres fichiers .c.
 */
#include <stdio.h>
#include "list.h"
#include "dataset.h"
#include "knn.h"
#include "sensor.h"
#include "json_check.h"

int main(void)
{
    printf("===== PARTIE 1 : ingestion de flowers.csv =====\n");
    List data;
    list_init(&data);
    int loaded = dataset_load_csv("flowers.csv", &data);
    printf("  %d fleurs chargees, taille de la liste = %d\n", loaded, data.size);
    list_preview(&data, 3);

    printf("\n===== PARTIE 2 : nettoyage et statistiques =====\n");
    int removed = dataset_remove_invalid(&data);
    printf("  %d lignes invalides supprimees, il reste %d fleurs\n", removed, data.size);
    list_preview(&data, 2);
    printf("\n");
    dataset_print_stats(&data);
    printf("\n");
    dataset_print_distribution("total", &data);

    printf("\n===== PARTIE 3 : split train/test et KNN =====\n");
    List train, test;
    list_init(&train);
    list_init(&test);
    dataset_train_test_split(&data, &train, &test);
    dataset_print_distribution("train", &train);
    dataset_print_distribution("test", &test);
    printf("\n");
    int k_values[] = { 1, 3, 5, 7, 15 };
    for (int i = 0; i < 5; i++)
        knn_evaluate(&train, &test, k_values[i], 0);
    printf("\n");
    knn_evaluate(&train, &test, 5, 1);

    printf("\n===== PARTIE 4 : surveillance de sensor.csv (fenetre 10, seuil 4 C) =====\n");
    int nb_anomalies = sensor_monitor("sensor.csv", 10, 4.0f);
    printf("  -> %d anomalie(s) detectee(s)\n", nb_anomalies);

    printf("\n===== PARTIE 5 : validation des fichiers JSON =====\n");
    const char *files[] = { "config_ok.json", "config_ko1.json", "config_ko2.json", "config_tricky.json" };
    for (int i = 0; i < 4; i++) {
        printf("%s :\n", files[i]);
        printf("  -> %s\n", json_is_well_formed(files[i]) ? "bien forme" : "MAL FORME");
    }

    list_free(&data);
    list_free(&train);
    list_free(&test);
    return 0;
}
