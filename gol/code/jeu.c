#include "jeu.h"

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

int compte_voisins_vivants_c (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

int compte_voisins_vivants_nc(int i, int j, grille g) {
	int v = 0;
	for(int k = max(0,i-1);k <= min(g.nbl-1,i+1);k++){
		for(int l = max(0,j-1);l <= min(g.nbc-1,j+1);l++){
			if((k != i || l != j) && est_vivante(k,l,g)){
				v++;			
			}
		}
	}
  return v;
}

void evolue (grille *g, grille *gc, int (*compte_voisins_vivants)(int,int,grille),int vieillissement){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc;
	
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{			
			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				switch (vieillissement){
					case 1 : {
						if ( (compte_voisins_vivants(i,j,*gc)!=2 && compte_voisins_vivants(i,j,*gc)!= 3) || g->cellules[i][j] >=8 )
						{
							set_morte(i,j,*g);
						}
						else
						{
							g->cellules[i][j]++;		
						}
						break;
					}
					case 0 : {
						if ( compte_voisins_vivants(i,j,*gc)!=2 && compte_voisins_vivants(i,j,*gc)!= 3 )
						{
							set_morte(i,j,*g);
						}
						else
						{
							g->cellules[i][j]++;		
						}
						break;
					}
				}
			}
			else 
			{ // evolution d'une cellule morte
				if ( compte_voisins_vivants(i,j,*gc)==3 ) set_vivante(i,j,*g);
			}
		}
	}
	return;
}
