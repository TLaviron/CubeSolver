#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>


#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "solveur.h"
#include "constantes.h"
#include "combinaison.h"
#include "mouvements.h"
#include "conversions.h"

int resolutionNaturelle(Cube* cubeInitial, char combinaison[])
{
    int longueur = 0, direction = 0;
    Cube cubeTravail = copie(*cubeInitial);
    longueur = aretesPremierEtage(&cubeTravail, combinaison, &direction);
    longueur = lissage(combinaison, longueur);
    longueur = coinsPremierEtage(&cubeTravail, combinaison, longueur, direction);
    longueur = lissage(combinaison, longueur);
    longueur = deuxiemeEtage(&cubeTravail, combinaison, longueur, direction);
    longueur = lissage(combinaison, longueur);
    longueur = croixTroisiemeEtage(&cubeTravail, combinaison, longueur, direction);
    longueur = lissage(combinaison, longueur);
    longueur = aretesTroisiemeEtage(&cubeTravail, combinaison, longueur, direction);
    longueur = lissage(combinaison, longueur);
    longueur = coinsTroisiemeEtage(&cubeTravail, combinaison, longueur, direction);
    longueur = lissage(combinaison, longueur);
    longueur = orientationCoinsTroisiemeEtage(&cubeTravail, combinaison, longueur, direction);
    longueur = lissage(combinaison, longueur);

    return longueur;
}

int aretesPremierEtage(Cube* cubeInitial, char combinaison[], int *directionDebut)
{/* aretes bien placees vaut de 0 a 15, chaque cube sur un bit
    -pour front/back, dans l'ordre : 0bDLUR
    -right/left : 0bBDFU
    -up/down : 0bLBRF*/
    int longueurCombi = 0, longueurMini = NB_MVT_MAX, longueurActuelle = 0, i =0, j = 0, aretesBienPlacees = 0, position = 0;
    char combiActuelle[NB_MVT_MAX*2+1] = "", combiMini[NB_MVT_MAX*2+1] = "", chaineVide[1] = "";
    for (i = 0 ; i < 6 ; i++)
    {
        longueurActuelle = 0;
        strcpy(combiActuelle, chaineVide);
        switch (i)
        {
        case LEFT:
            break;
        case DOWN:
            break;
        case RIGHT:
            break;
        case UP:
            break;
        case FRONT:
            aretesBienPlacees = 0;
            if (cubeInitial->edge[FR].c == FR && cubeInitial->edge[FR].o == 0)
            {//rechercher des aretes déja en place
                aretesBienPlacees += 1;
            }
            if (cubeInitial->edge[UF].c == UF && cubeInitial->edge[UF].o == 0)
            {
                aretesBienPlacees += 2;
            }
            if (cubeInitial->edge[FL].c == FL && cubeInitial->edge[FL].o == 0)
            {
                aretesBienPlacees += 4;
            }
            if (cubeInitial->edge[DF].c == DF && cubeInitial->edge[DF].o == 0)
            {
                aretesBienPlacees += 8;
            }
            while (aretesBienPlacees%2 == 0)
            {//FR manquant
                for (j = 0 ; j < 12 ; j++)
                {
                    if (cubeInitial->edge[j].c == FR)
                    {
                        position = j;
                    }
                }
                switch (position)
                {
                case UF:
                    if (cubeInitial->edge[position].o == 1 && aretesBienPlacees == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    else if (cubeInitial->edge[position].o == 1 && aretesBienPlacees != 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 2, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 2, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    else if (cubeInitial->edge[position].o ==0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    break;
                case UL:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        if (aretesBienPlacees != 0)
                        {
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeInitial);
                        }
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeInitial);
                        aretesBienPlacees +=1;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        if (aretesBienPlacees != 0)
                        {
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        }
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    break;
                case UB:
                    if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 2, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    else if (cubeInitial->edge[position].o == 0)
                    {
                        if (((aretesBienPlacees/2)%2) ==1)
                        {
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        }
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeInitial);
                        if (((aretesBienPlacees/2)%2) ==1)
                        {
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        }
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    break;
                case UR:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        if (aretesBienPlacees != 0)
                        {
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        }
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    break;
                case DF:
                    if (cubeInitial->edge[position].o == 1 && aretesBienPlacees == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    else if (cubeInitial->edge[position].o == 1 && aretesBienPlacees != 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 2, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 2, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    else if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    break;
                case DL:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        if (aretesBienPlacees != 0)
                        {
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeInitial);
                        }
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        if (aretesBienPlacees != 0)
                        {
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        }
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    break;
                case DB:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        if (((aretesBienPlacees/2)%2) == 1)
                        {
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        }
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeInitial);
                        if (((aretesBienPlacees/2)%2) == 1)
                        {
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        }
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 2, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    break;
                case DR:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        if (aretesBienPlacees != 0)
                        {
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        }
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    break;
                case FR:
                    if (aretesBienPlacees == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    else if (aretesBienPlacees !=0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    break;
                case FL:
                    if (cubeInitial->edge[position].o == 0 && aretesBienPlacees == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    else if (cubeInitial->edge[position].o == 0 && aretesBienPlacees != 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 2, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 2, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    break;
                case LB:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 2, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        if (aretesBienPlacees != 0 )
                        {
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeInitial);
                            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeInitial);
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeInitial);
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                            aretesBienPlacees+=1;
                        }
                        else if (aretesBienPlacees == 0)
                        {
                            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeInitial);
                            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeInitial);
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                            aretesBienPlacees+=1;
                        }
                    }
                    break;
                case RB:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 2, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeInitial);
                        if (aretesBienPlacees !=0)
                        {
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        }
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        aretesBienPlacees+=1;
                    }
                    break;


                }
            }
            while ((aretesBienPlacees/2)%2 == 0)
            {//UF manquant
                for (j = 0 ; j < 12 ; j++)
                {
                    if (cubeInitial->edge[j].c == UF)
                    {
                        position = j;
                    }
                }
                switch (position)
                {
                case UF:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        aretesBienPlacees +=2;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        aretesBienPlacees+=2;
                    }

                    break;
                case UL:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeInitial);
                        aretesBienPlacees+=2;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        aretesBienPlacees +=2 ;
                    }
                    break;
                case UB:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 2, cubeInitial);
                        aretesBienPlacees+=2;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        aretesBienPlacees+=2;
                    }
                    break;
                case UR:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeInitial);
                        aretesBienPlacees+=2;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        aretesBienPlacees+=2;
                    }
                    break;
                case DF:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 2, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 2, cubeInitial);
                        aretesBienPlacees+=2;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        aretesBienPlacees+=2;
                    }
                    break;
                case DL:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeInitial);
                        aretesBienPlacees+=2;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        aretesBienPlacees+=2;
                    }
                    break;
                case DB:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 2, cubeInitial);
                        aretesBienPlacees+=2;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeInitial);
                        if ((aretesBienPlacees/4)%2 == 1)
                        {
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        }
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeInitial);
                        if ((aretesBienPlacees/4)%2 == 1)
                        {
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        }
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeInitial);
                        aretesBienPlacees+=2;
                    }
                    break;
                case DR:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeInitial);
                        aretesBienPlacees+=2;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        aretesBienPlacees+=2;
                    }
                    break;
                //FR en place
                case FL:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeInitial);
                        aretesBienPlacees+=2;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 2, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 2, cubeInitial);
                        aretesBienPlacees+=2;
                    }

                    break;
                case LB:
                    if (cubeInitial->edge[position].o == 0)
                    {

                        if ((aretesBienPlacees/4)%2 == 1)
                        {
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        }
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeInitial);
                        if ((aretesBienPlacees/4)%2 == 1)
                        {
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        }
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeInitial);
                        aretesBienPlacees+=2;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 2, cubeInitial);
                        aretesBienPlacees+=2;
                    }
                    break;
                case RB:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeInitial);
                        aretesBienPlacees+=2;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 2, cubeInitial);
                        aretesBienPlacees+=2;
                    }
                    break;
                }
            }
            while ((aretesBienPlacees/4)%2 == 0)
            {//FL manquant
                for (j = 0 ; j < 12 ; j++)
                {
                    if (cubeInitial->edge[j].c == FL)
                    {
                        position = j;
                    }
                }
                switch (position)
                {
                //UF en place
                case UL:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeInitial);
                        aretesBienPlacees +=4;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        aretesBienPlacees +=4;
                    }
                    break;
                case UB:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeInitial);
                        aretesBienPlacees +=4;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 2, cubeInitial);
                        aretesBienPlacees+=4;
                    }
                    break;
                case UR:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeInitial);
                        aretesBienPlacees +=4;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        aretesBienPlacees +=4;
                    }
                    break;
                case DF:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeInitial);
                        aretesBienPlacees +=4;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 2, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 2, cubeInitial);
                        aretesBienPlacees +=4;
                    }
                    break;
                case DL:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeInitial);
                        aretesBienPlacees +=4;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        aretesBienPlacees +=4;
                    }
                    break;
                case DB:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeInitial);
                        aretesBienPlacees +=4;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 2, cubeInitial);
                        aretesBienPlacees +=4;
                    }
                    break;
                case DR:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeInitial);
                        aretesBienPlacees +=4;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        aretesBienPlacees +=4;
                    }
                    break;
                case FL:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        aretesBienPlacees +=4;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        aretesBienPlacees +=4;
                    }
                    break;
                case LB:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 2, cubeInitial);
                        aretesBienPlacees +=4;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        aretesBienPlacees +=4;
                    }
                    break;
                case RB:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 2, cubeInitial);
                        aretesBienPlacees +=4;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeInitial);
                        aretesBienPlacees +=4;
                    }
                    break;
                }
            }
            while ((aretesBienPlacees/8)%2 == 0)
            {//DF manquant
                for (j = 0 ; j < 12 ; j++)
                {
                    if (cubeInitial->edge[j].c == DF)
                    {
                        position = j;
                    }
                }
                switch (position)
                {
                case UL:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeInitial);
                        aretesBienPlacees +=8;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        aretesBienPlacees +=8;
                    }
                    break;
                case UB:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 2, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeInitial);
                        aretesBienPlacees +=8;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        aretesBienPlacees +=8;
                    }
                    break;
                case UR:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeInitial);
                        aretesBienPlacees +=8;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        aretesBienPlacees +=8;
                    }
                    break;
                case DF:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        aretesBienPlacees +=8;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        aretesBienPlacees +=8;
                    }
                    break;
                case DL:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeInitial);
                        aretesBienPlacees +=8;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        aretesBienPlacees +=8;
                    }
                    break;
                case DB:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 2, cubeInitial);
                        aretesBienPlacees +=8;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        aretesBienPlacees +=8;
                    }
                    break;
                case DR:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeInitial);
                        aretesBienPlacees +=8;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        aretesBienPlacees +=8;
                    }
                    break;
                //Fl en place
                case LB:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeInitial);
                        aretesBienPlacees +=8;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 2, cubeInitial);
                        aretesBienPlacees +=8;
                    }
                    break;
                case RB:
                    if (cubeInitial->edge[position].o == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeInitial);
                        aretesBienPlacees +=8;
                    }
                    else if (cubeInitial->edge[position].o == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeInitial);
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 2, cubeInitial);
                        aretesBienPlacees +=8;
                    }
                    break;
                }
            }
             longueurActuelle = lissage(combiActuelle, longueurActuelle);
            combiActuelle[longueurActuelle*2] = '\0';
            if (longueurActuelle < longueurMini)
            {
                longueurMini = longueurActuelle;
                strcpy(combiMini, combiActuelle);
                *directionDebut = FRONT;
            }
            break;
        case BACK:
            break;
        }
    }
    longueurCombi += longueurMini;
    strcpy(combinaison, combiMini);
    return longueurCombi;
}

