#include "main.h"





bool compareTab(char* tab1, char* tab2, int taille){
	int i;
	for (i=0; i<taille; i++){
		if (tab1[i] != tab2[i])
			return False;
	}
	return True;
}

void retourneTab(char* tab, int taille){
	int i, j=taille-1, tmp;
	for (i=0; i<taille/2; i++){
		tmp = tab[i];
		tab[i] = tab[j];
		tab[j] = tmp;
		j--;
	}
}


char* range(char deb, char fin){
	char* tab = malloc(sizeof(char)*(fin-deb));
	for(; deb<fin; deb++)
		tab[deb] = deb;
	return tab;
	
}


void shuffle(char* tab, int taille, int nbEchange){
	
	int i, tmp;
	int indice1, indice2;

	for(i=0 ; i<nbEchange; i++){  //On échange nbEchange fois, deux valeurs du tableau.
		indice1 = (int)(rand() / (double)RAND_MAX * taille);
		indice2 = (int)(rand() / (double)RAND_MAX * taille);
		tmp = tab[indice1];
		tab[indice1] = tab[indice2];
		tab[indice2] = tmp;
	}
}
