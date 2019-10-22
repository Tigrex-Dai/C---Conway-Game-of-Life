#include "grille.h"
void alloue_grille (int l, int c, grille* g){
	int i,j;
	g->cellules=(int **)malloc(sizeof(int*)*l);
	for (i=0;i<c;i++){
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

void libere_grille (grille* g){
	int i;
	for (i=0;i<(g->nbc);i++){
		free(g->cellules[i]);
	}
	free(g->cellules);
	g->nbl=0;
	g->nbc=0;
}

void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0;
	
	fscanf(pfile, "%d", & l);
	printf("%d\n",l);
	fscanf(pfile, "%d", & c);
	printf("%d\n",c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	printf("%d\n",vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		printf("%d\n",i);
		fscanf(pfile, "%d", & j);
		printf("%d\n",j);
		set_vivante(i,j,*g);
	}
	
	fclose (pfile);
	return;
}


void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}
