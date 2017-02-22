/* solveur.h

Dernière modification par Little_Dragoon le 04/02
    -définition des structures de données du Cubie et du Cube
    -Ajout des prototypes des fonctions de chaque étape

contient les fonctions de recherche de solution, étape par étape
*/

#ifndef SOLVEUR
#define SOLVEUR

#include "mouvements.h"


// fonctions de résolution
int resolutionNaturelle(Cube* cubeInitial, char combinaison[]);

int aretesPremierEtage(Cube* cubeInitial, char combinaison[], int *directionDebut);

int coinsPremierEtage(Cube* cubePremiereCroix, char combinaison[], int longueurCombinaison, int directionDebut);

int deuxiemeEtage(Cube* cubePremierEtage, char combinaison[], int longueurCombinaison, int directionDebut);

int croixTroisiemeEtage(Cube* cubeDeuxEtages, char combinaison[], int longueurCombinaison, int directionDebut);

int aretesTroisiemeEtage(Cube* cubeTroisiemeCroix, char combinaison[], int longueurCombinaison, int directionDebut);

int coinsTroisiemeEtage(Cube* cubeTroisiemeAretes, char combinaison[], int longueurCombinaison, int directionDebut);

int orientationCoinsTroisiemeEtage(Cube* cubePositionsFinies, char combinaison[], int longueurCombinaison, int directionDebut);

void ordreSolveur(int ordre[], long valeur, long nbValeurs);

long ordreInverse(int ordre[], long nbValeurs);

long factorielle(long n);











#endif

