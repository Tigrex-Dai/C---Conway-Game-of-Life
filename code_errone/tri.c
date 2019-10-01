#include "tri.h"

void bulle (int k) {
	int i=0;
	for (i=0 ; i<=k ; i++) { 
		if (t.valeurs[i+1] > t.valeurs[i]){ // echange de t[i] et t[i+1]
			int tmp = t.valeurs[i+1];
			t.valeurs[i+1] = t.valeurs[i];
			t.valeurs[i] = tmp;
		}
	}
}

void trier (){
	int i=0 ;
	for (i=t.taille-1 ; i>=0 ; i--) {
		bulle (i);
	}
}
