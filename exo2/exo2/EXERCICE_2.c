#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define TAILLEINITIALE 100


typedef struct Tableau {
	int* elt; // le tableau d’entiers
	int size; // la taille de ce tableau d’entiers
	int eltsCount; // le nombre d’éléments dans le tableau
} TABLEAU;

TABLEAU newArray() {
	TABLEAU tab;
	tab.size = TAILLEINITIALE;     //on initialise la taille
	tab.elt = (int*)malloc(tab.size * sizeof(int));   //on alloue la mémoire nécessaire
	if (tab.elt == NULL) return tab;   //on vérifie que la mémoire s'est bien allouée
	for (int i = 0; i < tab.size; i++) {   //on initialise à 0 le tableau
		*(tab.elt + i) = 0;
	}
	tab.eltsCount = 0;
	return tab;
}

int incrementArraySize(TABLEAU* tab, int incrementValue) {
	if (((*tab).elt == NULL) || (incrementValue <= 0)) return -1;   //on vérifie que tout est valide pour faire l'incrémentation
	int* tmp = (*tab).elt;     //vatiable temporaire au cas ou la mémoire n'est pas allouée
	(*tab).elt = (int*)realloc((*tab).elt, ((*tab).size + incrementValue) * sizeof(int)); //on alloue la nouvelle mémoire
	if ((*tab).elt == NULL) { //on vérifie que la mémoire est bien allouée
		(*tab).elt = tmp;
		return -1;
	}
	for (int i = (*tab).size; i < (*tab).size + incrementValue - 1; i++) {  //on met à 0 toutes les nouvelles valeurs
		(*tab).elt[i] = 0;
	}
	(*tab).size += incrementValue;  //on augmente la taille du tableau
	return (*tab).size;
}

int setElement(TABLEAU* tab, int pos, int element) {
	if (((*tab).elt == NULL) || (pos < 1)) return 0;  //on vérifie que tout est valide
	if (pos - 1 < (*tab).size) {    //premier cas si on ne dépasse pas la mémoire allouée
		(*tab).elt[pos - 1] = element;  //on incruste l'élement
		return 0;
	}
	else {

		if (incrementArraySize(tab, pos - (*tab).size) == -1) return 0;  //si on dépasse la mémoire, on l'augmente
		(*tab).elt[pos - 1] = element;  //on ajoute l'élement
		return pos;

	}
}

int displayElements(TABLEAU* tab, int startPos, int endPos) {
	int temp;
	if (((*tab).elt == NULL) || (startPos < 1) || (endPos > (*tab).size) || (endPos < 1) || (startPos > (*tab).size)) return -1; //on vérifie que tout est valide
	if (startPos > endPos) {  //si start est > à end, on les échanges
		temp = startPos;
		startPos = endPos;
		endPos = temp;
	}
	if (startPos == endPos) { //s'ils sont égaux, on ne display qu'un élément
		printf("pos %d : %d\n", startPos, (*tab).elt[startPos - 1]);
		return 0;
	}
	for (int i = startPos - 1; i < endPos; i++) {  //sinon on display tout entre start et end
		printf("%d ", (*tab).elt[i]);
	}
	return 0;
}

int deleteElements(TABLEAU* tab, int startPos, int endPos) {
	int* tmp; //variable pour enregistrer le tableau
	int temp; //variable pour échanger start et end
	if (((*tab).elt == NULL) || (startPos < 1) || (endPos > (*tab).size)) return -1; //on vérifie que tout est valide
	if (startPos > endPos) { //échange si start > end
		temp = startPos;
		startPos = endPos;
		endPos = temp;
	}
	if (startPos == endPos) {  //on supprime un seul élément, et on décale tout les éléments après celui supprimé vers la gauche
		for (int i = startPos - 1; i < (*tab).size - 1; i++) {
			(*tab).elt[i] = (*tab).elt[i + 1];
		}
		tmp = (*tab).elt;
		(*tab).elt = (int*)realloc((*tab).elt, ((*tab).size - 1) * sizeof(int)); // on enmève 1 mémoire comme on supprime 1 élément
		if ((*tab).elt == NULL) { //on vérifie que la mémoire s'est bien réallouée
			(*tab).elt = tmp;
			return -1;
		}
		return (*tab).size;
	}
	for (int i = startPos - 1; i < (*tab).size - (endPos - startPos + 1); i++) {  // cas ou on supprime plusieurs éléments
		(*tab).elt[i] = (*tab).elt[i + endPos - startPos + 1]; //on décale tout ce qu'il y a après end vers start (décalage de "n" vers la gauche)
	}
	tmp = (*tab).elt;
	(*tab).elt = (int*)realloc((*tab).elt, ((*tab).size - (endPos - startPos + 1)) * sizeof(int)); //on réalloue la mémoire 
	if ((*tab).elt == NULL) { //on vérifie qu'on a bien alloué
		(*tab).elt = tmp;
		return -1;
	}
	return (*tab).size;
}



int main() {
	TABLEAU tab = newArray();
	setElement(&tab, 1, 1);     //test: on met un élément en pos 1 et pos 4, on display, puis on supprime la pos 2 et 3 pour voir si le delete fonctionne
	setElement(&tab, 4, 4);
	displayElements(&tab, 1, 4);
	deleteElements(&tab, 2, 3);
	printf("\n");
	displayElements(&tab, 1, 4);

	return EXIT_SUCCESS;

}