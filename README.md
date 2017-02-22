# CubeSolver
Rubik's Cube solver program

Programme développé en 2013 dans le cadre du Projet Personnel Encadré de Terminale S/ Sciences de l'ingénieur.

Le but de ce programme est d'interfacer avec un robot manipulant un rubik's cube afin de pouvoir le résoudre automatiquement.
Le robot lui même n'a jamais dépassé le stade de modélisation, mais le logiciel est opérationnel.

Le projet nécessite les librairies SDL 1.2, SDL_image et SDL_ttf
Le makefile fourni permet une compilation sous Debian

Au lancement du programme, un cube résolu est initialement affiché. Le menu a droite permet d'interagir avec ce cube.

En cliquant sur 'Cube resolu', on réinitialise le cube à sa position d'origine.
En cliquant sur 'Deplacer le cube', on ouvre un sous menu permettant de tourner chacune des faces, ainsi qu'un bouton pour 
appliquer une combinaison aléatoire.
En cliquant sur 'Solveur/Analyse', on ouvre le sous menu permettant de résoudre le cube actuel.
  Le bouton 'Analyse' est inactif, il devrait demander le scan du cube par le robot.
  le bouton 'Solveur' permet de calculer une combinaison de mouvements permettant de résoudre le cube.
  le bouton 'Voir resultats' permet d'appliquer la combinaison calculée sur le cube virtuel.
  le bouton 'Envoyer solution' est inactif; il devrait envoyer au robot la séquence de mouvements pour résoudre le cube.
Le bouton 'Reset manuel du robot' ouvre un menu inactif, il devrait servir a commander directement le robot pour le replacer 
en position initiale.

L'algorithme utilisé pour calculer la solution est une reproduction de la méthode la plus simple utilisée par les humains 
pour résoudre le cube : elle consiste à reconstruire le cube étape par étape au moyen de permutations élémentaires.

