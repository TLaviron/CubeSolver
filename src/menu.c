/*menu.cpp

contient diverses fonction relatives a la gestion de l'interface

dernière modif par Little_Dragoon le 16/03
*/
#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL_ttf.h"

#include "menu.h"
#include "constantes.h"

int numeroBouton(SDL_Event event, int nbBoutons)
{
    int bouton = 0;
    if (event.button.x <(TAILLE_FACELET*12 + 20) || event.button.x > ((TAILLE_FACELET*12 + 20) + LARGEUR_BOUTON))
    {//si le clic est pas dans la colone des boutons, sortie
        return 0;
    }
    if ((event.button.y % (HAUTEUR_BOUTON + ESPACE_BOUTON)) < ESPACE_BOUTON)
    {// si le clic est entre un bouton
        return 0;
    }
    bouton = (event.button.y / (HAUTEUR_BOUTON + ESPACE_BOUTON)) + 1;
    if (bouton > nbBoutons)
    {//clic sur un bouton qui n'existe pas
        return 0;
    }
    else
    {
        return bouton;
    }
}

void actualiserMenu(SDL_Surface *boutons[], int nouveauMenu, int *nombreBoutons, TTF_Font *police, SDL_Color foreGround, SDL_Color backGround)
{
    int i = 0;
    for (i = 0 ; i < 8 ; i++)
    {//libère les anciennes surfaces avant de créer les nouvelles
        if (boutons[i]!= NULL)
        {
            SDL_FreeSurface(boutons[i]);
            boutons[i] = NULL;//réinitialisation du pointeur
        }
    }
    switch (nouveauMenu)
    {
    case 0: //menu principal
        boutons[0] = TTF_RenderText_Shaded(police, "Cube Resolu", foreGround, backGround);
        boutons[1] = TTF_RenderText_Shaded(police, "Deplacer le cube", foreGround, backGround);
        boutons[2] = TTF_RenderText_Shaded(police, "Solveur / Analyse", foreGround, backGround);
        boutons[3] = TTF_RenderText_Shaded(police, "Reset manuel du robot", foreGround, backGround);
        boutons[4] = TTF_RenderText_Shaded(police, "Quitter", foreGround, backGround);
        *nombreBoutons = 5;
        break;

    case 1: //déplacer
        boutons[0] = TTF_RenderText_Shaded(police, "Front (avant)", foreGround, backGround);
        boutons[1] = TTF_RenderText_Shaded(police, "Right (droite)", foreGround, backGround);
        boutons[2] = TTF_RenderText_Shaded(police, "Up (haut)", foreGround, backGround);
        boutons[3] = TTF_RenderText_Shaded(police, "Back (arriere)", foreGround, backGround);
        boutons[4] = TTF_RenderText_Shaded(police, "Left (gauche)", foreGround, backGround);
        boutons[5] = TTF_RenderText_Shaded(police, "Down (bas)", foreGround, backGround);
        boutons[6] = TTF_RenderText_Shaded(police, "Aleatoire", foreGround, backGround);
        boutons[7] = TTF_RenderText_Shaded(police, "Precedent", foreGround, backGround);
        *nombreBoutons = 8;
        break;

    case 2://solveur
        boutons[0] = TTF_RenderText_Shaded(police, "Analyse", foreGround, backGround);
        boutons[1] = TTF_RenderText_Shaded(police, "Solveur", foreGround, backGround);
        boutons[2] = TTF_RenderText_Shaded(police, "Voir resultats", foreGround, backGround);
        boutons[3] = TTF_RenderText_Shaded(police, "Envoyer solution", foreGround, backGround);
        boutons[4] = TTF_RenderText_Shaded(police, "Precedent", foreGround, backGround);
        *nombreBoutons = 5;
        break;

    case 3://solveur
        boutons[0] = TTF_RenderText_Shaded(police, "1 - Bras F horaire", foreGround, backGround);
        boutons[1] = TTF_RenderText_Shaded(police, "2 - Bras F direct", foreGround, backGround);
        boutons[2] = TTF_RenderText_Shaded(police, "3 - Bras R horaire", foreGround, backGround);
        boutons[3] = TTF_RenderText_Shaded(police, "4 - Bras R direct", foreGround, backGround);
        boutons[4] = TTF_RenderText_Shaded(police, "Precedent", foreGround, backGround);
        *nombreBoutons = 5;
        break;

    default:
        break;
    }
}

