#ifndef __gen_grille__
#define __gen_grille__

//Remplis la grille.
bool creer_grille(char* grille, char position);

//Selectionne les cases à afficher de la grille.
void retrait_grille(sudoku* Sudoku);



//Critere 1 : on enlève le chiffre si c'est la seule position possible.
bool ret_candidatSeul(sudoku* Sudoku, char position);

//Critere 2 : On peut enlever un chiffre dans un carré si toutes les autres cases vides du carré ont cette valeur dans sa colonne ou ligne.
bool ret_candidatUnique(sudoku* Sudoku, char position, char valeur);

//Critere 3 : On regarde s'il y a plusieurs solutions pour la grille. Si oui, on remet la valeur a la case.
bool ret_bruteforce(char* grille, char position, char sens);


#endif
