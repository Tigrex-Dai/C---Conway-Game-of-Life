#include "io.h"

void affiche(){
	int i;
	for (i=0; i<t.taille; i++){
		printf("%d\t",t.valeurs[i]);
	}	
	printf("\n");
}
