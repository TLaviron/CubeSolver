/*
CUBE SOLVER

ce programme est destiné a la résolution d'un Rubik's Cube par un robot,
dans le cadre du projet de Tle S-SI

Au dela de la résolution même, ce programme contient une interface graphique
pour permettre les controles, la gestion d'une caméra pour la capture d'image,
et la communication avec le PIC chargé de résoudre mécaniquement le cube, par liaison série.

Dernière modification par Little_Dragoon le 16/03
    -v0.01 : Affichage du cube a plat, et ca marche!
    -v0.02 : convertisseur facelets to cubies, ca compile (a tester)
    -v0.03 : convertisseur cubies -> facelets, frontMove testé
    -v0.04 : tous les mouvements de base fonctionnent correctement
*/

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <time.h>
#include <stdbool.h>

#include "constantes.h"
#include "solveur.h"
#include "image.h"
#include "menu.h"
#include "conversions.h"
#include "combinaison.h"
#include "mouvements.h"

int main ( int argc, char** argv )
{
    srand(time(NULL));
    //random number generator init

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError() );
        return EXIT_FAILURE;
    }
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    //initialise SDL_TTF
    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Impossible d'initialiser SDL_ttf : %s\n", TTF_GetError() );
        return EXIT_FAILURE;
    }
    atexit(TTF_Quit);

    SDL_WM_SetIcon(IMG_Load("cube_icone_32x32.png"), NULL);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        fprintf(stderr, "Unable to set %dx%d video: %s\n", LARGEUR_FENETRE, HAUTEUR_FENETRE, SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_WM_SetCaption("Cube Solver v1.1!", NULL);


    SDL_Surface* displayBG = SDL_CreateRGBSurface(SDL_HWSURFACE, (TAILLE_FACELET*12)+10, (TAILLE_FACELET*9)+10, 32, 0, 0, 0, 0);
    SDL_Surface *linesBGWide = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_FACELET*12+2, TAILLE_FACELET*3+2, 32, 0, 0, 0, 0);
    SDL_Surface *linesBGHigh = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_FACELET*3+2, TAILLE_FACELET*9+2, 32, 0, 0, 0, 0);
    SDL_Surface *robotStatus = NULL, *combiDisplay[6] = {NULL};
    SDL_Surface *boutons[8] = {NULL};
    SDL_Surface *boutonBG = NULL;

    boutonBG = IMG_Load("bouton.png");


    SDL_Rect posBG, posLinesWide, posLinesHigh, posBouton, posTexte, posCombi;
    posBG.x =0;
    posBG.y =0;
    posLinesHigh.x = 4+3*TAILLE_FACELET;
    posLinesHigh.y = 4;
    posLinesWide.x = 4;
    posLinesWide.y = 4+3*TAILLE_FACELET;

    TTF_Font *police = NULL;
    police = TTF_OpenFont("times.ttf", 16);
    if (police == NULL)
    {
        fprintf(stderr, "Impossible de charger la police : %s\n", TTF_GetError());
    }

    int facelets[6][9];
    cubeRempli(facelets);//obtention de la config du cube en facettes

    Cube rubiksCube;
    faceletsToCube(&rubiksCube, facelets);// conversion en cubies

    char combinaison[NB_MVT_MAX*2+1] = "Vide", combiPartielle[81] = "";

    int i = 0, j = 0, k = 0, nombreBoutons = 5, menu = 0, longueurCombi = 0, sens = -1;
    int ordre[5] = {0};

    Uint32 couleurs[9];//pour le dessin
    couleurs[RED] = SDL_MapRGB(screen->format, 255, 0, 0);
    couleurs[ORANGE] = SDL_MapRGB(screen->format, 255, 127, 0);
    couleurs[YELLOW] = SDL_MapRGB(screen->format, 255, 255, 0);
    couleurs[BLUE] = SDL_MapRGB(screen->format, 0, 0, 255);
    couleurs[GREEN] = SDL_MapRGB(screen->format, 0, 255, 0);
    couleurs[WHITE] = SDL_MapRGB(screen->format, 255, 255, 255);
    couleurs[BLACK] = SDL_MapRGB(screen->format, 0, 0, 0);
    couleurs[LT_GRAY] = SDL_MapRGB(screen->format, 195, 195, 195);
    couleurs[GRAY] = SDL_MapRGB(screen->format, 127, 127, 127);

    //pour sdl_ttf
    SDL_Color colorNoir = {0,0,0}, colorRouge = {192, 0, 0}, colorVert = {0, 192, 0}, colorGris = {195, 195, 195};

    actualiserMenu(boutons, menu, &nombreBoutons, police, colorNoir, colorGris);

    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        SDL_Delay(20);
        while (SDL_PollEvent(&event))
        {
            switch (menu)
            {
            case 0://menu principal
                switch (event.type)
                {
                case SDL_QUIT:
                    done = true;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        done = true;
                        break;

                    case SDLK_c://cube rempli
                        cubeRempli(facelets);
                        faceletsToCube(&rubiksCube, facelets);
                        break;

                    case SDLK_d:// déplacer
                        menu = 1;
                        actualiserMenu(boutons, menu, &nombreBoutons, police, colorNoir, colorGris);
                        break;

                    case SDLK_s://solveur
                        menu = 2;
                        actualiserMenu(boutons, menu, &nombreBoutons, police, colorNoir, colorGris);
                        break;

                    case SDLK_r://manuel
                        menu = 3;
                        actualiserMenu(boutons, menu, &nombreBoutons, police, colorNoir, colorGris);
                        break;

                    case SDLK_a://quitter, a parce que qwerty
                        done = true;
                        break;

                    default:
                        break;
                    }// fin de switch key

                case SDL_MOUSEBUTTONDOWN:
                    switch (numeroBouton(event, nombreBoutons))
                    {
                    case 0:
                        break;

                    case 1://cube rempli
                        cubeRempli(facelets);
                        faceletsToCube(&rubiksCube, facelets);
                        break;

                    case 2://deplacer
                        menu = 1;
                        actualiserMenu(boutons, menu, &nombreBoutons, police, colorNoir, colorGris);
                        break;

                    case 3://solver
                        menu = 2;
                        actualiserMenu(boutons, menu, &nombreBoutons, police, colorNoir, colorGris);
                        break;

                    case 4://manuel
                        menu = 3;
                        actualiserMenu(boutons, menu, &nombreBoutons, police, colorNoir, colorGris);
                        break;

                    case 5://quitter
                        done = true;
                        break;


                    default:
                        break;
                    }//fin de switch mouse

                default:
                    break;
                }//fin de switch event.type principal
                break;

            case 1://mouvements
                switch (event.type)
                {// check for messages
                    // exit if the window is closed
                case SDL_QUIT:
                    done = true;
                    break;

                    // check for keypresses
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        menu = 0;
                        actualiserMenu(boutons, menu, &nombreBoutons, police, colorNoir, colorGris);
                        break;

                    case SDLK_f:
                        rubiksCube = frontMove(rubiksCube);
                        cubeToFacelets(&rubiksCube, facelets);
                        break;

                    case SDLK_r:
                        rubiksCube = rightMove(rubiksCube);
                        cubeToFacelets(&rubiksCube, facelets);
                        break;

                    case SDLK_u:
                        rubiksCube = upMove(rubiksCube);
                        cubeToFacelets(&rubiksCube, facelets);
                        break;

                    case SDLK_b:
                        rubiksCube = backMove(rubiksCube);
                        cubeToFacelets(&rubiksCube, facelets);
                        break;

                    case SDLK_l:
                        rubiksCube = leftMove(rubiksCube);
                        cubeToFacelets(&rubiksCube, facelets);
                        break;

                    case SDLK_d:
                        rubiksCube = downMove(rubiksCube);
                        cubeToFacelets(&rubiksCube, facelets);
                        break;

                    case SDLK_q://aléatoire, q parce que qwerty
                        longueurCombi = 40;
                        scramble(&rubiksCube, combinaison, &longueurCombi, &sens, screen, couleurs);
                        cubeToFacelets(&rubiksCube, facelets);
                        break;

                    case SDLK_p:
                        menu = 0;
                        actualiserMenu(boutons, menu, &nombreBoutons, police, colorNoir, colorGris);

                    default:
                        break;
                    }//fin de switch sdlk
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    switch(numeroBouton(event, nombreBoutons))
                    {
                    case 0:
                        break;

                    case 1:
                        rubiksCube = frontMove(rubiksCube);
                        cubeToFacelets(&rubiksCube, facelets);
                        break;

                    case 2:
                        rubiksCube = rightMove(rubiksCube);
                        cubeToFacelets(&rubiksCube, facelets);
                        break;

                    case 3:
                        rubiksCube = upMove(rubiksCube);
                        cubeToFacelets(&rubiksCube, facelets);
                        break;

                    case 4:
                        rubiksCube = backMove(rubiksCube);
                        cubeToFacelets(&rubiksCube, facelets);
                        break;

                    case 5:
                        rubiksCube = leftMove(rubiksCube);
                        cubeToFacelets(&rubiksCube, facelets);
                        break;

                    case 6:
                        rubiksCube = downMove(rubiksCube);
                        cubeToFacelets(&rubiksCube, facelets);
                        break;

                    case 7:
                        longueurCombi = 40;
                        scramble(&rubiksCube, combinaison, &longueurCombi, &sens, screen, couleurs);
                        cubeToFacelets(&rubiksCube, facelets);
                        break;

                    case 8:
                        menu = 0;
                        actualiserMenu(boutons, menu, &nombreBoutons, police, colorNoir, colorGris);

                    default:
                        break;
                    }
                    break;

                default:
                    break;

                }//fin de switch event.type déplacement
                break;

            case 2://analyse et solveur
                switch (event.type)
                {
                case SDL_QUIT:
                    done = true;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        menu = 0;
                        actualiserMenu(boutons, menu, &nombreBoutons, police, colorNoir, colorGris);
                        break;

                    case SDLK_q://analyse, q parce que qwerty
                        break;

                    case SDLK_s:// solveur
                        longueurCombi = resolutionNaturelle(&rubiksCube, combinaison);
                        sens = SOLVE;
                        break;

                    case SDLK_v://voir solution
                        appliquerCombinaison(&rubiksCube, combinaison, &sens, longueurCombi, screen, couleurs);
                        cubeToFacelets(&rubiksCube, facelets);
                        break;

                    case SDLK_e://envoyer solution
                        break;

                    case SDLK_p://précédent
                        menu = 0;
                        actualiserMenu(boutons, menu, &nombreBoutons, police, colorNoir, colorGris);
                        break;

                    default:
                        break;
                    }// fin de switch key

                case SDL_MOUSEBUTTONDOWN:
                    switch (numeroBouton(event, nombreBoutons))
                    {
                    case 0:
                        break;

                    case 1://analyse
                        break;

                    case 2:// solveur
                        longueurCombi = resolutionNaturelle(&rubiksCube, combinaison);
                        sens = SOLVE;
                        break;

                    case 3://voir solution
                        appliquerCombinaison(&rubiksCube, combinaison, &sens, longueurCombi, screen, couleurs);
                        cubeToFacelets(&rubiksCube, facelets);
                        break;

                    case 4://envoyer solution
                        break;

                    case 5://précédent
                        menu = 0;
                        actualiserMenu(boutons, menu, &nombreBoutons, police, colorNoir, colorGris);
                        break;

                    default:
                        break;
                    }//fin de switch mouse

                default:
                    break;
                }// fin de switch event.type solveur
                break;

            case 3://remise manuelle du robot
                switch (event.type)
                {
                case SDL_QUIT:
                    done = true;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        menu = 0;
                        actualiserMenu(boutons, menu, &nombreBoutons, police, colorNoir, colorGris);
                        break;

                    case SDLK_KP1:// 1/4 horaire F
                        break;

                    case SDLK_KP2:// 1/4 direct F
                        break;

                    case SDLK_KP3:// 1/4 horaire R
                        break;

                    case SDLK_KP4:// 1/4 direct R
                        break;

                    case SDLK_p://précédent
                        menu = 0;
                        actualiserMenu(boutons, menu, &nombreBoutons, police, colorNoir, colorGris);
                        break;

                    default:
                        break;
                    }// fin de switch key

                case SDL_MOUSEBUTTONDOWN:
                    switch (numeroBouton(event, nombreBoutons))
                    {
                    case 0:
                        break;

                    case 1:// 1/4 horaire F
                        break;

                    case 2:// 1/4 direct F
                        break;

                    case 3:// 1/4 horaire R
                        break;

                    case 4:// 1/4 direct R
                        break;

                    case 5://précédent
                        menu = 0;
                        actualiserMenu(boutons, menu, &nombreBoutons, police, colorNoir, colorGris);
                        break;

                    default:
                        break;
                    }//fin de switch mouse

                default:
                    break;
                }
                break;

            default:
                break;
            }//fin de switch menu

        } // end of message processing

        // DRAWING STARTS HERE
        {
            // clear screen
            SDL_FillRect(screen, 0, couleurs[LT_GRAY]);
            SDL_FillRect(displayBG, 0, couleurs[WHITE]);
            SDL_FillRect(linesBGHigh, 0, couleurs[BLACK]);
            SDL_FillRect(linesBGWide, 0, couleurs[BLACK]);

            SDL_BlitSurface(displayBG, 0, screen, &posBG);
            SDL_BlitSurface(linesBGHigh, 0, screen, &posLinesHigh);
            SDL_BlitSurface(linesBGWide, 0, screen, &posLinesWide);

            posBouton.x = (TAILLE_FACELET * 12 + 20);
            for (i = 0 ; i < nombreBoutons ; i ++)
            {//draw buttons
                posBouton.y = (HAUTEUR_BOUTON + ESPACE_BOUTON)*i + ESPACE_BOUTON;
                posTexte.x = posBouton.x + boutonBG->w/2 - boutons[i]->w/2;
                posTexte.y = posBouton.y + boutonBG->h/2 - boutons[i]->h/2;

                SDL_BlitSurface(boutonBG, NULL, screen, &posBouton);
                SDL_BlitSurface(boutons[i], NULL, screen, &posTexte);
            }

            //draw combi
            if (sens == SOLVE)
            {
                sprintf(combiPartielle, "Longueur de la combinaison : %d mouvements ; solve", longueurCombi);
            }
            else if (sens == CREATE)
            {
                sprintf(combiPartielle, "Longueur de la combinaison : %d mouvements ; generate", longueurCombi);
            }
            else
            {
                sprintf(combiPartielle, "Longueur de la combinaison : %d mouvements", longueurCombi);
            }
            for (i = 0 ; i <= 5 ; i++)
            {//libération des anciennes surfaces
                if (combiDisplay != NULL)
                {
                    SDL_FreeSurface(combiDisplay[i]);
                    combiDisplay[i]=NULL;
                }
            }
            combiDisplay[0] = TTF_RenderText_Shaded(police, combiPartielle, colorNoir, colorGris);
            for (i = 1 ; i <= 5 ; i++)
            {
                if (40*i <= longueurCombi)
                {
                    for (j = 0 ; j < 80 ; j ++)
                    {
                        combiPartielle[j] = combinaison[80*(i-1)+j];
                    }
                    combiPartielle[80] = '\0';
                }
                else if (40*i - longueurCombi < 40)
                {
                    for (j = 0 ; j < ((longueurCombi-(i-1)*40)*2); j++)
                    {
                        combiPartielle[j] = combinaison[80*(i-1)+j];
                    }
                    combiPartielle[(longueurCombi-(i-1)*40)*2] = '\0';
                }
                else
                {
                    combiPartielle[0] = '\0';
                }
                combiDisplay[i] = TTF_RenderText_Shaded(police, combiPartielle, colorNoir, colorGris);
            }
            posCombi.x = 10;
            for (i = 0 ; i <= 5 ; i++)
            {
                posCombi.y = displayBG->h + 7 +21*i;
                SDL_BlitSurface(combiDisplay[i], NULL, screen, &posCombi);
            }
            blitFacelets(screen, facelets, couleurs);
        }
        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop

    // free loaded surfaces
    for (i = 0 ; i < 8 ; i++)
    {
        SDL_FreeSurface(boutons[i]);
    }
    for (i = 0 ; i<5 ; i++)
    {
        SDL_FreeSurface(combiDisplay[i]);
    }
    SDL_FreeSurface(boutonBG);
    SDL_FreeSurface(robotStatus);
    SDL_FreeSurface(linesBGHigh);
    SDL_FreeSurface(linesBGWide);
    SDL_FreeSurface(displayBG);
    TTF_CloseFont(police);

    // all is well ;)
    printf("Exited cleanly\n");
    return EXIT_SUCCESS;
}
