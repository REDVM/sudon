#include "main.h"


void gestionDuJeu(sudoku* Sudoku){
	
/*
	if (!Sudoku->statut)
		return;
*/
	
	pushStatusBar(Sudoku->build, Sudoku->messageActuel);
	
	gtk_widget_queue_draw(GTK_WIDGET(gtk_builder_get_object(Sudoku->build, Sudoku->modeSolveur ? "canvas2" : "canvas")));
	
	
	Sudoku->statut = victoire(Sudoku);
	if (!Sudoku->modeSolveur && !Sudoku->statut && !strcmp(Sudoku->messageActuel, ""))
		Sudoku->messageActuel = "Sudoku terminé ! Une autre grille ?";
		
	
	pushStatusBar(Sudoku->build, Sudoku->messageActuel);
	
	
	
/*
	
	for (i=0; i < Sudoku->nbCoupsTotal;i++){
			g_print("%d: %d.%d \n ", i, Sudoku->listeCoups[i].position, Sudoku->listeCoups[i].valeur);			
		}
	g_print("\n\n\n\n\n");
*/
   
}

bool victoire(sudoku* Sudoku){
	int i;
	for (i=0 ; i < TAILLE*TAILLE ; i++)
		if(gUser[i] != Sudoku->grilleComplete[i])
			return True;
	return False;
	
	
	
}

bool placerChiffre(sudoku* Sudoku, char chiffre){
	char i, tmp;
	coup Coup;
	Coup.position = posActu;
	Coup.valeur = chiffre;
	
	if (gUser[posActu] != chiffre){
		if(!Sudoku->modeSolveur){
			for (i=0; i < Sudoku->nbCoupsOrdinateur;i++){
				if (Sudoku->listeCoups[i].position == posActu)
					return False;				
			}
			Sudoku->listeCoups[Sudoku->nbCoupsTotal] = Coup;
			(Sudoku->nbCoupsTotal)++;
		}
		gUser[posActu] = chiffre;
		
		gestionDuJeu(Sudoku);
		return True;
		
	}
	
	
	
	return False;
}
