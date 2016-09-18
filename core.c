#include "main.h"



bool coupLegal(char* grille, char position, char valeur){
	
	int i;
	for (i=0 ; i<TAILLE; i++){
		
		if ((grille[TAILLE*(position/TAILLE)+i] == valeur && TAILLE*(position/TAILLE)+i != position) || 
			(grille[position%TAILLE+TAILLE*i] == valeur   && position%TAILLE+TAILLE*i != position) || 
			(grille[( TAILLE*((position/TAILLE/3)*3+(i/3)) + ((position%TAILLE/3)*3+(i%3)))] == valeur && ( TAILLE*((position/TAILLE/3)*3+(i/3)) + ((position%TAILLE/3)*3+(i%3))) != position))
			return False;
			
	}
	return True;
}

