#include "io.h"


void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
	printf("|\n");
	return;
}

void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
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
				evolue(g,gc);
				efface_grille(*g);
				affiche_grille(*g);
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
                  
				//*temps_evolution = 0;
				affiche_grille(*g);
				break;				
			}
			case 'c' :
			{ // touch "c" pour (de)activer bord-cyclique
				if (compte_voisins_vivants == compte_voisins_vivants_c){
					compte_voisins_vivants = compte_voisins_vivants_nc;
					printf("Bord est maintenant non-cyclique");
				}
                else{
					compte_voisins_vivants = compte_voisins_vivants_c;
					printf("Bord est maintenant cyclique");
				}
                break;
			}
			case 'v' :
			{ // touche "v" pour activer vieillissement
				vieillissement += 1;
				vieillissement %= 2;
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
