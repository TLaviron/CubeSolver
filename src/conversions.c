#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "constantes.h"
#include "conversions.h"
#include "mouvements.h"


void faceletsToCube(Cube *cible, int facelets[][9])
{
    /*convertit un tableau de facettes en un cube codé en cubies*/
    int directionFacelets[6][9] = {0}, i = 0, j = 0;
    for (i = 0 ; i < 6 ; i++)
    {//conversion couleurs -> direction
        for(j = 0 ; j < 9 ; j++)
        {
            if (j !=4)
            {
                if (facelets[i][j] == facelets[0][4])
                {//left center
                    directionFacelets[i][j] = LEFT;
                }
                else if (facelets[i][j] == facelets[1][4])
                {//down center
                    directionFacelets[i][j] = DOWN;
                }
                else if (facelets[i][j] == facelets[2][4])
                {//right center
                    directionFacelets[i][j] = RIGHT;
                }
                else if (facelets[i][j] == facelets[3][4])
                {//Up center
                    directionFacelets[i][j] = UP;
                }
                else if (facelets[i][j] == facelets[4][4])
                {//front center
                    directionFacelets[i][j] = FRONT;
                }
                else if (facelets[i][j] == facelets[5][4])
                {//back center
                    directionFacelets[i][j] = BACK;
                }
            }
        }
    }//end of conversion

    //corner transformation
    getCorner(cible, URF, directionFacelets[UP][2], directionFacelets[RIGHT][8], directionFacelets[FRONT][6]);
    getCorner(cible, UFL, directionFacelets[UP][8], directionFacelets[FRONT][8], directionFacelets[LEFT][2]);
    getCorner(cible, ULB, directionFacelets[UP][6], directionFacelets[LEFT][0], directionFacelets[BACK][2]);
    getCorner(cible, UBR, directionFacelets[UP][0], directionFacelets[BACK][0], directionFacelets[RIGHT][6]);
    getCorner(cible, DFR, directionFacelets[DOWN][8], directionFacelets[FRONT][0], directionFacelets[RIGHT][2]);
    getCorner(cible, DLF, directionFacelets[DOWN][2], directionFacelets[LEFT][8], directionFacelets[FRONT][2]);
    getCorner(cible, DBL, directionFacelets[DOWN][0], directionFacelets[BACK][8], directionFacelets[LEFT][6]);
    getCorner(cible, DRB, directionFacelets[DOWN][6], directionFacelets[RIGHT][0], directionFacelets[BACK][6]);

    //edge transformation
    getEdge(cible, UF, directionFacelets[UP][5], directionFacelets[FRONT][7]);
    getEdge(cible, UL, directionFacelets[UP][7], directionFacelets[LEFT][1]);
    getEdge(cible, UB, directionFacelets[UP][3], directionFacelets[BACK][1]);
    getEdge(cible, UR, directionFacelets[UP][1], directionFacelets[RIGHT][7]);
    getEdge(cible, DF, directionFacelets[DOWN][5], directionFacelets[FRONT][1]);
    getEdge(cible, DL, directionFacelets[DOWN][1], directionFacelets[LEFT][7]);
    getEdge(cible, DB, directionFacelets[DOWN][3], directionFacelets[BACK][7]);
    getEdge(cible, DR, directionFacelets[DOWN][7], directionFacelets[RIGHT][1]);
    getEdge(cible, FR, directionFacelets[FRONT][3], directionFacelets[RIGHT][5]);
    getEdge(cible, FL, directionFacelets[FRONT][5], directionFacelets[LEFT][5]);
    getEdge(cible, LB, directionFacelets[BACK][5], directionFacelets[LEFT][3]);
    getEdge(cible, RB, directionFacelets[BACK][3], directionFacelets[RIGHT][3]);

}

void getCorner(Cube *cible, int cornerValue, int refFacelet, int clockWiseFacelet, int counterClockWiseFacelet)
{
    /*détermine le coin et son orientation en fonction de facettes ordonnées*/
    int corner = (1 << refFacelet) + (1 << clockWiseFacelet) + (1 << counterClockWiseFacelet);
    switch (corner)
    {
    case 28:
        cible->corner[cornerValue].c = URF;
        break;
    case 25:
        cible->corner[cornerValue].c = UFL;
        break;
    case 41:
        cible->corner[cornerValue].c = ULB;
        break;
    case 44:
        cible->corner[cornerValue].c = UBR;
        break;
    case 22:
        cible->corner[cornerValue].c = DFR;
        break;
    case 19:
        cible->corner[cornerValue].c = DLF;
        break;
    case 35:
        cible->corner[cornerValue].c = DBL;
        break;
    case 38:
        cible->corner[cornerValue].c = DRB;
        break;
    default:
        cible->corner[cornerValue].c = -1;
        break;
    }
    if (refFacelet == UP || refFacelet == DOWN)
    {
        cible->corner[cornerValue].o = 0;
    }
    else if (clockWiseFacelet == UP || clockWiseFacelet == DOWN)
    {
        cible->corner[cornerValue].o = 1;
    }
    else if (counterClockWiseFacelet == UP || counterClockWiseFacelet == DOWN)
    {
        cible->corner[cornerValue].o = 2;
    }
    else
    {
        cible->corner[cornerValue].o = -1;
    }
}

