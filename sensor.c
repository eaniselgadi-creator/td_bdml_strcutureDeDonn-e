/* sensor.c - Surveillance d'un flux de capteur avec une fenetre glissante. */
#include <stdio.h>
#include <math.h>
#include "queue.h"
#include "sensor.h"

int sensor_monitor(const char *filename, int window_size, float threshold)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror(filename);
        return 0;
    }
    char line[128];
    if (fgets(line, sizeof line, fp) == NULL) {     /* saute l'en-tete */
        fclose(fp);
        return 0;
    }

    Queue window;               /* les window_size dernieres valeurs normales */
    queue_init(&window);
    float sum = 0.0f;           /* somme des valeurs presentes dans window    */
    int nb_anomalies = 0;

    int minute;
    float temp;
    while (fgets(line, sizeof line, fp) != NULL) {
        if (sscanf(line, "%d,%f", &minute, &temp) != 2)
            continue;

        /* TODO 4.2 : si la fenetre est pleine (window.size == window_size) et que
         * temp s'ecarte de la moyenne de la fenetre de plus de threshold (fabsf),
         * afficher l'alerte ci-dessous, incrementer nb_anomalies et passer a la
         * mesure suivante (continue) SANS inserer temp dans la fenetre.
         *   printf("  ALERTE minute %3d : %5.1f C (moyenne %5.2f C)\n", minute, temp, mean); */
        (void)threshold;    /* a supprimer quand vous ecrivez le TODO 4.2 */

        /* TODO 4.1 : ajouter temp a la fenetre (queue_enqueue) et a sum ;
         * si la fenetre contient alors plus de window_size valeurs, retirer la
         * plus ancienne (queue_dequeue) et la soustraire de sum. */
        (void)window_size;  /* a supprimer quand vous ecrivez le TODO 4.1 */

        if (minute % 30 == 0 && !queue_is_empty(&window))
            printf("  minute %3d : moyenne mobile = %5.2f C\n", minute, sum / window.size);
    }
    queue_free(&window);
    fclose(fp);
    return nb_anomalies;
}
