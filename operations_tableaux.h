#ifndef __operations_tableaux__
#define __operations_tableaux__


//Compare deux tableaux.
bool compareTab(char* tab1, char* tab2, int taille);

//Inverse un tableau.
void retourneTab(char* tab, int taille);

// Melange un tableau de taille taille.
void shuffle(char* tab, int taille, int nbEchange);

//Retourne un tableau de taille fin-deb de valeurs de deb à fin.
char* range(char deb, char fin);
#endif
