/* json_check.c - Verification des { } et [ ] d'un fichier JSON avec une pile. */
#include <stdio.h>
#include "stack.h"
#include "json_check.h"

/* TODO 5.1 : verifier que les { } et [ ] sont equilibres et bien imbriques.
 * Lire caractere par caractere avec fgetc, incrementer line a chaque '\n'.
 *   - '{' ou '[' : stack_push ;
 *   - '}' ou ']' : pile vide -> erreur ; sinon stack_pop et verifier que
 *     l'ouvrant correspond ('{' pour '}', '[' pour ']') ;
 *   - fin du fichier : la pile doit etre vide.
 * A la premiere erreur, afficher la ligne et la cause, mettre ok a 0 et
 * arreter la lecture. Exemples de messages :
 *   printf("  ligne %d : '%c' attendu, '%c' trouve\n", line, expected, c);
 *   printf("  ligne %d : '%c' ferme alors que rien n'est ouvert\n", line, c);
 *   printf("  fin du fichier : %d '%c' jamais ferme(s)\n", s.size, stack_peek(&s));
 *
 * TODO 5.2 (bonus) : ignorer les accolades et crochets situes a l'interieur
 * d'une chaine "..." (testez avec config_tricky.json). */
int json_is_well_formed(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror(filename);
        return 0;
    }
    Stack s;
    stack_init(&s);
    int line = 1;
    int ok = 1;
    (void)line;     /* a supprimer quand vous ecrivez la fonction */
    stack_free(&s);
    fclose(fp);
    return ok;
}
