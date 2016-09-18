#ifndef __gestion__
#define __gestion__

//Initialisation des paramètres
void gestionDuJeu(sudoku* Sudoku);

//Place un chiffre si c'est possible et retourne vrai.
bool placerChiffre(sudoku* Sudoku, char chiffre);

//Renvoie le statut de la partie (False si c'est terminé.).
bool victoire(sudoku* Sudoku);

#endif