int coinsPremierEtage(Cube* cubePremiereCroix, char combinaison[], int longueurCombinaison, int directionDebut)
{/* coins bien placé vaut 0-15, 1 bit par coin ; nbcubes compte le nombre de bien placés
    front/back, dans l'ordre : DR = 8, DL = 4, UL = 2, UR = 1
    right/left : UB, DB, DF, UF
    up/down : LB, RB, FR, FL*/
    int i =0, longueurActuelle = 0, coinsBienPlaces = 0, nbCoinsPlaces = 0, position = 0, orientation = 0;
    char combiActuelle[NB_MVT_MAX*2+1] = "";

    switch (directionDebut)
    {
    case LEFT:
        break;
    case DOWN:
        break;
    case RIGHT:
        break;
    case UP:
        break;
    case FRONT:
        if (cubePremiereCroix->corner[URF].c == URF && cubePremiereCroix->corner[URF].o == 0)
        {
            nbCoinsPlaces++;
            coinsBienPlaces +=1;
        }
        if (cubePremiereCroix->corner[UFL].c == UFL && cubePremiereCroix->corner[UFL].o == 0)
        {
            nbCoinsPlaces++;
            coinsBienPlaces +=2;
        }
        if (cubePremiereCroix->corner[DLF].c == DLF && cubePremiereCroix->corner[DLF].o == 0)
        {
            nbCoinsPlaces++;
            coinsBienPlaces +=4;
        }
        if (cubePremiereCroix->corner[DFR].c == DFR && cubePremiereCroix->corner[DFR].o == 0)
        {
            nbCoinsPlaces++;
            coinsBienPlaces +=8;
        }
        while (coinsBienPlaces%2 == 0 && nbCoinsPlaces < 3)
        {//URF manquant
            for (i = 0 ; i < 8 ; i++)
            {
                if (cubePremiereCroix->corner[i].c == URF)
                {
                    position = i;
                    orientation = cubePremiereCroix->corner[i].o;
                }
            }
            switch (position)
            {
            case URF:
                if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubePremiereCroix);
                    coinsBienPlaces+=1;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    coinsBienPlaces+=1;
                    nbCoinsPlaces+=1;
                }
                break;
            case UFL:
                if (orientation == 0)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubePremiereCroix);
                    coinsBienPlaces+=1;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    coinsBienPlaces+=1;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubePremiereCroix);
                    coinsBienPlaces+=1;
                    nbCoinsPlaces+=1;
                }
                break;
            case ULB:
                if (orientation == 0)
                {
                    if ((coinsBienPlaces/2)%2 == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubePremiereCroix);
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                        ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubePremiereCroix);
                        coinsBienPlaces+=1;
                        nbCoinsPlaces+=1;
                    }
                    else if ((coinsBienPlaces/2)%2 == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubePremiereCroix);
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubePremiereCroix);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                        coinsBienPlaces+=1;
                        nbCoinsPlaces+=1;
                    }
                }
                else if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    coinsBienPlaces+=1;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubePremiereCroix);
                    coinsBienPlaces+=1;
                    nbCoinsPlaces+=1;
                }
                break;
            case UBR:
                if (orientation == 0)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubePremiereCroix);
                    coinsBienPlaces+=1;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    coinsBienPlaces+=1;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubePremiereCroix);
                    coinsBienPlaces+=1;
                    nbCoinsPlaces+=1;
                }
                break;
            case DFR:
                if (orientation == 0)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubePremiereCroix);
                    coinsBienPlaces+=1;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    coinsBienPlaces+=1;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    coinsBienPlaces+=1;
                    nbCoinsPlaces+=1;
                }
                break;
            case DLF:
                if (orientation == 0)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubePremiereCroix);
                    coinsBienPlaces+=1;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubePremiereCroix);
                    coinsBienPlaces+=1;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    coinsBienPlaces+=1;
                    nbCoinsPlaces+=1;
                }
                break;
            case DBL:
                if (orientation == 0)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    coinsBienPlaces+=1;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubePremiereCroix);
                    coinsBienPlaces+=1;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubePremiereCroix);
                    coinsBienPlaces+=1;
                    nbCoinsPlaces+=1;
                }
                break;
            case DRB:
                if (orientation == 0)
                {
                    if ((coinsBienPlaces/8)%2 == 0)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubePremiereCroix);
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                        ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubePremiereCroix);
                        coinsBienPlaces+=1;
                        nbCoinsPlaces+=1;
                    }
                    else if ((coinsBienPlaces/8)%2 == 1)
                    {
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubePremiereCroix);
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                        ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubePremiereCroix);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                        ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                        ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                        coinsBienPlaces+=1;
                        nbCoinsPlaces+=1;
                    }
                }
                else if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    coinsBienPlaces+=1;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubePremiereCroix);
                    coinsBienPlaces+=1;
                    nbCoinsPlaces+=1;
                }
                break;
            }


        }
        if (cubePremiereCroix->corner[UFL].c == UFL && cubePremiereCroix->corner[UFL].o == 0 && (coinsBienPlaces/2)%2 == 0)
        {//des coins a nouveau bien placés
            nbCoinsPlaces++;
            coinsBienPlaces +=2;
        }
        if (cubePremiereCroix->corner[DLF].c == DLF && cubePremiereCroix->corner[DLF].o == 0 && (coinsBienPlaces/4)%2 == 0)
        {
            nbCoinsPlaces++;
            coinsBienPlaces +=4;
        }
        if (cubePremiereCroix->corner[DFR].c == DFR && cubePremiereCroix->corner[DFR].o == 0 && (coinsBienPlaces/8)%2 == 0)
        {
            nbCoinsPlaces++;
            coinsBienPlaces +=8;
        }
        while ((coinsBienPlaces/2)%2 == 0 && nbCoinsPlaces < 3)
        {//UFL manquant
            for (i = 0 ; i < 8 ; i++)
            {
                if (cubePremiereCroix->corner[i].c == UFL)
                {
                    position = i;
                    orientation = cubePremiereCroix->corner[i].o;
                }
            }
            switch (position)
            {
            // URF en place
            case UFL:
                if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    coinsBienPlaces+=2;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    coinsBienPlaces+=2;
                    nbCoinsPlaces+=1;
                }
                break;
            case ULB:
                if (orientation == 0)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    coinsBienPlaces+=2;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    coinsBienPlaces+=2;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    coinsBienPlaces+=2;
                    nbCoinsPlaces+=1;
                }
                break;
            case UBR:
                if (orientation == 0)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    coinsBienPlaces+=2;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    coinsBienPlaces+=2;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    coinsBienPlaces+=2;
                    nbCoinsPlaces+=1;
                }
                break;
            case DFR:
                if (orientation == 0)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    coinsBienPlaces+=2;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubePremiereCroix);
                    coinsBienPlaces+=2;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    coinsBienPlaces+=2;
                    nbCoinsPlaces+=1;
                }
                break;
            case DLF:
                if (orientation == 0)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    coinsBienPlaces+=2;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    coinsBienPlaces+=2;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    coinsBienPlaces+=2;
                    nbCoinsPlaces+=1;
                }
                break;
            case DBL:
                if (orientation == 0)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    coinsBienPlaces+=2;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    coinsBienPlaces+=2;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    coinsBienPlaces+=2;
                    nbCoinsPlaces+=1;
                }
                break;
            case DRB:
                if (orientation == 0)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    coinsBienPlaces+=2;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    coinsBienPlaces+=2;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    coinsBienPlaces+=2;
                    nbCoinsPlaces+=1;
                }
                break;
            }


        }
        if (cubePremiereCroix->corner[DLF].c == DLF && cubePremiereCroix->corner[DLF].o == 0 && (coinsBienPlaces/4)%2 == 0)
        {//des coins a nouveau bien placés
            nbCoinsPlaces++;
            coinsBienPlaces +=4;
        }
        if (cubePremiereCroix->corner[DFR].c == DFR && cubePremiereCroix->corner[DFR].o == 0 && (coinsBienPlaces/8)%2 == 0)
        {
            nbCoinsPlaces++;
            coinsBienPlaces +=8;
        }
        while ((coinsBienPlaces/4)%2 == 0 && nbCoinsPlaces < 3)
        {//DLF manquant
            for (i = 0 ; i < 8 ; i++)
            {
                if (cubePremiereCroix->corner[i].c == DLF)
                {
                    position = i;
                    orientation = cubePremiereCroix->corner[i].o;
                }
            }
            switch (position)
            {
            //UFL en place
            case ULB:
                if (orientation == 0)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubePremiereCroix);
                    coinsBienPlaces+=4;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubePremiereCroix);
                    coinsBienPlaces+=4;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    coinsBienPlaces+=4;
                    nbCoinsPlaces+=1;
                }
                break;
            case UBR:
                if (orientation == 0)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubePremiereCroix);
                    coinsBienPlaces+=4;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    coinsBienPlaces+=4;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    coinsBienPlaces+=4;
                    nbCoinsPlaces+=1;
                }
                break;
            case DFR:
                if (orientation == 0)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubePremiereCroix);
                    coinsBienPlaces+=4;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubePremiereCroix);
                    coinsBienPlaces+=4;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    coinsBienPlaces+=4;
                    nbCoinsPlaces+=1;
                }
                break;
            case DLF:
                if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubePremiereCroix);
                    coinsBienPlaces+=4;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    coinsBienPlaces+=4;
                    nbCoinsPlaces+=1;
                }
                break;
            case DBL:
                if (orientation == 0)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    coinsBienPlaces+=4;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubePremiereCroix);
                    coinsBienPlaces+=4;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubePremiereCroix);
                    coinsBienPlaces+=4;
                    nbCoinsPlaces+=1;
                }
                break;
            case DRB:
                if (orientation == 0)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubePremiereCroix);
                    coinsBienPlaces+=4;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    coinsBienPlaces+=4;
                    nbCoinsPlaces+=1;
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubePremiereCroix);
                    ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubePremiereCroix);
                    coinsBienPlaces+=4;
                    nbCoinsPlaces+=1;
                }
                break;
            }
        }
        /*non necessaire dans cette phase
        while ((coinsBienPlaces/8)%2 == 0 && nbCoinsPlaces < 3)
        {//DFR manquant
            for (i = 0 ; i < 8 ; i++)
            {
                if (cubePremiereCroix->corner[i].c == DFR)
                {
                    fprintf(stdout, "Coin DFR detecte en position %d ; orientation %d\n", i, cubePremiereCroix->corner[i].o);
                    position = i;
                    orientation = cubePremiereCroix->corner[i].o;
                }
            }
            switch (position)
            {
            case URF:
                break;
            case UFL:
                break;
            case ULB:
                break;
            case UBR:
                break;
            case DFR:
                break;
            case DLF:
                break;
            case DBL:
                break;
            case DRB:
                break;
            }
        }*/
        break;
    case BACK:
        break;

    }

    longueurCombinaison += longueurActuelle;
    strcat(combinaison, combiActuelle);
    return longueurCombinaison;
}

