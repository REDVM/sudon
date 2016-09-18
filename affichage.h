#ifndef __affichage__
#define __affichage__


void affichageFenetre(sudoku* Sudoku);

//Fenetre de chargement.
void run_chargement(GtkBuilder* build);

//Quand on quitte la fenetre de chargement.
void quit_chargement(GtkBuilder* build);

//Quand on veut afficher quelque chose dans labarre d'etat.
void pushStatusBar(GtkBuilder* build, char* txt);
#endif
