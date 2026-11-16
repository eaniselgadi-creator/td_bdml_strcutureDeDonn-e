/* flower.h - Une fleur du dataset et les operations sur une fleur seule. */
#ifndef FLOWER_H
#define FLOWER_H

#define NB_FEATURES 4   /* 4 mesures en cm                              */
#define NB_SPECIES  3   /* 0 = setosa, 1 = versicolor, 2 = virginica    */

extern const char *FEATURE_NAMES[NB_FEATURES];
extern const char *SPECIES_NAMES[NB_SPECIES];

typedef struct {
    float features[NB_FEATURES];
    int species;
} Flower;

/* Fourni : affiche une fleur sur une ligne. */
void flower_print(const Flower *f);

/* TODO 2.1 : 1 si la fleur est valide, 0 sinon. */
int flower_is_valid(const Flower *f);

/* TODO 3.2 : distance euclidienne entre deux fleurs. */
float flower_distance(const Flower *a, const Flower *b);

#endif