int deuxiemeEtage(Cube* cubePremierEtage, char combinaison[], int longueurCombinaison, int directionDebut)
{/* coin libre correspond au nombre de 1/4 de tour horaire pour placer le coin libre en face du coin
    correspondant au bit 0x0:
    arete libre est celle en face de coin libre de la même valeur

    aretesBienPlacees et nbAretesPlacees correspondent aux mêmes coins que coins 1er etage

    faceUn et face deux sont définis dans l'ordre tel que la face du 1er étage, face un et face deux,
    les face adjacentes a l'arete libre, forment une base directe

    orientation coin est le sens du coin manquant en prenant pour référence les faces de début de résolution et de fin
    orientation arete vaut 0 si il faut la placer face à face Un et 1 si il faut la placer face a face Deux
    */
    int coinLibre = 0, areteLibre = 0, longueurActuelle = 0, longueurMini = NB_MVT_MAX, aretesBienPlacees = 0, nbAretesPlacees = 0, position = 0, orientation = 0, i = 0, j = 0, config = 0;
    int faceUn = 0, faceDeux = 0, orientationCoin = 0, orientationArete = 0;
    int ordre[4] = {0};
    char combiActuelle[NB_MVT_MAX*2+1] = "" , combiMini[NB_MVT_MAX*2+1];

    Cube cubeCopie = copie(*cubePremierEtage);
    Cube *cubeTravail = &cubeCopie;
    Cube cubeActuel;

    for (config = 0 ; config < factorielle(4) ; config++)
    {
        ordreSolveur(ordre, (long)config, 4);
        for (i = 0 ; i < 4 ; i++)
        {
        }
        //remises a zéro pour chaque test
        longueurActuelle = 0;
        strcpy(combiActuelle, "");
        *cubeTravail = copie(*cubePremierEtage);
        aretesBienPlacees =0;
        nbAretesPlacees = 0;

        switch (directionDebut)
        {
        case LEFT:
            break;
        case DOWN:
            break;
        case RIGHT:
            break;
        case UP:
            break;
        case FRONT:
            for (j = 0 ; j < 3 ; j++)
            {//remise des trois premières arêtes
                if (cubeTravail->corner[URF].c != URF || cubeTravail->corner[URF].o !=0)
                {
                    coinLibre = 0;
                }
                else if (cubeTravail->corner[UFL].c != UFL || cubeTravail->corner[UFL].o !=0)
                {
                    coinLibre = 1;
                }
                else if (cubeTravail->corner[DLF].c != DLF || cubeTravail->corner[DLF].o !=0)
                {
                    coinLibre = 2;
                }
                else
                {
                    coinLibre = 3;
                }

                if (cubeTravail->edge[UR].c == UR && cubeTravail->edge[UR].o == 0 && (aretesBienPlacees/1)%2 == 0)
                {//test de placements
                    aretesBienPlacees +=1;
                    nbAretesPlacees ++;
                }
                if (cubeTravail->edge[UL].c == UL && cubeTravail->edge[UL].o == 0 && (aretesBienPlacees/2)%2 == 0)
                {
                    aretesBienPlacees +=2;
                    nbAretesPlacees ++;
                }
                if (cubeTravail->edge[DL].c == DL && cubeTravail->edge[DL].o == 0 && (aretesBienPlacees/4)%2 == 0)
                {
                    aretesBienPlacees +=4;
                    nbAretesPlacees ++;
                }
                if (cubeTravail->edge[DR].c == DR && cubeTravail->edge[DR].o == 0 && (aretesBienPlacees/8)%2 == 0)
                {
                    aretesBienPlacees +=8;
                    nbAretesPlacees ++;
                }



                switch (ordre[j])
                {
                case 0:
                    while (aretesBienPlacees%2 == 0 && nbAretesPlacees < 3)
                    {//UR manquant
                        for (i = 0 ; i < 12 ; i++)
                        {
                            if (cubeTravail->edge[i].c == UR)
                            {
                                position = i;
                                orientation = cubeTravail->edge[i].o;
                            }
                        }
                        switch (position)
                        {
                        case UL:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+3)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((4-coinLibre)%4), cubeTravail);
                            aretesBienPlacees +=1;
                            nbAretesPlacees ++;
                            break;
                        case UB:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, (coinLibre%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((4-coinLibre)%4), cubeTravail);
                            aretesBienPlacees +=1;
                            nbAretesPlacees ++;
                            break;
                        case UR:
                            if (orientation == 0)
                            {
                                aretesBienPlacees +=1;
                                nbAretesPlacees ++;
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, (coinLibre%4), cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((4-coinLibre)%4), cubeTravail);
                                aretesBienPlacees +=1;
                                nbAretesPlacees ++;
                            }
                            break;
                        case DL:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+2)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((4-coinLibre)%4), cubeTravail);
                            aretesBienPlacees +=1;
                            nbAretesPlacees ++;
                            break;
                        case DB:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, (coinLibre%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((4-coinLibre)%4), cubeTravail);
                            aretesBienPlacees +=1;
                            nbAretesPlacees ++;
                            break;
                        case DR:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+1)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((4-coinLibre)%4), cubeTravail);
                            aretesBienPlacees +=1;
                            nbAretesPlacees ++;
                            break;
                        case LB:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, (coinLibre%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((4-coinLibre)%4), cubeTravail);
                            aretesBienPlacees +=1;
                            nbAretesPlacees ++;
                            break;
                        case RB:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, (coinLibre%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((4-coinLibre)%4), cubeTravail);
                            aretesBienPlacees +=1;
                            nbAretesPlacees ++;
                            break;
                        }
                    }
                    break;

                case 1:
                    while ((aretesBienPlacees/2)%2 == 0 && nbAretesPlacees < 3)
                    {//UL manquant
                        for (i = 0 ; i < 12 ; i++)
                        {
                            if (cubeTravail->edge[i].c == UL)
                            {
                                position = i;
                                orientation = cubeTravail->edge[i].o;
                            }
                        }
                        switch (position)
                        {
                        case UL:
                            if (orientation == 0)
                            {
                                aretesBienPlacees +=2;
                                nbAretesPlacees ++;
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+3)%4), cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((5-coinLibre)%4), cubeTravail);
                                aretesBienPlacees +=2;
                                nbAretesPlacees ++;
                            }

                            break;
                        case UB:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+3)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((5-coinLibre)%4), cubeTravail);
                            aretesBienPlacees +=2;
                            nbAretesPlacees ++;
                            break;
                        case UR:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((5-coinLibre)%4), cubeTravail);
                            aretesBienPlacees +=2;
                            nbAretesPlacees ++;
                            break;
                        case DL:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+2)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((5-coinLibre)%4), cubeTravail);
                            aretesBienPlacees +=2;
                            nbAretesPlacees ++;
                            break;
                        case DB:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+3)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((5-coinLibre)%4), cubeTravail);
                            aretesBienPlacees +=2;
                            nbAretesPlacees ++;
                            break;
                        case DR:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+1)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((5-coinLibre)%4), cubeTravail);
                            aretesBienPlacees +=2;
                            nbAretesPlacees ++;
                            break;
                        case LB:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+3)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((5-coinLibre)%4), cubeTravail);
                            aretesBienPlacees +=2;
                            nbAretesPlacees ++;
                            break;
                        case RB:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+3)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((5-coinLibre)%4), cubeTravail);
                            aretesBienPlacees +=2;
                            nbAretesPlacees ++;
                            break;
                        }
                    }
                    break;

                case 2:
                    while ((aretesBienPlacees/4)%2 == 0 && nbAretesPlacees < 3)
                    {//DL manquant
                        for (i = 0 ; i < 12 ; i++)
                        {
                            if (cubeTravail->edge[i].c == DL)
                            {
                                position = i;
                                orientation = cubeTravail->edge[i].o;
                            }
                        }
                        switch (position)
                        {
                        case UL:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+3)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((6-coinLibre)%4), cubeTravail);
                            aretesBienPlacees +=4;
                            nbAretesPlacees ++;
                            break;
                        case UB:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+2)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((6-coinLibre)%4), cubeTravail);
                            aretesBienPlacees +=4;
                            nbAretesPlacees ++;
                            break;
                        case UR:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((6-coinLibre)%4), cubeTravail);
                            aretesBienPlacees +=4;
                            nbAretesPlacees ++;
                            break;
                        case DL:
                            if (orientation == 0)
                            {
                                aretesBienPlacees +=4;
                                nbAretesPlacees ++;
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+2)%4), cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((6-coinLibre)%4), cubeTravail);
                                aretesBienPlacees +=4;
                                nbAretesPlacees ++;
                            }
                            break;
                        case DB:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+2)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((6-coinLibre)%4), cubeTravail);
                            aretesBienPlacees +=4;
                            nbAretesPlacees ++;
                            break;
                        case DR:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+1)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((6-coinLibre)%4), cubeTravail);
                            aretesBienPlacees +=4;
                            nbAretesPlacees ++;
                            break;
                        case LB:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+2)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((6-coinLibre)%4), cubeTravail);
                            aretesBienPlacees +=4;
                            nbAretesPlacees ++;
                            break;
                        case RB:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+2)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((6-coinLibre)%4), cubeTravail);
                            aretesBienPlacees +=4;
                            nbAretesPlacees ++;
                        }
                    }
                    break;

                case 3:
                    while ((aretesBienPlacees/8)%2 == 0 && nbAretesPlacees < 3)
                    {//DR manquant
                        for (i = 0 ; i < 12 ; i++)
                        {
                            if (cubeTravail->edge[i].c == DR)
                            {
                                position = i;
                                orientation = cubeTravail->edge[i].o;
                            }
                        }
                        switch (position)
                        {
                        case UL:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+3)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 2, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, (3-coinLibre), cubeTravail);
                            aretesBienPlacees +=8;
                            nbAretesPlacees ++;
                            break;
                        case UB:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+1)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, (3-coinLibre), cubeTravail);
                            aretesBienPlacees +=8;
                            nbAretesPlacees ++;
                            break;
                        case UR:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, (3-coinLibre), cubeTravail);
                            aretesBienPlacees +=8;
                            nbAretesPlacees ++;
                            break;
                        case DL:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+2)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, 3, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTravail);
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, (3-coinLibre), cubeTravail);
                            aretesBienPlacees +=8;
                            nbAretesPlacees ++;
                            break;
                        case DB:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+1)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, (3-coinLibre), cubeTravail);
                            aretesBienPlacees +=8;
                            nbAretesPlacees ++;
                            break;
                        case DR:
                            if (orientation == 0)
                            {
                                aretesBienPlacees +=8;
                                nbAretesPlacees ++;
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+1)%4), cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, (3-coinLibre), cubeTravail);
                                aretesBienPlacees +=8;
                                nbAretesPlacees ++;
                            }
                            break;
                        case LB:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+1)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, (3-coinLibre), cubeTravail);
                            aretesBienPlacees +=8;
                            nbAretesPlacees ++;
                            break;
                        case RB:
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((coinLibre+1)%4), cubeTravail);
                            if (orientation == 0)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTravail);
                            }
                            else if (orientation == 1)
                            {
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                                ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTravail);
                            }
                            ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, (3-coinLibre), cubeTravail);
                            aretesBienPlacees +=8;
                            nbAretesPlacees ++;
                            break;
                        }
                    }

                    break;
                }//end switch ordre[j]

                //gestion d'arêtes incorrectement placées
                if ((aretesBienPlacees/1)%2 == 1 && (cubeTravail->edge[UR].c != UR || cubeTravail->edge[UR].o != 0))
                {
                    fprintf(stderr, "ERREUR : arete UR incorrectement placée. \nconfig %d, valeur traitée %d\nArete placee etait en position %d, orientation %d.\n", config, ordre[j], position, orientation);
                }
                if ((aretesBienPlacees/2)%2 == 1 && (cubeTravail->edge[UL].c != UL || cubeTravail->edge[UL].o != 0))
                {
                    fprintf(stderr, "ERREUR : arete UL incorrectement placée. \nconfig %d, valeur traitée %d\nArete placee etait en position %d, orientation %d.\n", config, ordre[j], position, orientation);
                }
                if ((aretesBienPlacees/4)%2 == 1 && (cubeTravail->edge[DL].c != DL || cubeTravail->edge[DL].o != 0))
                {
                    fprintf(stderr, "ERREUR : arete DL incorrectement placée. \nconfig %d, valeur traitée %d\nArete placee etait en position %d, orientation %d.\n", config, ordre[j], position, orientation);
                }
                if ((aretesBienPlacees/8)%2 == 1 && (cubeTravail->edge[DR].c != DR || cubeTravail->edge[DR].o != 0))
                {
                    fprintf(stderr, "ERREUR : arete DR incorrectement placée. \nconfig %d, valeur traitée %d\nArete placee etait en position %d, orientation %d.\n", config, ordre[j], position, orientation);
                }

            }
            //remise du dernier coin, calcul de l'arête libre
            if (cubeTravail->edge[UR].c != UR || cubeTravail->edge[UR].o != 0)
            {
                areteLibre = 0;
                faceUn = RIGHT;
                faceDeux = UP;
            }
            else if (cubeTravail->edge[UL].c != UL || cubeTravail->edge[UL].o != 0)
            {
                areteLibre = 1;
                faceUn = UP;
                faceDeux = LEFT;
            }
            else if (cubeTravail->edge[DL].c != DL || cubeTravail->edge[DL].o != 0)
            {
                areteLibre = 2;
                faceUn = LEFT;
                faceDeux = DOWN;
            }
            else
            {
                areteLibre = 3;
                faceUn = DOWN;
                faceDeux = RIGHT;
            }

            switch (coinLibre)
            {
            case 0://coin URF libre
                for (i = 0 ; i < 8 ; i ++)
                {//recherche
                    if (cubeTravail->corner[i].c == URF)
                    {
                        position = i;
                        orientation = cubeTravail->corner[i].o;

                        if ((position == ULB && orientation == 0)||(position == UBR && orientation == 2)||
                            (position == DBL && orientation == 2)||(position == DRB && orientation == 0))
                        {
                            orientationCoin = 0;
                        }
                        else if ((position == ULB && orientation == 1)||(position == UBR && orientation == 0)||
                            (position == DBL && orientation == 0)||(position == DRB && orientation == 1))
                        {
                            orientationCoin = 1;
                        }
                        else if ((position == ULB && orientation == 2)||(position == UBR && orientation == 1)||
                            (position == DBL && orientation == 1)||(position == DRB && orientation == 2))
                        {
                            orientationCoin = 2;
                        }
                        else
                        {
                            orientationCoin = -1;
                        }
                    }
                }
                break;
            case 1://coin UFL libre
                for (i = 0 ; i < 8 ; i ++)
                {//recherche
                    if (cubeTravail->corner[i].c == UFL)
                    {
                        position = i;
                        orientation = cubeTravail->corner[i].o;

                        if ((position == ULB && orientation == 1)||(position == UBR && orientation == 0)||
                            (position == DBL && orientation == 0)||(position == DRB && orientation == 1))
                        {
                            orientationCoin = 0;
                        }
                        else if ((position == ULB && orientation == 2)||(position == UBR && orientation == 1)||
                            (position == DBL && orientation == 1)||(position == DRB && orientation == 2))
                        {
                            orientationCoin = 1;
                        }
                        else if ((position == ULB && orientation == 0)||(position == UBR && orientation == 2)||
                            (position == DBL && orientation == 2)||(position == DRB && orientation == 0))
                        {
                            orientationCoin = 2;
                        }
                        else
                        {
                            orientationCoin = -1;
                        }
                    }
                }
                break;
            case 2://coin DLF libre
                for (i = 0 ; i < 8 ; i ++)
                {//recherche
                    if (cubeTravail->corner[i].c == DLF)
                    {
                        position = i;
                        orientation = cubeTravail->corner[i].o;

                        if ((position == ULB && orientation == 0)||(position == UBR && orientation == 2)||
                            (position == DBL && orientation == 2)||(position == DRB && orientation == 0))
                        {
                            orientationCoin = 0;
                        }
                        else if ((position == ULB && orientation == 1)||(position == UBR && orientation == 0)||
                            (position == DBL && orientation == 0)||(position == DRB && orientation == 1))
                        {
                            orientationCoin = 1;
                        }
                        else if ((position == ULB && orientation == 2)||(position == UBR && orientation == 1)||
                            (position == DBL && orientation == 1)||(position == DRB && orientation == 2))
                        {
                            orientationCoin = 2;
                        }
                        else
                        {
                            orientationCoin = -1;
                        }
                    }
                }
                break;
            case 3://coin DFR libre
                for (i = 0 ; i < 8 ; i ++)
                {//recherche
                    if (cubeTravail->corner[i].c == DFR)
                    {
                        position = i;
                        orientation = cubeTravail->corner[i].o;

                        if ((position == ULB && orientation == 1)||(position == UBR && orientation == 0)||
                            (position == DBL && orientation == 0)||(position == DRB && orientation == 1))
                        {
                            orientationCoin = 0;
                        }
                        else if ((position == ULB && orientation == 2)||(position == UBR && orientation == 1)||
                            (position == DBL && orientation == 1)||(position == DRB && orientation == 2))
                        {
                            orientationCoin = 1;
                        }
                        else if ((position == ULB && orientation == 0)||(position == UBR && orientation == 2)||
                            (position == DBL && orientation == 2)||(position == DRB && orientation == 0))
                        {
                            orientationCoin = 2;
                        }
                        else
                        {
                            orientationCoin = -1;
                        }
                    }
                }
                break;
            }//coin repéré
            if (position == URF || position == UFL || position == DLF ||position == DFR)
            {//coin a son emplacement
                ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((4+coinLibre-areteLibre)%4), cubeTravail);
                if (orientation ==0)
                {
                    //nothing to be done
                }
                else if (orientation == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 1, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 3, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 3, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 1, cubeTravail);
                }
                else if (orientation == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 3, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 1, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 1, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 3, cubeTravail);
                }
                ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((4+areteLibre-coinLibre)%4), cubeTravail);
            }
            else
            {//sinon on lui règle son compte
                ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((4+coinLibre-areteLibre)%4), cubeTravail);
                switch (position)
                {
                case ULB:
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, ((areteLibre+3)%4), cubeTravail);
                    break;
                case UBR:
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, ((areteLibre)%4), cubeTravail);
                    break;
                case DBL:
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, ((areteLibre+2)%4), cubeTravail);
                    break;
                case DRB:
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, ((areteLibre+1)%4), cubeTravail);
                    break;
                }
                if (orientationCoin == 0)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 3, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 1, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 1, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 3, cubeTravail);
                }
                else if (orientationCoin == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 1, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 3, cubeTravail);
                }
                else if (orientationCoin == 2)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 3, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 1, cubeTravail);
                }
                ajouterMouvement(combiActuelle, &longueurActuelle, FRONT, ((4+areteLibre-coinLibre)%4), cubeTravail);
                coinLibre = -1;
            }//coin en place! (finaly)

            //remise de la dernière arête
            switch (areteLibre)
            {
            case 0://arete UR libre
                for (i = 0 ; i < 12 ; i++)
                {//recherche
                    if (cubeTravail->edge[i].c == UR)
                    {
                        position = i;
                        orientation = cubeTravail->edge[i].o;
                        if ((position == UB && orientation == 1)||(position == DB && orientation == 1)||
                            (position == LB && orientation == 0)||(position == RB && orientation == 0))
                        {
                            orientationArete = 0;
                        }
                        else if ((position == UB && orientation == 0)||(position == DB && orientation == 0)||
                            (position == LB && orientation == 1)||(position == RB && orientation == 1))
                        {
                            orientationArete = 1;
                        }
                        else
                        {
                            orientationArete = -1;
                        }
                    }
                }
                break;
            case 1://arete UL libre
                for (i = 0 ; i < 12 ; i++)
                {//recherche
                    if (cubeTravail->edge[i].c == UL)
                    {
                        position = i;
                        orientation = cubeTravail->edge[i].o;
                        if ((position == UB && orientation == 0)||(position == DB && orientation == 0)||
                            (position == LB && orientation == 1)||(position == RB && orientation == 1))
                        {
                            orientationArete = 0;
                        }
                        else if ((position == UB && orientation == 1)||(position == DB && orientation == 1)||
                            (position == LB && orientation == 0)||(position == RB && orientation == 0))
                        {
                            orientationArete = 1;
                        }
                        else
                        {
                            orientationArete = -1;
                        }
                    }
                }
                break;
            case 2://arete DL libre
                for (i = 0 ; i < 12 ; i++)
                {//recherche
                    if (cubeTravail->edge[i].c == DL)
                    {
                        position = i;
                        orientation = cubeTravail->edge[i].o;
                        if ((position == UB && orientation == 1)||(position == DB && orientation == 1)||
                            (position == LB && orientation == 0)||(position == RB && orientation == 0))
                        {
                            orientationArete = 0;
                        }
                        else if ((position == UB && orientation == 0)||(position == DB && orientation == 0)||
                            (position == LB && orientation == 1)||(position == RB && orientation == 1))
                        {
                            orientationArete = 1;
                        }
                        else
                        {
                            orientationArete = -1;
                        }
                    }
                }
                break;
            case 3://arete DR libre
                for (i = 0 ; i < 12 ; i++)
                {//recherche
                    if (cubeTravail->edge[i].c == DR)
                    {
                        position = i;
                        orientation = cubeTravail->edge[i].o;
                        if ((position == UB && orientation == 0)||(position == DB && orientation == 0)||
                            (position == LB && orientation == 1)||(position == RB && orientation == 1))
                        {
                            orientationArete = 0;
                        }
                        else if ((position == UB && orientation == 1)||(position == DB && orientation == 1)||
                            (position == LB && orientation == 0)||(position == RB && orientation == 0))
                        {
                            orientationArete = 1;
                        }
                        else
                        {
                            orientationArete = -1;
                        }
                    }
                }
                break;
            }
            if (orientationArete == -1&& orientation == 1)
            {//arete dans sa position inversée
                ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 3, cubeTravail);
                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 3, cubeTravail);
                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 3, cubeTravail);
                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 1, cubeTravail);
                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 1, cubeTravail);

                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);

                ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 1, cubeTravail);
                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 1, cubeTravail);
                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 1, cubeTravail);
                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 3, cubeTravail);
                ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 3, cubeTravail);
            }
            else if (orientationArete != -1)
            {//arete sur la 3e couronne
                switch (position)
                {//placement
                case UB:
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, ((3+areteLibre+orientationArete)%4), cubeTravail);
                    break;
                case DB:
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, ((1+areteLibre+orientationArete)%4), cubeTravail);
                    break;
                case LB:
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, ((2+areteLibre+orientationArete)%4), cubeTravail);
                    break;
                case RB:
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, ((areteLibre+orientationArete)%4), cubeTravail);
                    break;
                }
                if (orientationArete == 0)
                {//solveur!
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 3, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 3, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 3, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 1, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 1, cubeTravail);
                }
                else if (orientationArete == 1)
                {
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 1, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 1, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 1, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 3, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTravail);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 3, cubeTravail);
                }
            }//2e phase terminée! (bordel, il était temps)
            break;
        case BACK:
            break;
        }//end direction switch
        longueurActuelle = lissage(combiActuelle, longueurActuelle);
        if (longueurActuelle < longueurMini)
        {
            cubeActuel = copie(*cubeTravail);
            longueurMini = longueurActuelle;
            strcpy(combiMini, combiActuelle);
        }

    }
    *cubePremierEtage = copie(cubeActuel);
    longueurCombinaison += longueurMini;
    strcat(combinaison, combiMini);
    return longueurCombinaison;
}

