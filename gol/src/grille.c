/**
 * @file grille.c
 * @author DAI Yuquan
 */
 
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h> 
 
#include "grille.h"

/**
 * @brief alloue une grille de taille l*c, et initialise toutes les cellules a mortes
 * @param l nombre de lignes
 * @param c nombre de colonnes
 * @param g grille
 */
void alloue_grille (int l, int c, grille* g){
	int i,j;
	g->cellules=(int **)malloc(sizeof(int*)*l);
	for (i=0;i<l;i++){
		g->cellules[i]=(int *)malloc(sizeof(int)*c);
	}
	g->nbl=l;
	g->nbc=c;
	for (i=0;i<l;i++){
		for (j=0;j<c;j++){
			g->cellules[i][j]=0;
		}
	}
}

/**
 * @brief permet de liberer la memoire allouee pour les cellules
 * @param g grille
 */
void libere_grille (grille *g) { 
	int i;
	for(i=(g->nbl-1);i>=0;i--){
		free(g->cellules[i]);
	}
	free(g->cellules);
	g->nbl=0;
	g->nbc=0;
}

/**
 * @brief init_grille_from_file alloue et initalise la grille g a partir d'un fichier
 * @param filename nom du fichier a ouvrir
 * @param g grille
 */
void init_grille_from_file(char const*const filename, grille *g) {
	FILE *pfile = fopen(filename, "r");
	if (pfile == NULL) {
		fprintf(stderr,"Erreur (%s:%d): Lecture du fichier \"%s\" impossible (%s)\n", __FILE__, __LINE__ - 4, filename, strerror(errno));
		exit(EXIT_FAILURE);
	}

	int i,j,n,l,c,vivantes,nonvias=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
	
	fscanf(pfile, "%d", & nonvias);
	for (n=0; n< nonvias; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_nonvia(i,j,*g);
	}

	fclose(pfile);
	return;
}

/**
 * @brief copie_grille recopie gs dans gd
 * @param gs grille
 * @param gd grille
 */
void copie_grille (grille *gs, grille *gd){
	assert(gs->nbl == gd->nbl && gs->nbc == gd->nbc);
	int i, j;
	for (i=0; i<gs->nbl; ++i) for (j=0; j<gs->nbc; ++j) gd->cellules[i][j] = gs->cellules[i][j];
}

/**
 * @brief meme_grille test si gs et gd soit meme
 * @param gs grille
 * @param gd grille
 * @return test true ou false
 */
bool meme_grille(grille *gs, grille *gd){
	assert(gs->nbl == gd->nbl && gs->nbc == gd->nbc);
	bool test = 1;
	for (int i = 0; i < gs->nbl; ++i){
		for (int j = 0; j < gs->nbc; ++j){
			if(est_vivante(i,j,*gd)!=est_vivante(i,j,*gs)){
				test = 0;
			}
		}
		if(test==0){
			break;
		}
	}
	return test;
}

/** @brief On definie global gs,gg ici */
grille gs,gg;

extern inline int est_vivante(int i, int j, grille g);
extern inline int est_nonvia(int i, int j, grille g);
extern inline void set_vivante(int i, int j, grille g);
extern inline void set_nonvia(int i, int j, grille g);
extern inline void set_morte(int i, int j, grille g);

