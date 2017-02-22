#ifndef CONVERSIONS
#define CONVERSIONS

#include "mouvements.h"
//fonctions de conversion
void faceletsToCube(Cube *cible, int facelets[][9]);

void getCorner(Cube *cible, int cornerValue, int refFacelet, int clockWiseFacelet, int counterClockWiseFacelet);

void getEdge(Cube *cible, int edgeValue, int refFacelet, int reverseFacelet);

void cubeToFacelets(Cube *cubeAConvertir, int facelets[][9]);

void retrieveCorner(Cube *cubeAConvertir, int cornerValue, int *refFacelet, int *clockWiseFacelet, int *counterClockWiseFacelet);

void retrieveEdge(Cube *cubeAConvertir, int edgeValue, int* refFacelet, int *reverseFacelet);

#endif // CONVERSIONS
