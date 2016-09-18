#ifndef __structures__
#define __structures__


#define TAILLE 9
#define VIDE 0

#define FACILE  		 30
#define INTERMEDIAIRE	 40
#define DIFFICILE        45
#define DIABOLIQUE 		 55


#define posActu Sudoku->positionSelectionnee
#define gUser ((Sudoku->modeSolveur) ? Sudoku->grilleUserSolveurMode : Sudoku->grilleUser)


typedef char bool;
enum {False, True};


typedef struct{
	char position;
	char valeur;
} coup;


typedef struct{
	char grilleComplete[TAILLE*TAILLE];
	char grilleUser[TAILLE*TAILLE];
	char grilleUserSolveurMode[TAILLE*TAILLE];
	
	coup listeCoups[TAILLE*TAILLE*1000];
	int nbCoupsTotal;
	int nbCoupsOrdinateur;
	char difficulte;
	char positionSelectionnee;
	
	char* messageActuel;
	bool statut;
	bool afficherErreurs;  //Preference.
	bool modeSolveur;
	GtkBuilder* build;
} sudoku;


#endif
