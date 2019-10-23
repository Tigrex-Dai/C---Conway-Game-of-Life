#include <stdio.h>
#include <string.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"


int main (int argc, char ** argv) {
	
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>\n");
		return 1;
	}
	
	char begin[] = {"Survie du plus apte... C'est le jeu de la vie."};
	for(int i = 0;str[i]!='\0';i++)
	{
		printf("%c",begin[i]);
		fflush(stdout);
		delay(500);
	}
	delay(1500);
	printf("/n");

	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	affiche_grille(g);
	
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
