#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constantes.h"
#include "combinaison.h"
#include "mouvements.h"


int lissage(char combinaison[], int longueurCombinaison)
{//réduit la combi et renvoie la nouvelle longueur
    int i =0;
    while (!chaineReduite(combinaison, longueurCombinaison))
    {
        for ( i = 0 ; i < (longueurCombinaison-1) ; i++)
        {
            if (combinaison[2*i] == combinaison[2*(i+1)])
            {//si deux fois la même face, on compresse
                combinaison[2*i+1] = (((combinaison[2*i+1] -48)+(combinaison[2*i+3] - 48))%4) + 48;
                combinaison[2*(i+1)] =0;
                combinaison[2*(i+1)+1] =0;
                reduire(combinaison, longueurCombinaison);
                longueurCombinaison--;
            }
            if (combinaison[2*i+1] == '0')
            {//si la somme des mouvements est multiple de 4, on supprime
                combinaison[2*i] = 0;
                combinaison[2*i+1] = 0;
                reduire(combinaison, longueurCombinaison);
                longueurCombinaison--;
            }
        }
        if (combinaison[2*longueurCombinaison-1] == '0')
            {//dernier mouvement nul
                combinaison[2*(longueurCombinaison-1)] = 0;
                combinaison[2*longueurCombinaison-1] = 0;
                longueurCombinaison--;
            }
        combinaison[longueurCombinaison*2] = '\0';
    }
    combinaison[longueurCombinaison*2] = '\0';//fin de chaine
    return longueurCombinaison;
}

int chaineReduite(char combinaison[], int longueurCombinaison)
{//cherche si la combi est réduite au max
    int i = 0;
    for (i = 0 ; i < longueurCombinaison-1 ; i++)
    {
        if (combinaison[i*2] == combinaison[(i+1)*2])
        {//deux cases pareilles
            return 0;
        }
        if (combinaison[i*2+1] == '0')
        {//rotation nulle
            return 0;
        }
        if (combinaison[i*2] == 0)
        {//case vide avant la fin
            return 0;
        }
    }
    return 1;
}

void reduire(char combinaison[], int longueurCombinaison)
{//supprime les cases vides au milieu de chaine(décale la chaine)
    int i = 0;
    for (i = 0 ; i < longueurCombinaison-1 ; i++)
    {
        if (combinaison[2*i] == 0 && combinaison[2*i+1]==0)
        {
            combinaison[2*i] = combinaison[2*(i+1)];
            combinaison[2*i+1] = combinaison[2*(i+1)+1];
            combinaison[2*(i+1)] = 0;
            combinaison[2*(i+1)+1] = 0;
        }
    }
}

void ajouterMouvement(char combinaison[], int *longueur, char mouvement, char rotation, Cube *cubeTravail)
{//ajoute un mouvement a la combi et l'applique au cube
    int i =0;
    if ((*longueur) < NB_MVT_MAX)
    {
        switch (mouvement)
        {
        case FRONT:
            combinaison[(*longueur)*2] = 'F';
            combinaison[(*longueur)*2+1] = (rotation+48);
            for (i = 0 ; i < rotation ; i++)
            {
                *cubeTravail = frontMove(*cubeTravail);
            }
            (*longueur)++;
            break;
        case RIGHT:
            combinaison[(*longueur)*2] = 'R';
            combinaison[(*longueur)*2+1] = (rotation+48);
            for (i = 0 ; i < rotation ; i++)
            {
                *cubeTravail = rightMove(*cubeTravail);
            }
            (*longueur)++;
            break;
        case UP:
            combinaison[(*longueur)*2] = 'U';
            combinaison[(*longueur)*2+1] = (rotation+48);
            for (i = 0 ; i < rotation ; i++)
            {
                *cubeTravail = upMove(*cubeTravail);
            }
            (*longueur)++;
            break;
        case DOWN:
            combinaison[(*longueur)*2] = 'D';
            combinaison[(*longueur)*2+1] = (rotation+48);
            for (i = 0 ; i < rotation ; i++)
            {
                *cubeTravail = downMove(*cubeTravail);
            }
            (*longueur)++;
            break;
        case LEFT:
            combinaison[(*longueur)*2] = 'L';
            combinaison[(*longueur)*2+1] = (rotation+48);
            for (i = 0 ; i < rotation ; i++)
            {
                *cubeTravail = leftMove(*cubeTravail);
            }
            (*longueur)++;
            break;
        case BACK:
            combinaison[(*longueur)*2] = 'B';
            combinaison[(*longueur)*2+1] = (rotation+48);
            for (i = 0 ; i < rotation ; i++)
            {
                *cubeTravail = backMove(*cubeTravail);
            }
            (*longueur)++;
            break;
        }
        combinaison[(*longueur)*2] = '\0';
    }
}

