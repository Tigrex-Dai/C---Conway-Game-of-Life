/**
 * @file   io.h
 * @author DAI Yuquan
 * @brief  Fichier entête du code source io.c
 */

#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include "grille.h"
#include "jeu.h"

// tailles de l'ecran graphique
/** largeur de l'ecran graphique */
#define SIZEX 1000
/** longeur de l'ecran graphique */
#define SIZEY 800

// variables globales qui permettent de travailler avec l'ecran graphique
/** @brief l'ecran graphique */
Display *DPY;
/** @brief liason avec l'ecran graphique par cairo */
cairo_surface_t *CS;
/** @brief la masque avec laquelle on affiche tout */
cairo_t *CR;

// initialise l'ecran graphique du jeu
void init_surface();

// affichage d'une ligne de la grille
void affiche_ligne (int x, int y, int* ligne,int vieillissement);

// affichage d'une grille
void affiche_grille (grille g,char *modec,char *modev,int vieillissement);

// affichage un text utilisant cairo
void affiche_cairo_text (int x, int y, char *text);

//affichage une partie de grille (ligne) utilisant cairo
void dessine_cairo_ligne (int x1, int y1, int x2, int y2);

//affichage une partie de grille (cellule) utilisant cairo
void affiche_cellule(int x, int y, int val,int vieillissement);

//teste d'oscillance
void affiche_osc (grille *g, grille *gc);

// debute le jeu
void debut_jeu(grille *g, grille *gc);

// garde le temps d'exécution
extern int temps_evolution;



#endif
