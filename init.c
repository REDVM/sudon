#include "main.h"




void init(sudoku* Sudoku){
	
	Sudoku->difficulte = INTERMEDIAIRE;
	Sudoku->afficherErreurs = False;
	Sudoku->modeSolveur = False;
	Sudoku->messageActuel = "";
	
	
	
	
	init_grille(Sudoku);

	posActu = 0;
	

	
}
void init_grille(sudoku* Sudoku){
	
	Sudoku->messageActuel = "";
	Sudoku->statut = True;
	
	
	int i;
	
	
	if (Sudoku->modeSolveur){
		for (i=0; i<TAILLE*TAILLE ; i++){
			gUser[i] = VIDE;
		}
		gestionDuJeu(Sudoku);
		return;
	}
	
	Sudoku->nbCoupsOrdinateur = 0;
	for (i=0; i<TAILLE*TAILLE ; i++)
		Sudoku->grilleComplete[i] = VIDE;
	
	
	
	creer_grille(Sudoku->grilleComplete, 0);
	
	for (i=0; i<TAILLE*TAILLE ; i++){
		gUser[i] = Sudoku->grilleComplete[i];  //On recopie la grille complete dans l'autre.

	}
	
	


	retrait_grille(Sudoku);

/*
	int somme = 0;
	i=0;
	do{
		retrait_grille(Sudoku);
		i++;
	} while (i<1000);
	
	g_print("\n\n%d\n\n", Sudoku->nbCoupsOrdinateur/1000);
	
*/
	g_print("\n%d\n", Sudoku->nbCoupsOrdinateur);
	
	
	
	Sudoku->nbCoupsTotal = Sudoku->nbCoupsOrdinateur;
	
	
}


