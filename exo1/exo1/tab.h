#include <stdio.h>
#include <stdlib.h>


int initTab(int*, int);
// Permet d'initialiser un nombre donn� de valeurs d'un tableau � 0!
int afficheTab(int*, int, int);
// Permet d'afficher un certain nombre de valeur se trouvant dans un tableau donn� de taille donn�.
int* ajoutElementDansTableau(int*, int*, int*, int);
// Permet d'ajouter un �l�ment � la suite de notre tableau : s'il manque de la place, alors on en cr�e! 