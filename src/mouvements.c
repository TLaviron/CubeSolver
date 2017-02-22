#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "constantes.h"
#include "mouvements.h"
#include "combinaison.h"
#include "conversions.h"


Cube frontMove(Cube cubeATourner)
{
    /* application d'un mouvement simple au cube envoyé,
    renvoie un cube ayant subi le mouvement*/
    Cube cubeFinal= copie(cubeATourner);
    //conversion position arètes
    cubeFinal.edge[UF].c = cubeATourner.edge[FL].c;
    cubeFinal.edge[FR].c = cubeATourner.edge[UF].c;
    cubeFinal.edge[DF].c = cubeATourner.edge[FR].c;
    cubeFinal.edge[FL].c = cubeATourner.edge[DF].c;

    //conversion orientations arètes
    cubeFinal.edge[UF].o = (cubeATourner.edge[FL].o + 1)%2;
    cubeFinal.edge[FR].o = (cubeATourner.edge[UF].o + 1)%2;
    cubeFinal.edge[DF].o = (cubeATourner.edge[FR].o + 1)%2;
    cubeFinal.edge[FL].o = (cubeATourner.edge[DF].o + 1)%2;

    //conversion position coins
    cubeFinal.corner[URF].c = cubeATourner.corner[UFL].c;
    cubeFinal.corner[DFR].c = cubeATourner.corner[URF].c;
    cubeFinal.corner[DLF].c = cubeATourner.corner[DFR].c;
    cubeFinal.corner[UFL].c = cubeATourner.corner[DLF].c;

    //conversion orientations coins
    cubeFinal.corner[URF].o = (cubeATourner.corner[UFL].o + 1)%3;
    cubeFinal.corner[DFR].o = (cubeATourner.corner[URF].o + 2)%3;
    cubeFinal.corner[DLF].o = (cubeATourner.corner[DFR].o + 1)%3;
    cubeFinal.corner[UFL].o = (cubeATourner.corner[DLF].o + 2)%3;

    return cubeFinal;
}

Cube upMove(Cube cubeATourner)
{
    Cube cubeFinal= copie(cubeATourner);

    //modification des positions des 4 coins
    cubeFinal.corner[URF].c = cubeATourner.corner[UBR].c;
    cubeFinal.corner[UFL].c = cubeATourner.corner[URF].c;
    cubeFinal.corner[ULB].c = cubeATourner.corner[UFL].c;
    cubeFinal.corner[UBR].c = cubeATourner.corner[ULB].c;

    //modification des positions des 4 arêtes
    cubeFinal.edge[UF].c = cubeATourner.edge[UR].c;
    cubeFinal.edge[UL].c = cubeATourner.edge[UF].c;
    cubeFinal.edge[UB].c = cubeATourner.edge[UL].c;
    cubeFinal.edge[UR].c = cubeATourner.edge[UB].c;

    cubeFinal.corner[URF].o = cubeATourner.corner[UBR].o;
    cubeFinal.corner[UFL].o = cubeATourner.corner[URF].o;
    cubeFinal.corner[ULB].o = cubeATourner.corner[UFL].o;
    cubeFinal.corner[UBR].o = cubeATourner.corner[ULB].o;

    //modification des orientations des 4 arêtes
    cubeFinal.edge[UF].o = cubeATourner.edge[UR].o;
    cubeFinal.edge[UL].o = cubeATourner.edge[UF].o;
    cubeFinal.edge[UB].o = cubeATourner.edge[UL].o;
    cubeFinal.edge[UR].o = cubeATourner.edge[UB].o;

    return cubeFinal;
}

Cube rightMove(Cube cubeATourner)
{
    Cube cubeFinal= copie(cubeATourner);

    cubeFinal.corner[URF].c = cubeATourner.corner[DFR].c;
    cubeFinal.corner[UBR].c = cubeATourner.corner[URF].c;
    cubeFinal.corner[DRB].c = cubeATourner.corner[UBR].c;
    cubeFinal.corner[DFR].c = cubeATourner.corner[DRB].c;

    cubeFinal.corner[URF].o = (cubeATourner.corner[DFR].o+2)%3;
    cubeFinal.corner[UBR].o = (cubeATourner.corner[URF].o+1)%3;
    cubeFinal.corner[DRB].o = (cubeATourner.corner[UBR].o+2)%3;
    cubeFinal.corner[DFR].o = (cubeATourner.corner[DRB].o+1)%3;

    cubeFinal.edge[UR].c = cubeATourner.edge[FR].c;
    cubeFinal.edge[RB].c = cubeATourner.edge[UR].c;
    cubeFinal.edge[DR].c = cubeATourner.edge[RB].c;
    cubeFinal.edge[FR].c = cubeATourner.edge[DR].c;

    cubeFinal.edge[UR].o = cubeATourner.edge[FR].o;
    cubeFinal.edge[RB].o = cubeATourner.edge[UR].o;
    cubeFinal.edge[DR].o = cubeATourner.edge[RB].o;
    cubeFinal.edge[FR].o = cubeATourner.edge[DR].o;

    return cubeFinal;
}

