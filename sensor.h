/* sensor.h - Surveillance d'un flux de capteur avec une fenetre glissante. */
#ifndef SENSOR_H
#define SENSOR_H

/* Lit le flux de mesures, affiche la moyenne mobile toutes les 30 minutes et
 * signale les anomalies. Retourne le nombre d'anomalies detectees. */
int sensor_monitor(const char *filename, int window_size, float threshold);

#endif
