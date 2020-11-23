#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "tab.h"                 // Fichier personnel d'en-tête "tab".


#define TAILLEINITIALE 100


int main() {

	int myTab1[10];
	initTab(myTab1, 10);		// On met des 0 dans chaque case de notre tableau.
	afficheTab(myTab1, 10, 10);     // On affiche myTab2 en ligne, avec " - " entre chaque valeurs.


	printf("\n");


	int* myTab2 = NULL;
	int TAB2SIZE = TAILLEINITIALE;
	int nbElts = 30;


	myTab2 = (int*)malloc(TAILLEINITIALE * sizeof(int));

	if (myTab2 != NULL) { initTab(myTab2, TAB2SIZE); }    // On met des 0 dans chaque case de notre tableau.

	else { printf("Memoire insuffisante !"); return(-1); }

	for (int i = 0; i < nbElts; i++) {   // On remplie les nbElts premières valeurs du tableau avec des valeurs comprises entre 1 et 30!
		*(myTab2 + i) = i + 1;
	}
	myTab2 = ajoutElementDansTableau(myTab2, &TAB2SIZE, &nbElts, 50505);   // On rajoute la valeur "50505" à la suite de notre tableau de 100 caractères (on crée donc une nouvelle place dédié...)!
	afficheTab(myTab2, TAB2SIZE, nbElts);   // On affiche myTab2 en ligne, avec " - " entre chaque valeurs.


	if (myTab2 != NULL) { free(myTab2); }   // Via cette condition on évite un warning éventuel.


	return EXIT_SUCCESS;
}
