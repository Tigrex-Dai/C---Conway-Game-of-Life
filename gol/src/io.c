/**
 * @file io.c
 * @author DAI Yuquan
 */

#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include <string.h>
#include <stdlib.h>
#include <X11/XKBlib.h>
#include "io.h"
#include "grille.h"

// variables globales qui permettent de travailler avec l'ecran graphique
/** @brief l'ecran graphique */
Display *DPY;
/** @brief liason avec l'ecran graphique par cairo */
cairo_surface_t *CS;
/** @brief la masque avec laquelle on affiche tout */
cairo_t *CR;

cairo_surface_t *image_B;
cairo_t *image_dc_B;

/**
 * @brief initialise l'ecran graphique
 */
void init_surface() {
    Window rootwin;
    Window win;
    int scr;

    // X11 display
    if(!(DPY=XOpenDisplay(NULL))) {
        fprintf(stderr, "ERROR: Could not open display\n");
        exit(1);
    }

    scr=DefaultScreen(DPY);
    rootwin=RootWindow(DPY, scr);

    win=XCreateSimpleWindow(DPY, rootwin, 1, 1, SIZEX, SIZEY, 0, BlackPixel(DPY, scr), BlackPixel(DPY, scr));

    XStoreName(DPY, win, "Jeu de la vie");
    XSelectInput(DPY, win, ExposureMask|KeyPressMask|ButtonPressMask);
    XMapWindow(DPY, win);

    // create cairo surface
    CS = cairo_xlib_surface_create(DPY, win, DefaultVisual(DPY, 0), SIZEX, SIZEY);
    CR = cairo_create(CS);
    oscplate = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 0, 0);
	oscplate_dc = cairo_create (oscplate);

	
    cairo_set_font_size(CR, 20);
    cairo_select_font_face(CR, "Georgia", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
}

/**
 * @brief affiche un string sur l'ecran graphique
 * @param x coordone x
 * @param y coordone y
 * @param text le string qui sera afiche
 */
void affiche_cairo_text (int x, int y, char *text){
    cairo_set_source_rgb(CR, 1, 0.847, 0.42);
    cairo_move_to(CR, x, y);
    cairo_show_text(CR, text);
}

/**
 * @brief desine une ligne sur l'ecran graphique
 * @param x1 coordonne x du premier point
 * @param y1 coordonne y du premier point
 * @param x2 coordonne x du second point
 * @param y2 coordonne x du second point
 */
void dessine_cairo_ligne (int x1, int y1, int x2, int y2){
    cairo_set_source_rgb(CR, 0.4, 0.7, 1);
    cairo_move_to(CR, x1, y1);
    cairo_line_to(CR, x2, y2);
    cairo_set_line_width (CR, 5);
    cairo_stroke (CR);
}

/**
 * @brief affiche une cellule de la grille
 * @param x coordonne x du point de debut de l'affichage
 * @param y coordonne y du point de debut de l'affichage
 * @param val valeur de la cellule
 * @param vieillissement si true, on montre l'ages des cellules et non si false
 */
void affiche_cellule(int x, int y, int val,int vieillissement){
	char symbol[10];
	static char age[10];
	sprintf(age, "%d",val);
	if(vieillissement==1){
		switch(val){
			case 0:
				strcpy(symbol, " ");
				break;
			case -1:
				strcpy(symbol, "X");
				break;
			default:
                strcpy(symbol, age);
		 		break;
		}
	}
	else{
		switch(val){
			case 0:
				strcpy(symbol, " ");
				break;
			case -1:
				strcpy(symbol, "X");
				break;
			default:
               	strcpy(symbol, "O");
		 		break;
		}
	}
    affiche_cairo_text(x, y, symbol);
}

/**
 * @brief affiche une ligne de la grille sur l'ecran graphique
 * @param x nombre d'elements de la ligne
 * @param y nombre de la ligne
 * @param ligne une ligne de la grille
 * @param vieillissement si true, on montre l'ages des cellules et non si false
 */
void affiche_ligne (int x, int y, int* ligne,int vieillissement){
	int i, j=0;
	for (i=0; i<x; i++){
        affiche_cellule(i * 50 + 50, y, ligne[i],vieillissement);
        j++;
    }
}

/**
 * @brief affiche la grille
 * @param g grille
 * @param modec text pour circuler
 * @param modev text pour vieillissement
 * @param vieillissement si true, on montre l'ages des cellules et non si false
 */
