#include <stdio.h>
#include <stdlib.h> 
#include "tableau.h"
#include "io.h"
#include "alea.h"
#include "tri.h"

tableau t; // tableau d'entiers avec sa taille

int main (int argc, char ** argv)
{
	if (argc < 3 ){ 
		printf("usage : main <nb elems> <max val>\n");
		return 1;
	}
	
	t.taille = atoi (argv[1]); // lecture du 1er argument
	int m = atoi (argv[2]); // lecture du 2eme argument
	
	t.valeurs = 0; // initialisation du pointeur
	t.valeurs = (int*) malloc (t.taille*sizeof(int)); // allocation du tableau

	remplir (m); // remplissage aléatoire du tableau

	printf("tableau non trié :\n");
	affiche();

	trier();

	printf("tableau trié :\n");
	affiche();
	
	return 0;	
}
