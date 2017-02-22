/* solveur.h

Derni�re modification par Little_Dragoon le 04/02
    -d�finition des structures de donn�es du Cubie et du Cube
    -Ajout des prototypes des fonctions de chaque �tape

contient les fonctions de recherche de solution, �tape par �tape
*/

#ifndef SOLVEUR
#define SOLVEUR

#include "mouvements.h"


// fonctions de r�solution
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

