/* flower.c - Operations sur une fleur. */
#include <stdio.h>
#include <math.h>
#include "flower.h"

const char *FEATURE_NAMES[NB_FEATURES] = {
    "sepal length", "sepal width", "petal length", "petal width"
};
const char *SPECIES_NAMES[NB_SPECIES] = { "setosa", "versicolor", "virginica" };

void flower_print(const Flower *f)
{
    printf("[%4.1f %4.1f %4.1f %4.1f] %s\n", f->features[0], f->features[1],
           f->features[2], f->features[3],
           (f->species >= 0 && f->species < NB_SPECIES) ? SPECIES_NAMES[f->species] : "?");
}

/* TODO 2.1 : une fleur est valide si chacune de ses 4 mesures est dans ]0 ; 30]
 * et si son espece vaut 0, 1 ou 2. Retourne 1 si valide, 0 sinon. */
/* Une fleur est valide si ses 4 mesures sont dans ]0 ; 30] et si son espece vaut 0, 1 ou 2. */
int flower_is_valid(const Flower *f)
{
    for (int i = 0; i < NB_FEATURES; i++) {
        if (f->features[i] <= 0.0f || f->features[i] > 30.0f)
            return 0;
    }

    if (f->species < 0 || f->species >= NB_SPECIES)
        return 0;

    return 1;
}
/* TODO 3.2 : distance euclidienne entre deux fleurs (sur les 4 mesures).
 * Plus elle est petite, plus les fleurs se ressemblent. Utilisez sqrtf. */
float flower_distance(const Flower *a, const Flower *b)
{
    float sum = 0.0f;
    for (int i = 0; i < NB_FEATURES; i++) {
        float d = a->features[i] - b->features[i];
        sum += d * d;
    }
    return sqrtf(sum);
}