Cube backMove(Cube cubeATourner)
{
    Cube cubeFinal= copie(cubeATourner);
    //conversion position arètes
    cubeFinal.edge[UB].c = cubeATourner.edge[RB].c;
    cubeFinal.edge[LB].c = cubeATourner.edge[UB].c;
    cubeFinal.edge[DB].c = cubeATourner.edge[LB].c;
    cubeFinal.edge[RB].c = cubeATourner.edge[DB].c;

    //conversion orientations arètes
    cubeFinal.edge[UB].o = (cubeATourner.edge[RB].o + 1)%2;
    cubeFinal.edge[LB].o = (cubeATourner.edge[UB].o + 1)%2;
    cubeFinal.edge[DB].o = (cubeATourner.edge[LB].o + 1)%2;
    cubeFinal.edge[RB].o = (cubeATourner.edge[DB].o + 1)%2;

    //conversion position coins
    cubeFinal.corner[ULB].c = cubeATourner.corner[UBR].c;
    cubeFinal.corner[DBL].c = cubeATourner.corner[ULB].c;
    cubeFinal.corner[DRB].c = cubeATourner.corner[DBL].c;
    cubeFinal.corner[UBR].c = cubeATourner.corner[DRB].c;

    //conversion orientations coins
    cubeFinal.corner[ULB].o = (cubeATourner.corner[UBR].o + 1)%3;
    cubeFinal.corner[DBL].o = (cubeATourner.corner[ULB].o + 2)%3;
    cubeFinal.corner[DRB].o = (cubeATourner.corner[DBL].o + 1)%3;
    cubeFinal.corner[UBR].o = (cubeATourner.corner[DRB].o + 2)%3;

    return cubeFinal;
}

Cube downMove(Cube cubeATourner)
{
    Cube cubeFinal= copie(cubeATourner);

    //modification des positions des 4 coins
    cubeFinal.corner[DFR].c = cubeATourner.corner[DLF].c;
    cubeFinal.corner[DLF].c = cubeATourner.corner[DBL].c;
    cubeFinal.corner[DBL].c = cubeATourner.corner[DRB].c;
    cubeFinal.corner[DRB].c = cubeATourner.corner[DFR].c;

    //modification des positions des 4 arêtes
    cubeFinal.edge[DF].c = cubeATourner.edge[DL].c;
    cubeFinal.edge[DL].c = cubeATourner.edge[DB].c;
    cubeFinal.edge[DB].c = cubeATourner.edge[DR].c;
    cubeFinal.edge[DR].c = cubeATourner.edge[DF].c;

    cubeFinal.corner[DFR].o = cubeATourner.corner[DLF].o;
    cubeFinal.corner[DLF].o = cubeATourner.corner[DBL].o;
    cubeFinal.corner[DBL].o = cubeATourner.corner[DRB].o;
    cubeFinal.corner[DRB].o = cubeATourner.corner[DFR].o;

    //modification des positions des 4 arêtes
    cubeFinal.edge[DF].o = cubeATourner.edge[DL].o;
    cubeFinal.edge[DL].o = cubeATourner.edge[DB].o;
    cubeFinal.edge[DB].o = cubeATourner.edge[DR].o;
    cubeFinal.edge[DR].o = cubeATourner.edge[DF].o;

    return cubeFinal;
}