int croixTroisiemeEtage(Cube* cubeDeuxEtages, char combinaison[], int longueurCombinaison, int directionDebut)
{/* aretes orientées vaut de 0 a 15 : 1 bit par arete bien orientée.
    Pour l'ordre, voir aretesPremierEtage
    */
    int i =0, j = 0, aretesOrientees = 0, longueurActuelle = 0;
    char combiActuelle[NB_MVT_MAX*2+1];

    switch (directionDebut)
    {
    case LEFT:
        break;
    case DOWN:
        break;
    case RIGHT:
        break;
    case UP:
        break;
    case FRONT:
        if (((cubeDeuxEtages->edge[RB].c == UB || cubeDeuxEtages->edge[RB].c == DB) && cubeDeuxEtages->edge[RB].o == 1)||
            ((cubeDeuxEtages->edge[RB].c == LB || cubeDeuxEtages->edge[RB].c == RB) && cubeDeuxEtages->edge[RB].o == 0))
        {//arete RB orientée
            aretesOrientees+=1;
        }
        if (((cubeDeuxEtages->edge[UB].c == UB || cubeDeuxEtages->edge[UB].c == DB) && cubeDeuxEtages->edge[UB].o == 0)||
            ((cubeDeuxEtages->edge[UB].c == LB || cubeDeuxEtages->edge[UB].c == RB) && cubeDeuxEtages->edge[UB].o == 1))
        {//arete UB orientée
            aretesOrientees+=2;
        }
        if (((cubeDeuxEtages->edge[LB].c == UB || cubeDeuxEtages->edge[LB].c == DB) && cubeDeuxEtages->edge[LB].o == 1)||
            ((cubeDeuxEtages->edge[LB].c == LB || cubeDeuxEtages->edge[LB].c == RB) && cubeDeuxEtages->edge[LB].o == 0))
        {//arete LB orientée
            aretesOrientees+=4;
        }
        if (((cubeDeuxEtages->edge[DB].c == UB || cubeDeuxEtages->edge[DB].c == DB) && cubeDeuxEtages->edge[DB].o == 0)||
            ((cubeDeuxEtages->edge[DB].c == LB || cubeDeuxEtages->edge[DB].c == RB) && cubeDeuxEtages->edge[DB].o == 1))
        {//arete DB orientée
            aretesOrientees+=8;
        }
        switch (aretesOrientees)
        {//remise directe
        case 0://aucun
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeDeuxEtages);

            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeDeuxEtages);
            break;
        case 3://RB et UB
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeDeuxEtages);
            break;
        case 5://RB et LB
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeDeuxEtages);
            break;
        case 6://UB et LB
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeDeuxEtages);
            break;
        case 9://RB et DB
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeDeuxEtages);
            break;
        case 10://UB et DB
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeDeuxEtages);
            break;
        case 12://LB et DB
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeDeuxEtages);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeDeuxEtages);
            break;
        case 15://tous
            break;
        default:
            fprintf(stderr, "ERREUR : Le cube est insolvable!\n");
            break;
        }

        break;
    case BACK:
        break;
    }
    longueurCombinaison += longueurActuelle;
    strcat(combinaison, combiActuelle);
    return longueurCombinaison;
}