void getEdge(Cube *cible, int edgeValue, int refFacelet, int reverseFacelet)
{
    /*détermine l'arête et son orientation en fonction de facettes ordonnées*/
    int edge = (1 << refFacelet) + (1 << reverseFacelet);
    switch (edge)
    {
    case 24:
        cible->edge[edgeValue].c = UF;
        break;
    case 9:
        cible->edge[edgeValue].c = UL;
        break;
    case 40:
        cible->edge[edgeValue].c = UB;
        break;
    case 12:
        cible->edge[edgeValue].c = UR;
        break;
    case 18:
        cible->edge[edgeValue].c = DF;
        break;
    case 3:
        cible->edge[edgeValue].c = DL;
        break;
    case 34:
        cible->edge[edgeValue].c = DB;
        break;
    case 6:
        cible->edge[edgeValue].c = DR;
        break;
    case 20:
        cible->edge[edgeValue].c = FR;
        break;
    case 17:
        cible->edge[edgeValue].c = FL;
        break;
    case 33:
        cible->edge[edgeValue].c = LB;
        break;
    case 36:
        cible->edge[edgeValue].c = RB;
        break;
    default:
        cible->edge[edgeValue].c = -1;
        break;
    }
    if (refFacelet == UP || refFacelet == DOWN || (( refFacelet == FRONT || refFacelet == BACK) && (reverseFacelet == RIGHT || reverseFacelet == LEFT)))
    {
        cible->edge[edgeValue].o = 0;
    }
    else if (refFacelet == RIGHT || refFacelet == LEFT || (( refFacelet == FRONT || refFacelet == BACK) && (reverseFacelet == UP || reverseFacelet == DOWN)))
    {
        cible->edge[edgeValue].o = 1;
    }
    else
    {
        cible->edge[edgeValue].o = -1;
    }

}

void cubeToFacelets(Cube *cubeAConvertir, int facelets[][9])
{
    /*convertit un cube codé en cubies en un tableau de facelets*/
    int i =0, j = 0;
    //conversion des coins
    retrieveCorner(cubeAConvertir, URF, &facelets[UP][2], &facelets[RIGHT][8], &facelets[FRONT][6]);
    retrieveCorner(cubeAConvertir, UFL, &facelets[UP][8], &facelets[FRONT][8], &facelets[LEFT][2]);
    retrieveCorner(cubeAConvertir, ULB, &facelets[UP][6], &facelets[LEFT][0], &facelets[BACK][2]);
    retrieveCorner(cubeAConvertir, UBR, &facelets[UP][0], &facelets[BACK][0], &facelets[RIGHT][6]);
    retrieveCorner(cubeAConvertir, DFR, &facelets[DOWN][8], &facelets[FRONT][0], &facelets[RIGHT][2]);
    retrieveCorner(cubeAConvertir, DLF, &facelets[DOWN][2], &facelets[LEFT][8], &facelets[FRONT][2]);
    retrieveCorner(cubeAConvertir, DBL, &facelets[DOWN][0], &facelets[BACK][8], &facelets[LEFT][6]);
    retrieveCorner(cubeAConvertir, DRB, &facelets[DOWN][6], &facelets[RIGHT][0], &facelets[BACK][6]);

    //conversion des arêtes
    retrieveEdge(cubeAConvertir, UF, &facelets[UP][5], &facelets[FRONT][7]);
    retrieveEdge(cubeAConvertir, UL, &facelets[UP][7], &facelets[LEFT][1]);
    retrieveEdge(cubeAConvertir, UB, &facelets[UP][3], &facelets[BACK][1]);
    retrieveEdge(cubeAConvertir, UR, &facelets[UP][1], &facelets[RIGHT][7]);
    retrieveEdge(cubeAConvertir, DF, &facelets[DOWN][5], &facelets[FRONT][1]);
    retrieveEdge(cubeAConvertir, DL, &facelets[DOWN][1], &facelets[LEFT][7]);
    retrieveEdge(cubeAConvertir, DB, &facelets[DOWN][3], &facelets[BACK][7]);
    retrieveEdge(cubeAConvertir, DR, &facelets[DOWN][7], &facelets[RIGHT][1]);
    retrieveEdge(cubeAConvertir, FR, &facelets[FRONT][3], &facelets[RIGHT][5]);
    retrieveEdge(cubeAConvertir, FL, &facelets[FRONT][5], &facelets[LEFT][5]);
    retrieveEdge(cubeAConvertir, LB, &facelets[BACK][5], &facelets[LEFT][3]);
    retrieveEdge(cubeAConvertir, RB, &facelets[BACK][3], &facelets[RIGHT][3]);

    for ( i = 0 ; i < 6 ; i++)
    {//conversion directions -> couleurs
        for ( j = 0 ; j < 9 ; j++)
        {
            if (j!=4)
            {
                facelets[i][j] = facelets[facelets[i][j]][4];
            }
        }
    }
}

