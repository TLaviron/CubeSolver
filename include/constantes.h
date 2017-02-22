/* constantes.h
Dernière modif par Little_Dragoon
    -définition de taile fenêtre
    -définition de la taille max de la combi

définit des constantes communes a tout le programme

*/

#ifndef CONSTANTES
#define CONSTANTES

    #define LARGEUR_FENETRE     800
    #define HAUTEUR_FENETRE     600
    #define NB_MVT_MAX          200
    #define TAILLE_FACELET      50
    #define LARGEUR_BOUTON      130
    #define HAUTEUR_BOUTON      44
    #define ESPACE_BOUTON       12
    #define TEMPS_COMBI         100// en ms


    enum {LEFT, DOWN, RIGHT, UP, FRONT, BACK};//directions
    enum {RED, ORANGE, YELLOW, BLUE, GREEN, WHITE, BLACK, LT_GRAY, GRAY};//couleurs (cube pour les 6 premières, dessin pour le reste)
    enum {URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB};//coins
    enum {UF, UL, UB, UR, DF, DL, DB, DR, FR, FL, LB, RB};//aretes
    enum {SOLVE, CREATE};//sens d'application de combi



#endif