int aretesTroisiemeEtage(Cube* cubeTroisiemeCroix, char combinaison[], int longueurCombinaison, int directionDebut)
{/* Pour ordre Aretes, on prend les valeurs dans l'ordre croissant des arêtes définies en phase 1,
    on leur associe les valeurs de 0 a 3
    ex pour front/back : R = 0, U = 1, L = 2 et B = 3
    ordre[]
    */
    int longueurActuelle = 0, valeurOrdre = 0, i =0, j = 0;
    int ordreAretes[4] = {0}, correspondances[4];
    char combiActuelle[NB_MVT_MAX*2+1] = "";


    switch (directionDebut)
    {
    case LEFT:
        break;
    case DOWN:
        break;
    case RIGHT:
        break;
    case UP:
        break;
    case FRONT:
        correspondances[0] = RB;
        correspondances[1] = UB;
        correspondances[2] = LB;
        correspondances[3] = DB;
        for (i = 0 ; i < 4 ; i ++)
        {
            for (j = 0 ; j < 4 ; j++)
            {
                if (cubeTroisiemeCroix->edge[correspondances[i]].c == correspondances[j])
                {
                    ordreAretes[i] = j;
                }
            }
        }
        valeurOrdre = (int)ordreInverse(ordreAretes, 4);
        switch (valeurOrdre)
        {
        case 0://0123
            break;
        case 1://0132 U+B'
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            break;
        case 2://0213 R+B'
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            break;
        case 3://0231 L
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            break;
        case 4://0312 L'
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            break;
        case 5://0321 R+B2 + U+B
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTroisiemeCroix);

            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeCroix);
            break;
        case 6://1023 D+B'
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            break;
        case 7://1032 U+B2 + L
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeCroix);

            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            break;
        case 8://1203 U
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            break;
        case 9://1230 B
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            break;
        case 10://1302 L+B
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeCroix);
            break;
        case 11://1320 R
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            break;
        case 12://2013 U'
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            break;
        case 13://2031 R+B
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeCroix);
            break;
        case 14://2103 U'+B2 + U+B
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeCroix);

            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeCroix);
            break;
        case 15://2130 D
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            break;
        case 16://2301 B2
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            break;
        case 17://2310 U+B
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeCroix);
            break;
        case 18://3012 B'
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeCroix);
            break;
        case 19://3021 R'
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            break;
        case 20://3102 D'
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            break;
        case 21://3120 L+B'
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            break;
        case 22://3201 D+B
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeCroix);
            break;
        case 23://3210 L'+B2 + L
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeCroix);

            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeCroix);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 2, cubeTroisiemeCroix);
            break;
        }
        break;
    case BACK:
        break;
    }
    longueurCombinaison += longueurActuelle;
    strcat(combinaison, combiActuelle);
    return longueurCombinaison;
}

