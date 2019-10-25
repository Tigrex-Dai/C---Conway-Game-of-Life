/**
 * @file grille.c
 * @author DAI Yuquan
 */
 
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
void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
	
	fclose (pfile);
	return;
}

/**
 * @brief copie_grille recopie gs dans gd
 * @param gs grille
 * @param gd grille
 */
void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}

extern inline int est_vivante(int i, int j, grille g);
extern inline void set_vivante(int i, int j, grille g);
extern inline void set_morte(int i, int j, grille g);
