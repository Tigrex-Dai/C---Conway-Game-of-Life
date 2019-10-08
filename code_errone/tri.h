#ifndef __TRI_H__
#define __TRI_H__
#include <stdio.h>
#include "tableau.h"

extern tableau t ;

// fait remonter une bulle jusqu'à la case k
void bulle (int k) ;

// tri (décroissant) du tableau t par la méthode du tri à bulle 
void trier ();

#endif
