/* image.h

Dernière modification par Little_Dragoon le 06/02
    -écrit une fonction placeholder pour obtenir le tableaux de facelets

doit contenir les fonctions de traitement d'image
*/

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "image.h"

void cubeRempli(int facelets[][9])
{//cube rempli
    int i = 0, j =0;
    for (i = 0 ; i<6 ; i++)
    {
        for(j = 0 ; j<9 ; j++)
        {
            if (i == FRONT)
            {
                facelets[i][j] = GREEN;
            }
            else if (i == RIGHT)
            {
                facelets[i][j] = ORANGE;
            }
            else if (i == LEFT)
            {
                facelets[i][j] = RED;
            }
            else if (i == UP)
            {
                facelets[i][j] = YELLOW;
            }
            else if (i == DOWN)
            {
                facelets[i][j] = WHITE;
            }
            else if (i == BACK)
            {
                facelets[i][j] = BLUE;
            }
        }
    }
}
