/**
 * @file io.c
 * @author DAI Yuquan
 */

#include "io.h"

/**
 * @brief dessine une ligne de trait de cellules sur l'ecran
 * @param c nombres de cellules
 */
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

/**
 * @brief dessine une ligne de cellules sur l'ecran
 * @param c nombres de cellules
 * @param ligne nombres de lignes
 * @param vieillissement si true, on montre l'ages des cellules et non si false
 */
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

/**
 * @brief affiche la grille
 * @param g grille
 * @param vieillissement si true, on montre l'ages des cellules et non si false
 */
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
	printf("Enter---Evoluer | <q>---quitter\n");
	printf("<n>---New Game | <c>---(de)activer bord-cyclique | <v>---(de)activer vieillissement\n");
	printf("Entrez un des ces instructions----");
	return;
}

/**
 * @brief efface la grille
 * @param g grille
 */
void efface_grille (grille g){
	//printf("\n\e[%dA",g.nbl*2 + 5); 
	printf("\033[2J");
}

/**
 * @brief debute le jeu
 * @param g grille
 * @param gc grille
 */
void debut_jeu(grille *g, grille *gc){
	int (*compte_voisins_vivants)(int,int,grille);
	compte_voisins_vivants=compte_voisins_vivants_c;
	
	int vieillissement = 0;
	
	int c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				temps_evolution++;
				evolue(g,gc,compte_voisins_vivants,vieillissement);
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
					//printf("\nBord est maintenant non-cyclique\n");
				}
                else{
					compte_voisins_vivants = compte_voisins_vivants_c;
					//printf("\nBord est maintenant cyclique\n");
				}
                break;
			}
			case 'v' :
			{ // touche "v" pour (de)activer vieillissement
				vieillissement += 1;
				vieillissement %= 2;
				efface_grille (*g);
				affiche_grille (*g,vieillissement);
				break;
			}
			default : 
			{ // touche non traitée
				//printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}

/** @brief on garde le temps d'evolution ici */
int temps_evolution=0;
