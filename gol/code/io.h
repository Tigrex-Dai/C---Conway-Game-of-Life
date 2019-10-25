#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include "grille.h"
#include "jeu.h"

// affichage d'un trait horizontal
void affiche_trait (int c);

// affichage d'une ligne de la grille
void affiche_ligne (int c, int* ligne, int vieillissement);

// affichage d'une grille
void affiche_grille (grille g,int vieillissement);

// effacement d'une grille
void efface_grille (grille g);

// debute le jeu
void debut_jeu(grille *g, grille *gc);

// garde le temps d'exécution
extern int temps_evolution;



#endif
