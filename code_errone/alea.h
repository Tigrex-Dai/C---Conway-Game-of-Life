#ifndef __ALEA_H__
#define __ALEA_H__
#include <stdlib.h>
#include "tableau.h"

extern tableau t ;

// tire un entier aléatoire entre 0 et m
int alea (int m);

// remplit t avec des valeurs aléatoires
void remplir (int m);

#endif