Cube leftMove(Cube cubeATourner)
{
    Cube cubeFinal= copie(cubeATourner);

    cubeFinal.corner[UFL].c = cubeATourner.corner[ULB].c;
    cubeFinal.corner[DLF].c = cubeATourner.corner[UFL].c;
    cubeFinal.corner[DBL].c = cubeATourner.corner[DLF].c;
    cubeFinal.corner[ULB].c = cubeATourner.corner[DBL].c;

    cubeFinal.corner[UFL].o = (cubeATourner.corner[ULB].o+1)%3;
    cubeFinal.corner[DLF].o = (cubeATourner.corner[UFL].o+2)%3;
    cubeFinal.corner[DBL].o = (cubeATourner.corner[DLF].o+1)%3;
    cubeFinal.corner[ULB].o = (cubeATourner.corner[DBL].o+2)%3;

    cubeFinal.edge[UL].c = cubeATourner.edge[LB].c;
    cubeFinal.edge[FL].c = cubeATourner.edge[UL].c;
    cubeFinal.edge[DL].c = cubeATourner.edge[FL].c;
    cubeFinal.edge[LB].c = cubeATourner.edge[DL].c;

    cubeFinal.edge[UL].o = cubeATourner.edge[LB].o;
    cubeFinal.edge[FL].o = cubeATourner.edge[UL].o;
    cubeFinal.edge[DL].o = cubeATourner.edge[FL].o;
    cubeFinal.edge[LB].o = cubeATourner.edge[DL].o;

    return cubeFinal;
}

Cube copie(Cube cubeACopier)
{
    /* renvoie une copie du cube donné en paramètre*/
    Cube cubeFinal;
    int i=0;
    //copie du cube en l'état
    for ( i =0 ; i < 8 ; i ++)
    {//coins
        cubeFinal.corner[i].c = cubeACopier.corner[i].c;
        cubeFinal.corner[i].o = cubeACopier.corner[i].o;
    }
    for ( i = 0 ; i < 12 ; i ++)
    {//aretes
        cubeFinal.edge[i].c = cubeACopier.edge[i].c;
        cubeFinal.edge[i].o = cubeACopier.edge[i].o;
    }
    return cubeFinal;
}

void scramble(Cube *cubeAMelanger, char combinaison[], int *longueurCombi, int *sens, SDL_Surface *screen, Uint32 couleurs[])
{
    /* génère une combinaison aléatoire pour mélanger le cube*/
    int i = 0, j = 0, face = 0, rotation = 0, taille = *longueurCombi;
    for (i = 0 ; i < taille ; i++)
    {
        face = rand()%6;
        rotation = ((rand()%3)+1);
        switch (face)
        {
        case FRONT:
            combinaison[i*2] = 'F';
            break;

        case LEFT:
            combinaison[i*2] = 'L';
            break;

        case RIGHT:
            combinaison[i*2] = 'R';
            break;

        case UP:
            combinaison[i*2] = 'U';
            break;

        case DOWN:
            combinaison[i*2] = 'D';
            break;

        case BACK:
            combinaison[i*2] = 'B';
            break;

        default:
            break;

        }
        switch (rotation)
        {
        case 1:
            combinaison[i*2+1] = '1';
            break;

        case 2:
            combinaison[i*2+1] = '2';
            break;

        case 3:
            combinaison[i*2+1] = '3';
            break;

        default:
            combinaison[i*2+1] = '0';
            break;
        }
    }
    combinaison[taille*2] = '\0';

    *longueurCombi = lissage(combinaison, *longueurCombi);

    *sens = CREATE;
    appliquerCombinaison(cubeAMelanger, combinaison, sens, *longueurCombi, screen, couleurs);

}

