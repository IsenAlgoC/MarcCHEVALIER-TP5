#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define TAILLEINITIALE 100


typedef struct Tableau {

	int* elt;       // Le tableau d’entiers (d'éléments) !
	int size;       // La taille de ce tableau d’entiers.
	int eltsCount;  // Le nombre d’éléments dans le tableau !
} TABLEAU;


TABLEAU newArray() {							/***   QUESTION 1   ***/

	TABLEAU elt;
	elt.size = TAILLEINITIALE;                        // On initialise la taille initiale de elt.
	elt.elt = (int*)malloc(elt.size * sizeof(int));   // On alloue la mémoire nécessaire via un "malloc"!
	if (elt.elt == NULL) return elt;                  // On vérifie que la mémoire s'est bien allouée...
	for (int i = 0; i < elt.size; i++) {              // On initialise à 0 chaque valeur du tableau.
		*(elt.elt + i) = 0;
	}
	elt.eltsCount = 0;                // eltScount = 0 
	return elt;
}


int incrementArraySize(TABLEAU* tab, int incrementValue) {				/***   QUESTION 2   ***/

	if (((*tab).elt == NULL) || (incrementValue <= 0)) return -1;							// On vérifie que tout est valide pour faire l'incrémentation.
	int* tmp = (*tab).elt;                                                                  // Création d'un pointeur temporaire au cas où la mémoire n'est pas allouée...
	(*tab).elt = (int*)realloc((*tab).elt, ((*tab).size + incrementValue) * sizeof(int));   // On alloue la nouvelle mémoire via un "realloc"!
	if ((*tab).elt == NULL) {                                                               // On vérifie que la mémoire est bien allouée...
		(*tab).elt = tmp;
		return -1;
	}
	for (int i = (*tab).size; i < ((*tab).size + incrementValue - 1) ; i++) {    // On met à 0 toutes les nouvelles valeurs.
		(*tab).elt[i] = 0;
	}
	(*tab).size += incrementValue;                                               // On augmente la taille du tableau.
	return (*tab).size;
}


int setElement(TABLEAU* tab, int pos, int element) {					/***   QUESTION 3   ***/

	if (((*tab).elt == NULL) || (pos < 1)) return 0;    // On vérifie que tout est valide.
	if (pos - 1 < (*tab).size) {                        // Premier cas: si l'on ne dépasse pas la mémoire allouée,
		(*tab).elt[pos - 1] = element;                  // on rentre l'élément !
		return 0;
	}
	else {																 // Second cas: si l'on dépasse la mémoire allouée, on l'augmente et
		if (incrementArraySize(tab, pos - (*tab).size) == -1) return 0;  
		(*tab).elt[pos - 1] = element;                                   // on ajoute l'élement !
		return pos;

	}
}


int displayElements(TABLEAU* tab, int startPos, int endPos) {			/***   QUESTION 4   ***/

	int temp;
	if (((*tab).elt == NULL) || (startPos < 1) || (endPos > (*tab).size) || (endPos < 1) || (startPos > (*tab).size)) return -1;   // On vérifie que tout est valide !
	if (startPos > endPos) {                            // Si startPos est > à endPos, on les échanges via la variable créée temporairement pour (temp)!
		temp = startPos;
		startPos = endPos;
		endPos = temp;
	}
	if (startPos == endPos) {                           // S'ils sont égaux, on n'affiche qu'un seul élément !
		printf("pos %d : %d\n", startPos, (*tab).elt[startPos - 1]);
		return 0;
	}
	for (int i = startPos - 1; i < endPos; i++) {       // Sinon, on affiche chaque terme entre startPos et endPos !
		printf("%d ", (*tab).elt[i]);
	}
	return 0;
}


int deleteElements(TABLEAU* tab, int startPos, int endPos) {			/***   QUESTION 5   ***/

	int* tmp;				// Création d'un pointeur pour enregistrer le tableau !
	int temp;				// Création d'une variable pour échanger startPos et endPos si besoin...
	if (((*tab).elt == NULL) || (startPos < 1) || (endPos > (*tab).size)) return -1;    // On vérifie que tout est valide.
	if (startPos > endPos) {        // On échange les variables si startPos > endPos !
		temp = startPos;
		startPos = endPos;
		endPos = temp;
	}
	if (startPos == endPos) {      // On supprime un seul et unique élément, et on décale tous les éléments après celui supprimé vers la gauche !
		for (int i = startPos - 1; i < (*tab).size - 1 ; i++) {
			(*tab).elt[i] = (*tab).elt[i + 1];
		}
		tmp = (*tab).elt;
		(*tab).elt = (int*)realloc((*tab).elt, ((*tab).size - 1) * sizeof(int));    // On enmève un seul espace mémoire puisque l'on supprime un seul élément.
		if ((*tab).elt == NULL) {    // On vérifie l'allocation la mémoire.
			(*tab).elt = tmp;
			return -1;
		}
		return (*tab).size;
	}
	for (int i = startPos - 1; i < (*tab).size - (endPos - startPos + 1); i++) {    // Cas ou on supprime plusieurs éléments!
		(*tab).elt[i] = (*tab).elt[i + endPos - startPos + 1];						// On décale tout ce qu'il y a après endPos vers startPos (décalage de "n" vers la gauche) !
	}
	tmp = (*tab).elt;
	(*tab).elt = (int*)realloc((*tab).elt, ((*tab).size - (endPos - startPos + 1)) * sizeof(int));     // On réalloue la mémoire.
	if ((*tab).elt == NULL) {		// On vérifie l'allocation la mémoire.
		return -1;
	}
	return (*tab).size;
}



int main() {							/***   QUESTION 6   ***/
	TABLEAU tab = newArray();
	setElement(&tab, 1, 1);			 // Pour le test: on met un élément en position 1 et position 90, 
	setElement(&tab, 90, 90);	     // on affiche, puis on supprime les positions entre 2 et 89 
	displayElements(&tab, 1, 100);	 // pour voir si le "deleteElements" fonctionne !

	deleteElements(&tab, 2, 89);
	printf("\n\n");
	displayElements(&tab, 1, 5);
	printf("\n\n");

	return EXIT_SUCCESS;

}