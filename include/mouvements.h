#ifndef MOUVMENTS
#define MOUVMENTS

#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Cubie Cubie;
struct Cubie
{
    int c;
    int o;
};
/*note pour le cube :
    c : voir constantes.h pour les valeurs possibles
    o : pour un coin, 0 pour sa position normale, 1 pour 1/3 de tour CW, 2 pour 1/3 CCW
        pour une arète, 0 en position normale, 1 inversée
        les références sont haut ou bas (U/D) puis avant ou arrière(F/B)
*/

typedef struct Cube Cube;
struct Cube
{
    Cubie corner[8];
    Cubie edge[12];
};
//fonctions de mouvements
Cube frontMove(Cube cubeATourner);

Cube upMove(Cube cubeATourner);

Cube rightMove(Cube cubeATourner);

Cube backMove(Cube cubeATourner);

Cube downMove(Cube cubeATourner);

Cube leftMove(Cube cubeATourner);

Cube copie(Cube cubeACopier);

void scramble(Cube *cubeAMelanger, char combinaison[], int *longueurCombi, int *sens, SDL_Surface *screen, Uint32 couleurs[]);

void appliquerCombinaison(Cube *rubiksCube, char combinaison[], int *sens, int longueurCombi, SDL_Surface *screen, Uint32 couleurs[]);

void fonctionUseless(int argument1, double argument2);

void blitFacelets(SDL_Surface *screen, int facelets[][9], Uint32 couleurs[]);




#endif // MOUVMENTS
