#ifndef __callbacks__
#define __callbacks__

//Actualisation du canvas.
void fill_canvas(GtkWidget* canvas, GdkEventExpose* event, sudoku* Sudoku);

//Lorsque l'on quitte la fenetre principale.
void quit_fen(GtkWidget* w);

//Lorsque que l'on survol le canvas avec la souris.
void survol_canvas(GtkWidget* canvas, GdkEventMotion* event, sudoku* Sudoku);

//Lorsque l'on appuie sur une touche du clavier;
void on_key_press(GtkWidget* w, GdkEventKey* event, sudoku* Sudoku);

//Quand on clique sur une case du canvas + mollette.
void click_canvas(GtkWidget* w, GdkEvent* event, sudoku* Sudoku);

//Quand on provoque une nouvelle partie.
void cb_newPartie(GtkWidget* w, sudoku* Sudoku);

//Quand on veut changer la difficulté.
void cb_changeDifficulte(GtkWidget* w, sudoku* Sudoku);

//Quand on ouvre la fenetre a propos.
void run_apropos(GtkWidget* w, GtkBuilder* build);

//Quand on change l'affichage.
void cb_changeAffichage(GtkWidget* w, sudoku* Sudoku);

//Dévoile une case
void cb_afficheChiffre(GtkWidget* w, sudoku* Sudoku);

//Corrige tout !
void cb_correction(GtkWidget* w, sudoku* Sudoku);

//Vide le solveur.
void cb_vider(GtkWidget* w, sudoku* Sudoku);

//Resoudre la grille entrée par l'utilisateur.
void cb_resoudre(GtkWidget* w, sudoku* Sudoku);
#endif