void retrieveCorner(Cube *cubeAConvertir, int cornerValue, int *refFacelet, int *clockWiseFacelet, int *counterClockWiseFacelet)
{
    /*détermine les facettes d'un coin en fonction ed son type et de son orientation*/
    int faceUn = GRAY, faceDeux = GRAY, faceTrois = GRAY;
    switch (cubeAConvertir->corner[cornerValue].c)
    {
    case URF:
        faceUn = UP;
        faceDeux = RIGHT;
        faceTrois = FRONT;
        break;
    case UFL:
        faceUn = UP;
        faceDeux = FRONT;
        faceTrois = LEFT;
        break;
    case ULB:
        faceUn = UP;
        faceDeux = LEFT;
        faceTrois = BACK;
        break;
    case UBR:
        faceUn = UP;
        faceDeux = BACK;
        faceTrois = RIGHT;
        break;
    case DFR:
        faceUn = DOWN;
        faceDeux = FRONT;
        faceTrois = RIGHT;
        break;
    case DLF:
        faceUn = DOWN;
        faceDeux = LEFT;
        faceTrois = FRONT;
        break;
    case DBL:
        faceUn = DOWN;
        faceDeux = BACK;
        faceTrois = LEFT;
        break;
    case DRB:
        faceUn = DOWN;
        faceDeux = RIGHT;
        faceTrois = BACK;
        break;
    default:
        faceUn = GRAY;
        faceDeux = GRAY;
        faceTrois = GRAY;
        break;
    }
    switch (cubeAConvertir->corner[cornerValue].o)
    {
    case 0:
        *refFacelet = faceUn;
        *clockWiseFacelet = faceDeux;
        *counterClockWiseFacelet = faceTrois;
        break;
    case 1:
        *refFacelet = faceTrois;
        *clockWiseFacelet = faceUn;
        *counterClockWiseFacelet = faceDeux;
        break;
    case 2:
        *refFacelet = faceDeux;
        *clockWiseFacelet = faceTrois;
        *counterClockWiseFacelet = faceUn;
        break;
    default:
        *refFacelet = GRAY;
        *clockWiseFacelet = GRAY;
        *counterClockWiseFacelet = GRAY;
        break;

    }
}

void retrieveEdge(Cube *cubeAConvertir, int edgeValue, int* refFacelet, int *reverseFacelet)
{
    /*détermine les facettes d'une arête en fonction ed son type et de son orientation*/
    int faceUn = GRAY, faceDeux = GRAY;
    switch(cubeAConvertir->edge[edgeValue].c)
    {
    case UF:
        faceUn = UP;
        faceDeux = FRONT;
        break;
    case UL:
        faceUn = UP;
        faceDeux = LEFT;
        break;
    case UB:
        faceUn = UP;
        faceDeux = BACK;
        break;
    case UR:
        faceUn = UP;
        faceDeux = RIGHT;
        break;
    case DF:
        faceUn = DOWN;
        faceDeux = FRONT;
        break;
    case DL:
        faceUn = DOWN;
        faceDeux = LEFT;
        break;
    case DB:
        faceUn = DOWN;
        faceDeux = BACK;
        break;
    case DR:
        faceUn = DOWN;
        faceDeux = RIGHT;
        break;
    case FR:
        faceUn = FRONT;
        faceDeux = RIGHT;
        break;
    case FL:
        faceUn = FRONT;
        faceDeux = LEFT;
        break;
    case LB:
        faceUn = BACK;
        faceDeux = LEFT;
        break;
    case RB:
        faceUn = BACK;
        faceDeux = RIGHT;
        break;
    default:
        faceUn = GRAY;
        faceDeux = GRAY;
        break;
    }
    switch (cubeAConvertir->edge[edgeValue].o)
    {
    case 0:
        *refFacelet = faceUn;
        *reverseFacelet = faceDeux;
        break;
    case 1:
        *refFacelet = faceDeux;
        *reverseFacelet = faceUn;
        break;
    default:
        *refFacelet = GRAY;
        *reverseFacelet = GRAY;
        break;
    }
}
