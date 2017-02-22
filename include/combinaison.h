#ifndef COMBINAISON
#define COMBINAISON

#include "mouvements.h"
//fonctions de modif de chaine
int lissage(char combinaison[], int longueurCombinaison);

int chaineReduite(char combinaison[], int longueurCombinaison);

void reduire(char combinaison[], int longueurCombinaison);

void ajouterMouvement(char combinaison[], int *longueur, char mouvement, char rotation, Cube *cubeTravail);

#endif // COMBINAISON
