#ifndef MENU
#define MENU

int numeroBouton(SDL_Event event, int nbBoutons);

void actualiserMenu(SDL_Surface *boutons[], int nouveauMenu, int *nombreBoutons, TTF_Font *police, SDL_Color foreGround, SDL_Color backGround);

#endif // MENU

