#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define TAILLEINITIALE 100


typedef struct Tableau {

	int* elt;       // Le tableau d�entiers (d'�l�ments) !
	int size;       // La taille de ce tableau d�entiers.
	int eltsCount;  // Le nombre d��l�ments dans le tableau !
} TABLEAU;


TABLEAU newArray() {							/***   QUESTION 1   ***/

	TABLEAU elt;
	elt.size = TAILLEINITIALE;                        // On initialise la taille initiale de elt.
	elt.elt = (int*)malloc(elt.size * sizeof(int));   // On alloue la m�moire n�cessaire via un "malloc"!
	if (elt.elt == NULL) return elt;                  // On v�rifie que la m�moire s'est bien allou�e...
	for (int i = 0; i < elt.size; i++) {              // On initialise � 0 chaque valeur du tableau.
		*(elt.elt + i) = 0;
	}
	elt.eltsCount = 0;                // eltScount = 0 
	return elt;
}


int incrementArraySize(TABLEAU* tab, int incrementValue) {				/***   QUESTION 2   ***/

	if (((*tab).elt == NULL) || (incrementValue <= 0)) return -1;							// On v�rifie que tout est valide pour faire l'incr�mentation.
	int* tmp = (*tab).elt;                                                                  // Cr�ation d'un pointeur temporaire au cas o� la m�moire n'est pas allou�e...
	(*tab).elt = (int*)realloc((*tab).elt, ((*tab).size + incrementValue) * sizeof(int));   // On alloue la nouvelle m�moire via un "realloc"!
	if ((*tab).elt == NULL) {                                                               // On v�rifie que la m�moire est bien allou�e...
		(*tab).elt = tmp;
		return -1;
	}
	for (int i = (*tab).size; i < ((*tab).size + incrementValue - 1) ; i++) {    // On met � 0 toutes les nouvelles valeurs.
		(*tab).elt[i] = 0;
	}
	(*tab).size += incrementValue;                                               // On augmente la taille du tableau.
	return (*tab).size;
}


int setElement(TABLEAU* tab, int pos, int element) {					/***   QUESTION 3   ***/

	if (((*tab).elt == NULL) || (pos < 1)) return 0;    // On v�rifie que tout est valide.
	if (pos - 1 < (*tab).size) {                        // Premier cas: si l'on ne d�passe pas la m�moire allou�e,
		(*tab).elt[pos - 1] = element;                  // on rentre l'�l�ment !
		return 0;
	}
	else {																 // Second cas: si l'on d�passe la m�moire allou�e, on l'augmente et
		if (incrementArraySize(tab, pos - (*tab).size) == -1) return 0;  
		(*tab).elt[pos - 1] = element;                                   // on ajoute l'�lement !
		return pos;

	}
}


int displayElements(TABLEAU* tab, int startPos, int endPos) {			/***   QUESTION 4   ***/

	int temp;
	if (((*tab).elt == NULL) || (startPos < 1) || (endPos > (*tab).size) || (endPos < 1) || (startPos > (*tab).size)) return -1;   // On v�rifie que tout est valide !
	if (startPos > endPos) {                            // Si startPos est > � endPos, on les �changes via la variable cr��e temporairement pour (temp)!
		temp = startPos;
		startPos = endPos;
		endPos = temp;
	}
	if (startPos == endPos) {                           // S'ils sont �gaux, on n'affiche qu'un seul �l�ment !
		printf("pos %d : %d\n", startPos, (*tab).elt[startPos - 1]);
		return 0;
	}
	for (int i = startPos - 1; i < endPos; i++) {       // Sinon, on affiche chaque terme entre startPos et endPos !
		printf("%d ", (*tab).elt[i]);
	}
	return 0;
}


int deleteElements(TABLEAU* tab, int startPos, int endPos) {			/***   QUESTION 5   ***/

	int* tmp;				// Cr�ation d'un pointeur pour enregistrer le tableau !
	int temp;				// Cr�ation d'une variable pour �changer startPos et endPos si besoin...
	if (((*tab).elt == NULL) || (startPos < 1) || (endPos > (*tab).size)) return -1;    // On v�rifie que tout est valide.
	if (startPos > endPos) {        // On �change les variables si startPos > endPos !
		temp = startPos;
		startPos = endPos;
		endPos = temp;
	}
	if (startPos == endPos) {      // On supprime un seul et unique �l�ment, et on d�cale tous les �l�ments apr�s celui supprim� vers la gauche !
		for (int i = startPos - 1; i < (*tab).size - 1 ; i++) {
			(*tab).elt[i] = (*tab).elt[i + 1];
		}
		tmp = (*tab).elt;
		(*tab).elt = (int*)realloc((*tab).elt, ((*tab).size - 1) * sizeof(int));    // On enm�ve un seul espace m�moire puisque l'on supprime un seul �l�ment.
		if ((*tab).elt == NULL) {    // On v�rifie l'allocation la m�moire.
			(*tab).elt = tmp;
			return -1;
		}
		return (*tab).size;
	}
	for (int i = startPos - 1; i < (*tab).size - (endPos - startPos + 1); i++) {    // Cas ou on supprime plusieurs �l�ments!
		(*tab).elt[i] = (*tab).elt[i + endPos - startPos + 1];						// On d�cale tout ce qu'il y a apr�s endPos vers startPos (d�calage de "n" vers la gauche) !
	}
	tmp = (*tab).elt;
	(*tab).elt = (int*)realloc((*tab).elt, ((*tab).size - (endPos - startPos + 1)) * sizeof(int));     // On r�alloue la m�moire.
	if ((*tab).elt == NULL) {		// On v�rifie l'allocation la m�moire.
		return -1;
	}
	return (*tab).size;
}



int main() {							/***   QUESTION 6   ***/
	TABLEAU tab = newArray();
	setElement(&tab, 1, 1);			 // Pour le test: on met un �l�ment en position 1 et position 90, 
	setElement(&tab, 90, 90);	     // on affiche, puis on supprime les positions entre 2 et 89 
	displayElements(&tab, 1, 100);	 // pour voir si le "deleteElements" fonctionne !

	deleteElements(&tab, 2, 89);
	printf("\n\n");
	displayElements(&tab, 1, 5);
	printf("\n\n");

	return EXIT_SUCCESS;

}