int coinsTroisiemeEtage(Cube* cubeTroisiemeAretes, char combinaison[], int longueurCombinaison, int directionDebut)
{/* Le principe de codage des positions est similaire aux aretes 3e étage, voir coins 1er étage pour les ordres*/
    int i = 0, j = 0, longueurActuelle = 0, valeurOrdre = 0;
    int ordreCoins[4] = {0}, correspondances[4]= {0};
    char combiActuelle[NB_MVT_MAX*2+1] = "";

    switch (directionDebut)
    {
    case LEFT:
        break;
    case DOWN:
        break;
    case RIGHT:
        break;
    case UP:
        break;
    case FRONT:
        correspondances[0] = UBR;
        correspondances[1] = ULB;
        correspondances[2] = DBL;
        correspondances[3] = DRB;
        for (i = 0 ; i < 4 ; i ++)
        {
            for (j = 0 ; j < 4 ; j++)
            {
                if (cubeTroisiemeAretes->corner[correspondances[i]].c == correspondances[j])
                {
                    ordreCoins[i] = j;
                }
            }
        }
        valeurOrdre = (int)ordreInverse(ordreCoins, 4);
        switch (valeurOrdre)
        {
        case 0://0123
            break;
        case 3://0231 D, B
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTroisiemeAretes);
            break;
        case 4://0312 L, B'
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeAretes);
            break;
        case 7://1032 U, B' + L, B'
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTroisiemeAretes);

            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeAretes);
            break;
        case 8://1203 L, B
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTroisiemeAretes);
            break;
        case 11://1320 U, B
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeAretes);
            break;
        case 12://2013 U, B'
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTroisiemeAretes);
            break;
        case 15://2130 R, B
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeAretes);
            break;
        case 16://2301 L, B + D, B
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTroisiemeAretes);

            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTroisiemeAretes);
            break;
        case 19://3021 R, B'
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTroisiemeAretes);
            break;
        case 20://3102 D, B'
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeAretes);
            break;
        case 23://3210 U, B + L,B'
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, RIGHT, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, LEFT, 3, cubeTroisiemeAretes);

            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, DOWN, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 3, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, BACK, 1, cubeTroisiemeAretes);
            ajouterMouvement(combiActuelle, &longueurActuelle, UP, 1, cubeTroisiemeAretes);
            break;
        default:
            fprintf(stderr, "ERREUR : Cube insolvable!\n");
            break;
        }
        break;
    case BACK:
        break;
    }

    longueurCombinaison += longueurActuelle;
    strcat(combinaison, combiActuelle);
    return longueurCombinaison;
}