void appliquerCombinaison(Cube *rubiksCube, char combinaison[], int *sens, int longueurCombi, SDL_Surface *screen, Uint32 couleurs[])
{
    /* applique une combinaison générée ou calculée au cube fourni.
    prends en argument le cube a transformer, la combinaison a appliquer, le sens, sa longueur, et l'écran et couleurs pour l'afficher en cours*/
    int i = 0, j = 0;
    int facelets[6][9] = {0};
    char face = 0, rotation = 0;
    Uint32 tempsActuel = 0;

    facelets[0][4] = RED;
    facelets[1][4] = WHITE;
    facelets[2][4] = ORANGE;
    facelets[3][4] = YELLOW;
    facelets[4][4] = GREEN;
    facelets[5][4] = BLUE;

    if (*sens == SOLVE)
    {
        for (i = 0 ; i < longueurCombi ; i++)
        {
            tempsActuel = SDL_GetTicks();
            face = combinaison[2*i];
            rotation = (combinaison[(2*i)+1]-48);
            for (j = 0 ; j < rotation ; j++)
            {
                switch (face)
                {
                case 'F':
                    *rubiksCube = frontMove(*rubiksCube);
                    break;
                case 'R':
                    *rubiksCube = rightMove(*rubiksCube);
                    break;
                case 'U':
                    *rubiksCube = upMove(*rubiksCube);
                    break;
                case 'D':
                    *rubiksCube = downMove(*rubiksCube);
                    break;
                case 'L':
                    *rubiksCube = leftMove(*rubiksCube);
                    break;
                case 'B':
                    *rubiksCube = backMove(*rubiksCube);
                    break;
                }
                cubeToFacelets(rubiksCube, facelets);
                blitFacelets(screen, facelets, couleurs);
                if (SDL_GetTicks() - tempsActuel < TEMPS_COMBI)
                {
                    SDL_Delay(TEMPS_COMBI + tempsActuel - SDL_GetTicks());
                }
            }

        }
        *sens = CREATE;
    }
    else if (*sens == CREATE)
    {
        for (i = 0 ; i < longueurCombi ; i++)
        {
            tempsActuel = SDL_GetTicks();
            face = combinaison[2*(longueurCombi-(i+1))];
            rotation = 4-(combinaison[2*(longueurCombi-(i+1))+1]-48);
            for (j = 0 ; j < rotation ; j++)
            {
                switch (face)
                {
                case 'F':
                    *rubiksCube = frontMove(*rubiksCube);
                    break;
                case 'R':
                    *rubiksCube = rightMove(*rubiksCube);
                    break;
                case 'U':
                    *rubiksCube = upMove(*rubiksCube);
                    break;
                case 'D':
                    *rubiksCube = downMove(*rubiksCube);
                    break;
                case 'L':
                    *rubiksCube = leftMove(*rubiksCube);
                    break;
                case 'B':
                    *rubiksCube = backMove(*rubiksCube);
                    break;
                }
                cubeToFacelets(rubiksCube, facelets);
                blitFacelets(screen, facelets, couleurs);
                if (SDL_GetTicks() - tempsActuel < TEMPS_COMBI)
                {
                    SDL_Delay(TEMPS_COMBI + tempsActuel - SDL_GetTicks());
                }
            }
        }
        *sens = SOLVE;
    }

}

void blitFacelets(SDL_Surface *screen, int facelets[][9], Uint32 couleurs[])
{
    /* fonction premettant d'afficher les facettes d'un cube donné*/
    SDL_Surface* faceletSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_FACELET-2, TAILLE_FACELET-2, 32, 0, 0, 0, 0);
    SDL_Rect posFacelet;
    int i = 0 , j = 0, k = 0, blitDir = 0;

    for( i =0 ; i<6 ; i++)
    {//draw facelets
        switch (i)
        {
            case LEFT:
                posFacelet.x = 6;
                posFacelet.y = 6+3*TAILLE_FACELET;
                blitDir = 1;
                break;

            case DOWN:
                posFacelet.x = 6+3*TAILLE_FACELET;
                posFacelet.y = 6+8*TAILLE_FACELET;
                blitDir = 2;
                break;

            case RIGHT:
                posFacelet.x = 6+8*TAILLE_FACELET;
                posFacelet.y = 6+5*TAILLE_FACELET;
                blitDir = 3;
                break;

            case UP:
                posFacelet.x = 6+5*TAILLE_FACELET;
                posFacelet.y = 6;
                blitDir = 4;
                break;

            case FRONT:
                posFacelet.x = 6+5*TAILLE_FACELET;
                posFacelet.y = 6+5*TAILLE_FACELET;
                blitDir = 3;
                break;

            case BACK:
                posFacelet.x = 6+9*TAILLE_FACELET;
                posFacelet.y = 6+3*TAILLE_FACELET;
                blitDir = 1;
                break;
        }
        for( j =0 ; j<3 ; j++)
        {//tout ceci est bien merdique
            for(k = 0 ; k<3 ; k++)
            {//mais ca marche!
                SDL_FillRect(faceletSurface, 0, couleurs[facelets[i][(j*3+k)]]);
                SDL_BlitSurface(faceletSurface, 0, screen, &posFacelet);
                posFacelet.x += TAILLE_FACELET * (blitDir%2)*(2-blitDir);
                posFacelet.y += TAILLE_FACELET * ((blitDir-1)%2) * (blitDir-3);
            }
            posFacelet.x += TAILLE_FACELET * ((blitDir-1)%2)*(3-blitDir) - 3*TAILLE_FACELET * (blitDir%2)*(2-blitDir);
            posFacelet.y += TAILLE_FACELET * (blitDir%2)*(2-blitDir) - 3*TAILLE_FACELET * ((blitDir-1)%2) * (blitDir-3);
        }
    }
    SDL_Flip(screen);
    SDL_FreeSurface(faceletSurface);
}

void fonctionUseless(int argument1, double argument2)
{
    fprintf(stdout, "Bonjouuuuuur!\n");
}
