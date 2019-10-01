#include "alea.h"

int alea (int m){
	return rand() % (m+1) ;
}

void remplir (int m){
	int i = 0;
	while (i<t.taille) {t.valeurs[i++] = alea(m);} 
}
