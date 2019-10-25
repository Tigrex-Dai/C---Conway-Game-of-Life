/**
 * @file main.c
 * @author DAI Yuquan
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"

/**
 * @brief execute le jeu
 * @param argv repertoire du fichier avec la grille
 * @return 0 si l'utilisateur a appuye sur 'q'
 */

int main (int argc, char ** argv) {
	
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>\n");
		return 1;
	}
	int usleep(useconds_t usec);
	
	char begin[] = {"Survie du plus apte... C'est le jeu de la vie."};
	for(int i = 0;begin[i]!='\0';i++)
	{
		printf("%c",begin[i]);
		fflush(stdout);
		usleep(50000);
	}
	usleep(150000);
	printf("\n");

	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	affiche_grille(g,0);
	
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
