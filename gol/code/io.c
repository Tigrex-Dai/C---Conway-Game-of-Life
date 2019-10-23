#include "io.h"


void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne, int vieillissement){
	int i;
	if (vieillissement)
	{
		 for (i=0; i<c; ++i) 
			if (ligne[i] == 0 ) printf ("|   "); else printf ("| %d ",ligne[i]);
		 printf("|\n");
	}
	else
	{
		for (i=0; i<c; ++i) 
			if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
		printf("|\n");
	}
	return;
}

void affiche_grille (grille g, int vieillissement){
	int i, l=g.nbl, c=g.nbc;
	printf("Temps d'evolution : %d", temps_evolution);
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i],vieillissement);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}

void debut_jeu(grille *g, grille *gc){
	int (*compte_voisins_vivants)(int,int,grille);
	compte_voisins_vivants=compte_voisins_vivants_c;
	
	int vieillissement = 0;
	
	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				temps_evolution++;
				evolue(g,gc,compte_voisins_vivants);
				efface_grille(*g);
				affiche_grille(*g,vieillissement);
				break;
			}
			case 'n' :
			{ // touche "n" pour renouveller grille
				char grille[100];
                printf("\r\e[0KNouvelle grille a charger : \n");
                scanf("%s", grille);

				libere_grille(g);
				libere_grille(gc);

				init_grille_from_file(grille, g);
				alloue_grille(g->nbl, g->nbc, gc);
                  
				temps_evolution = 0;
				affiche_grille(*g,vieillissement);
				break;				
			}
			case 'c' :
			{ // touch "c" pour (de)activer bord-cyclique
				if (compte_voisins_vivants == compte_voisins_vivants_c){
					compte_voisins_vivants = compte_voisins_vivants_nc;
					printf("\nBord est maintenant non-cyclique\n");
				}
                else{
					compte_voisins_vivants = compte_voisins_vivants_c;
					printf("\nBord est maintenant cyclique\n");
				}
                break;
			}
			case 'v' :
			{ // touche "v" pour activer vieillissement
				vieillissement += 1;
				vieillissement %= 2;
				efface_grille (*g);
				affiche_grille (*g,vieillissement);
				break;
			}
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}

int temps_evolution=0;
