/**
 * @file   grille.h
 * @author DAI Yuquan
 * @brief  Fichier entête du code source grille.c
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
/**
 * @brief structure grille: le type principal du jeu, qui contient informations sur le tableau de cellules
 */
typedef struct {
	int nbl;/**< nombre de lignes */
	int nbc; /**< nombre de colonnes */
	int** cellules;/**< tableau de tableau de cellules */
	} grille;

// alloue une grille de taille l*c, et initialise toutes les cellules à mortes
void alloue_grille (int l, int c, grille* g);

// libère une grille
void libere_grille (grille* g);

// alloue et initalise la grille g à partir d'un fichier
void init_grille_from_file (char * filename, grille* g);

// rend vivante la cellule (i,j) de la grille g
inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}
// rend non-viable la cellule (i,j) de la grille g
inline void set_nonvia(int i, int j, grille g){g.cellules[i][j] = -1;}
// rend morte la cellule (i,j) de la grille g
inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}
// teste si la cellule (i,j) de la grille g est vivante
inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] >= 1;}
// teste si la cellule (i,j) de la grille g est 
inline int est_nonvia(int i, int j, grille g){return g.cellules[i][j] == -1;}

// recopie gs dans gd (sans allocation)
void copie_grille (grille gs, grille gd);

#endif
