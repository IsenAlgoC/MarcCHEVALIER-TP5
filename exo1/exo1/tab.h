#include <stdio.h>
#include <stdlib.h>


int initTab(int*, int);
// Permet d'initialiser un nombre donné de valeurs d'un tableau à 0!
int afficheTab(int*, int, int);
// Permet d'afficher un certain nombre de valeur se trouvant dans un tableau donné de taille donné.
int* ajoutElementDansTableau(int*, int*, int*, int);
// Permet d'ajouter un élément à la suite de notre tableau : s'il manque de la place, alors on en crée! 