int orientationCoinsTroisiemeEtage(Cube* cubePositionsFinies, char combinaison[], int longueurCombinaison, int directionDebut)
{/* le tableau des orientations est de 5 cases car on travaille avec des paires, on double la première case
    faceUn, faceDeux, servent a eppliquer la formule générique en fonction de ces variables.
    */
    int longueurActuelle = 0, faceUn = 0, faceDeux = 0, faceTrois = 0, somme = 0, paires = 0, i =0;
    int orientations[5] = {0}, correspondances[5] = {0};
    char combiActuelle[NB_MVT_MAX*2+1] = "";

    switch (directionDebut)
    {
    case LEFT:
        break;
    case DOWN:
        break;
    case RIGHT:
        break;
    case UP:
        break;
    case FRONT:
        correspondances[0] = UBR;
        correspondances[1] = ULB;
        correspondances[2] = DBL;
        correspondances[3] = DRB;
        correspondances[4] = UBR;
        for (i = 0 ; i < 5 ; i ++)
        {//lecture de l'état
            orientations[i] = cubePositionsFinies->corner[correspondances[i]].o;
        }
        for (i = 0 ; i < 4 ; i++)
        {//calcul des données
            somme+= orientations[i];
            if (orientations[i] != 0 && orientations[i+1] != 0)
            {
                paires++;
            }
        }

        if ((somme%3) != 0)
        {//test d'erreur
            fprintf(stderr, "ERREUR : Cube insolvable! (somme des orientations des coins != 3)\n");
            break;
        }
        while (somme !=0)
        {
            for (i = 0 ; i < 4 ; i++)
            {//parcours du tableau pour modifier des paires
                if (orientations[i] != 0 &&(orientations[i+1] != 0 || paires == 0))
                {//une paire a modifier
                    if (orientations[i] == 1)
                    {//sens direct
                        faceDeux = BACK;
                        orientations[i] = (orientations[i]+2)%3;
                        orientations[i+1] = (orientations[i+1]+1)%3;
                        switch (i)
                        {
                        case 0://paire UBR/ULB
                            faceUn = DOWN;
                            faceTrois = UP;
                            orientations[4] = orientations[0];
                            break;
                        case 1://paire ULB/DBL
                            faceUn = RIGHT;
                            faceTrois = LEFT;
                            break;
                        case 2://paire DBL/DRB
                            faceUn = UP;
                            faceTrois = DOWN;
                            break;
                        case 3://paire DRB/UBR
                            faceUn = LEFT;
                            faceTrois = RIGHT;
                            orientations[0] = orientations[4];
                            break;
                        }
                    }
                    else if (orientations[i] == 2)
                    {//sens inverse!
                        faceUn = FRONT;
                        faceTrois = BACK;
                        orientations[i] = (orientations[i]+1)%3;
                        orientations[i+1] = (orientations[i+1]+2)%3;
                        switch (i)
                        {
                        case 0://paire UBR/ULB
                            faceDeux = UP;
                            orientations[4] = orientations[0];
                            break;
                        case 1://paire ULB/DBL
                            faceDeux = LEFT;
                            break;
                        case 2://paire DBL/DRB
                            faceDeux = DOWN;
                            break;
                        case 3://paire DRB/UBR
                            faceDeux = RIGHT;
                            orientations[0] = orientations[4];
                            break;
                        }
                    }//mouvements paramétrés, application
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 1, cubePositionsFinies);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 1, cubePositionsFinies);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 3, cubePositionsFinies);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 1, cubePositionsFinies);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 1, cubePositionsFinies);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 2, cubePositionsFinies);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceUn, 3, cubePositionsFinies);

                    ajouterMouvement(combiActuelle, &longueurActuelle, faceTrois, 3, cubePositionsFinies);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 3, cubePositionsFinies);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceTrois, 1, cubePositionsFinies);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 3, cubePositionsFinies);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceTrois, 3, cubePositionsFinies);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceDeux, 2, cubePositionsFinies);
                    ajouterMouvement(combiActuelle, &longueurActuelle, faceTrois, 1, cubePositionsFinies);
                }
            }


            for (i = 0 ; i < 5 ; i ++)
            {//lecture de l'état
                orientations[i] = cubePositionsFinies->corner[correspondances[i]].o;
            }
            somme = 0;
            paires = 0;
            for (i = 0 ; i < 4 ; i++)
            {//calcul des données
                somme+= orientations[i];
                if (orientations[i] != 0 && orientations[i+1] != 0)
                {
                    paires++;
                }
            }

            if ((somme%3) != 0)
            {//test d'erreur
                fprintf(stderr, "ERREUR : Cube insolvable! (somme des orientations des coins != 3)\n");
                break;
            }
        }
        break;
    case BACK:
        break;
    }

    longueurCombinaison += longueurActuelle;
    strcat(combinaison, combiActuelle);
    return longueurCombinaison;
}