void affiche_grille (grille g,char *modec,char *modev,int vieillissement){
	int i, l=g.nbl, c=g.nbc;
	char header[80];
	static char str[10];
	sprintf(str, "%d",temps_evolution);

	cairo_set_source_rgb(CR, 0, 0, 0);
	cairo_paint(CR);

	strcpy(header, "Temps d'evolution: ");
	strcat(header, str);
	affiche_cairo_text(20, 30, header);
	
	affiche_cairo_text(300, 30, modec);
	affiche_cairo_text(490, 30, modev);
	
	affiche_cairo_text(20, 680, "Instruction:");
	affiche_cairo_text(20, 710, "<clic gauche>---evoluer | <clic droite>---quitter");
	affiche_cairo_text(20, 740, "<n>---New Game | <c>---(de)activer bord-cyclique | <v>---(de)activer vieillissement");

	image_B = cairo_image_surface_create_from_png ("nice.png");
	if(cairo_surface_status(image_B)!=CAIRO_STATUS_SUCCESS){
		errx(1,"image unloaded");
	}
	image_dc_B = cairo_create(image_B);

	cairo_set_source_surface(CR, image_B, 900, 700);
	cairo_paint(CR);

	cairo_destroy(image_dc_B);
	cairo_surface_destroy(image_B);
        
	for (i=0; i<l; i++) {
		dessine_cairo_ligne(30, i * 50 + 50, c * 50 + 30, i * 50 + 50);
		affiche_ligne(c, i * 50 + 80, g.cellules[i],vieillissement);
	}
	dessine_cairo_ligne(30, i * 50 + 50, c * 50 + 30, i * 50 + 50);

	for (i=30; i<=c*50; i+=50){
		dessine_cairo_ligne(i, 50, i, l * 50 + 50);
	}
	dessine_cairo_ligne(i, 50, i, l * 50 + 50);
	
	
}



/**
 * @brief debute le jeu
 * @param g grille
 * @param gc grille
 */
void debut_jeu(grille *g, grille *gc) {
	int (*compte_voisins_vivants)(int,int,grille);
	compte_voisins_vivants=compte_voisins_vivants_c;
	int vieillissement=0;
	char *modec="Cyclique: On";
	char *modev="Vieillissement: Off";

	XEvent e;
	
	affiche_grille(*g,modec,modev,vieillissement);

	while(1){
		XNextEvent(DPY, &e);
		
		if (e.type == KeyPress){
			switch (e.xkey.keycode){
				case 54:{ // 'c'
					if (compte_voisins_vivants == compte_voisins_vivants_c){
						compte_voisins_vivants = compte_voisins_vivants_nc;
						modec="Cyclique: Off";
					}
                    else{
                        compte_voisins_vivants = compte_voisins_vivants_c;
						modec="Cyclique: On";
					}
					affiche_grille(*g,modec,modev,vieillissement);
                    break;
                }
                case 55:{ // 'v'
					vieillissement += 1;
					vieillissement %= 2;
					if(vieillissement == 1){
						modev="Vieillissement: On";
					}
					else{
						modev="Vieillissement: Off";
					}
					affiche_grille(*g,modec,modev,vieillissement);
                    break;
                }
                case 57:{ // 'n'
                    char grille[100];
                    printf("\r\e[0KNouvelle grille a charger : \n");
                    scanf("%s", grille);

                    libere_grille(g);
                    libere_grille(gc);
                    libere_grille(&gs);
                    libere_grille(&gg);

                    init_grille_from_file(grille, g);
                    alloue_grille(g->nbl, g->nbc, gc);
                    alloue_grille(g->nbl, g->nbc, &gs);
                    alloue_grille(g->nbl, g->nbc, &gg);
                    copie_grille(g,&gs);
                  
                    temps_evolution = 0;
                    affiche_grille(*g,modec,modev,vieillissement);
                    break;
                }
                
            }
        }
        else if(e.type == ButtonPress){
            if (e.xbutton.button == 1){ // clique
                temps_evolution++;
            	evolue(g,gc,compte_voisins_vivants,vieillissement);
            	affiche_grille(*g,modec,modev,vieillissement);
            }
            else if(e.xbutton.button == 3){ // clique droit
                cairo_surface_destroy(CS); // destroy cairo surface
				XCloseDisplay(DPY); // close the display
                break;
            }
		}        
    }
	return;
}


/** @brief on garde le temps d'evolution ici */
int temps_evolution=0;
