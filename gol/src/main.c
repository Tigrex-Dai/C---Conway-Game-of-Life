/**
 * @file main.c
 * @author DAI Yuquan
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include "grille.h"
#include "io.h"
#include "jeu.h"


/**
 * @brief alloue quelques grilles avant executer le corp du jeu et les libere apres finir
 * @param fichier nom du fichier avec la grille
 */
void joue (char *fichier){

	grille g, gc;

	init_surface();
     
	init_grille_from_file(fichier, &g);
	alloue_grille (g.nbl, g.nbc, &gc);
	alloue_grille (g.nbl, g.nbc, &gs);
	alloue_grille (g.nbl, g.nbc, &gg);
	copie_grille(&g,&gs);
	
	debut_jeu(&g, &gc);
	libere_grille(&g);
	libere_grille(&gc);
	libere_grille(&gs);
	libere_grille(&gg);
	return;
}

/**
 * @brief prepare et execute le jeu
 * @param argv repertoire du fichier avec la grille
 * @return 1 si l'utilisateur n'a pas entre un fichier correcte,
           0 si l'utilisateur fait un clic droite
 */
int main(int argc, char **argv) {
    if (argc != 2 )
	{
		printf("usage : main <fichier grille>\n");
		return 1;
	}

	char *fichier;
	fichier = argv[1];
	
	int usleep(useconds_t usec);
	char begin[] = {"Survie du plus apte... C'est le jeu de la vie."};
	for(int i = 0;begin[i]!='\0';i++)
	{
		printf("%c",begin[i]);
		fflush(stdout);
		usleep(50000);
	}
	usleep(300000);
	printf("\n");
	joue (fichier);

    return 0;
}