void ordreSolveur(int ordre[], long valeur, long nbValeurs)
{/*cette fonction permet de tester tous les ordres pour une même étape:
    elle renvoie l'ordre dans lequel vont etre recherchés les cubies en fonction de l'occurence actuelle
    */
    long i = 0, j = 0, k = 0, present = 0, valeursLibres = 0, valeurAffectee =0;

    for(i = 0 ; i < nbValeurs ; i++)
    {
        ordre[i] = (int)((valeur%factorielle(nbValeurs-i))/factorielle(nbValeurs-i-1));
        valeursLibres = 0;
        for (k = 0 ; k < nbValeurs ; k++)
        {//on cherche la présence de chaque valeur
            present = 0;//booleen
            for (j = 0 ; j < i ; j++)
            {//on cherche une valeur
                if (ordre[j] == k)
                {
                    present = 1;
                }
            }
            if (present == 0)
            {
                if (ordre[i] == (int)valeursLibres)
                {
                    valeurAffectee = k;
                }
                valeursLibres++;
            }
        }
        ordre[i] = (int)valeurAffectee;
    }

}

long ordreInverse(int ordre[], long nbValeurs)
{/* Cette fonction effectue l'opération inverse a la fonction ordre : on lui rentre des valeurs ordonnées
    et elle renvoie un entier unique pour chaque ordre
    */
    long i = 0, j = 0, inferieurs = 0;
    long valeur = 0;
    for (i = 0 ; i < nbValeurs ; i++)
    {
        inferieurs = 0;
        for (j = 0 ; j < i ; j++)
        {
            if (ordre[j] < ordre[i])
            {
                inferieurs ++;
            }
        }
        valeur += ((((long)ordre[i])-inferieurs)*factorielle(nbValeurs-i-1));
    }
    return valeur;
}

long factorielle(long n)
{
    long fact = 1, i = 0;
    for (i = 1 ; i <= n ; i ++)
    {
        fact *= i;
    }
    return fact;
}



