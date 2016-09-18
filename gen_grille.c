#include "main.h"

bool creer_grille(char* grille, char position){
	

	if (position == TAILLE * TAILLE)  //Si la grille est pleine alors le tour est joué !
			return True;
	
	char i, j=0, chiffresLegaux[9] = {VIDE};
	
	for(i=1; i <= 9; i++){  //On sauvegarde tous les chiffres possibles sur une case donnée.
		if(coupLegal(grille, position, i)){
			chiffresLegaux[j] = i;
			j++;
		}
	}

	shuffle(chiffresLegaux, j, 5);

	// Essayer les valeurs restantes jusqu'à trouver la solution
	for (i=0; i<j ; i++){

		grille[position] = chiffresLegaux[i];
		

		// Si on arrive à compléter la grille, c'est bon !
		if (creer_grille(grille, position + 1)) 
				return True;

		grille[position] = VIDE;
	}

	
	return False;
}

void retrait_grille(sudoku* Sudoku){
	char i, j = 0, indice, indice2, tmp, tmp2, casesEnlevees = 0;
	char tabPositions[(TAILLE*TAILLE)+1], chiffresLegaux[9] = {0};
	char grille1[TAILLE*TAILLE], grille2[TAILLE*TAILLE];
	
	
	
	
	
	
	
	/*Initialisation du tableau de positions tel qu'on parcourt 
	 * une position aléatoire p, puis son complémentaire 80-p, puis p', puis le complémentaire 80-p', ... */
	for (i=0 ; i < (TAILLE*TAILLE) ; i+=2){ //tabPositions := {0, 80, 1, 79, 2, 78, ..., 40, 40} (on ve parcourt pas le dernier élément.
		tabPositions[i] = j;
		tabPositions[i+1] = 80-j;
		j++;
	}
	for (i=0 ; i < 40 ; i++){ //On échange 40 fois deux couples de valeurs.
		do{  //Tant que les indices générés ne sont pas paires.
			indice = (int)(rand() / (double)RAND_MAX * ((TAILLE*TAILLE)-1));
			indice2 = (int)(rand() / (double)RAND_MAX * ((TAILLE*TAILLE)-1));
		} while ((indice%2) || (indice2%2));
		tmp =  tabPositions[indice];
		tmp2 = tabPositions[indice+1];
		tabPositions[indice] = tabPositions[indice2];
		tabPositions[indice+1] = tabPositions[indice2 + 1];
		tabPositions[indice2] = tmp;
		tabPositions[indice2+1] = tmp2;
/*
		printf("%d, %d: %d et %d  avec  %d et %d    |    %d %d\n", indice, indice2, tabPositions[indice], tabPositions[indice+1], tabPositions[indice2], tabPositions[indice2+1], indice%2, indice2%2);
*/
	}
	
	//Fin d'initialisation du tableau de position
	
	
	
	
	
	for (i=0 ; i<TAILLE*TAILLE ; i++){
		tmp = gUser[tabPositions[i]];
		gUser[tabPositions[i]] = VIDE;
		
		
		if ((ret_candidatSeul(Sudoku, tabPositions[i]) || ret_candidatUnique(Sudoku, tabPositions[i], tmp)) && casesEnlevees < Sudoku->difficulte)  //S'il y a plusieurs chiffres possibles pour cette case, on ne l'enlève pas.
			casesEnlevees++;
		else if (casesEnlevees < Sudoku->difficulte){
			
			memcpy(grille1, gUser, TAILLE*TAILLE*sizeof(char));
			memcpy(grille2, gUser, TAILLE*TAILLE*sizeof(char));
			ret_bruteforce(grille1, 0, False);
			ret_bruteforce(grille2, 0, True);
			if (compareTab(grille1, grille2, TAILLE*TAILLE))// Si les deux tableaux sont égaux => il n'y a qu'une seule solution.
				casesEnlevees++;
			else
				goto ajoutCoup;
		}
		else{
			ajoutCoup:
			gUser[tabPositions[i]] = tmp;
			Sudoku->listeCoups[Sudoku->nbCoupsOrdinateur].position = tabPositions[i];
			Sudoku->listeCoups[Sudoku->nbCoupsOrdinateur].valeur = tmp;
			(Sudoku->nbCoupsOrdinateur)++;
		}
	}
	
	
}

bool ret_candidatSeul(sudoku* Sudoku, char position){
	
	char k=0, j;
	for(j=1; j <= 9; j++){  //On compte tous les chiffres possibles sur une case donnée.
		if(coupLegal(gUser, position, j))
			k++;
	}
	return k == 1;
}


bool ret_candidatUnique(sudoku* Sudoku, char position, char valeur){
	
	char i, j, posCarre, posLigne, posColonne, presenceValeur;
	bool condCarre=True, condLigne=True, condColonne=True;
	for(i=0; i < 9; i++){  //On regarde si la valeur qui a été enlevée est un candidat unique dans les 3 zones.
	
		posCarre = (TAILLE*((position/TAILLE/3)*3+(i/3)) + ((position%TAILLE/3)*3+(i%3)));
		posLigne = TAILLE*(position/TAILLE)+i;
		posColonne = position%TAILLE+TAILLE*i;
		if (posCarre != position && gUser[posCarre] == VIDE && coupLegal(gUser, posCarre, valeur))
			condCarre = False;
			
		if (posLigne != position && gUser[posLigne] == VIDE && coupLegal(gUser, posLigne, valeur))
			condLigne = False;
			
		if (posColonne != position && gUser[posColonne] == VIDE && coupLegal(gUser, posColonne, valeur))
			condColonne = False;	
	}

	return condCarre || condLigne  || condColonne;
}


bool ret_bruteforce(char* grille, char position, char sens){
	
	if (position == TAILLE * TAILLE)  //Si la grille est pleine alors le tour est joué !
			return True;
	if(grille[position] != VIDE)
		return ret_bruteforce(grille, position+1, sens);
		
	
	char i, j=0, chiffresLegaux[9];
	
	for(i=1; i <= 9; i++){  //On sauvegarde tous les chiffres possibles sur une case donnée.
		if(coupLegal(grille, position, i)){
			chiffresLegaux[j] = i;
			j++;
		}
	}

	sens ? retourneTab(chiffresLegaux, j) : 0;
	// Essayer les valeurs restantes jusqu'à trouver la solution
	for (i=0; i<j ; i++){

		grille[position] = chiffresLegaux[i];
		

		// Si on arrive à compléter la grille, c'est bon !
		if (ret_bruteforce(grille, position + 1, sens)) 
				return True;

		
	}

	grille[position] = VIDE;
	return False;
}






