#include "main.h"



void fill_canvas(GtkWidget* canvas, GdkEventExpose* event, sudoku* Sudoku){
	
	int largeur = canvas->allocation.width, hauteur = canvas->allocation.height;
	int i, j, cellule, X, Y;
	int x, y;
	char chaine[2];
	
	if (canvas == GTK_WIDGET(gtk_builder_get_object(Sudoku->build, "canvas")))
		Sudoku->modeSolveur = False;
	else
		Sudoku->modeSolveur = True;
/*
	g_print("%d, %d  |  ", largeur, hauteur);
*/
	PangoLayout *pLayout = pango_layout_new(gdk_pango_context_get());
	PangoAttrList *attrList = pango_attr_list_new();
	
	//On va créer une couleur verte pour le fond
	GdkGC* gc = gdk_gc_new(canvas->window);	
	GdkGC* gc_fond = gdk_gc_new(canvas->window);	
	GdkGC* gc_select = gdk_gc_new(canvas->window);	
	GdkGC* gc_rouge = gdk_gc_new(canvas->window);	
	GdkGC* gc_bleuFonce = gdk_gc_new(canvas->window);
		
	GdkColormap* colormap = gdk_colormap_get_system(); //Sans ca, on a des couleurs vives aleatoires a chaque execution, ca peut etre interessant.
	GdkColor couleurFond, select, bleuFonce, rouge;
	
	gdk_color_parse("#ddd", &couleurFond);
	gdk_colormap_alloc_color (colormap, &couleurFond, FALSE, FALSE);
	gdk_gc_set_foreground (gc_fond, &couleurFond);
	
	gdk_color_parse("#0007ee", &bleuFonce);
	gdk_colormap_alloc_color (colormap, &bleuFonce, FALSE, FALSE);
	gdk_gc_set_foreground (gc_bleuFonce, &bleuFonce);
	
	gdk_color_parse("#99001d", &rouge);
	gdk_colormap_alloc_color (colormap, &rouge, FALSE, FALSE);
	gdk_gc_set_foreground (gc_rouge, &rouge);
	
	gdk_color_parse("#25ee00", &select);
	gdk_colormap_alloc_color (colormap, &select, FALSE, FALSE);
	gdk_gc_set_foreground (gc_select, &select);  
	//Fin de la couleur
	
	
	
	
	// On dessine le fond, puis les lignes
	gdk_draw_rectangle(canvas->window, gc_fond, TRUE, 0, 0, largeur, hauteur);
	
	
	for(i=0 ; i	< TAILLE; i++){
		x = (largeur*1.0/(TAILLE))*i;
		y = (hauteur*1.0/(TAILLE))*i;
		gdk_draw_line (canvas->window, canvas->style->black_gc, x, 0, x, hauteur);
		gdk_draw_line (canvas->window, canvas->style->black_gc, 0, y, largeur, y);
		if (i%3 == 0){
			gdk_draw_line (canvas->window, canvas->style->black_gc, x+1 , 0, x+1, hauteur);
			gdk_draw_line (canvas->window, canvas->style->black_gc, 0, y+1, largeur, y+1);
		}
	}
	gdk_draw_line (canvas->window, canvas->style->black_gc, largeur-1, 0, largeur-1, hauteur-1);
	gdk_draw_line (canvas->window, canvas->style->black_gc, 0, hauteur-1, largeur-1, hauteur-1);
	gdk_draw_line (canvas->window, canvas->style->black_gc, largeur-2, 0, largeur-2, hauteur-1);
	gdk_draw_line (canvas->window, canvas->style->black_gc, 0, hauteur-2, largeur-1, hauteur-2);

	
	for(i=0 ; i < TAILLE * TAILLE; i++){
		cellule = gUser[i];
		Y = (i/TAILLE);
		X = (i%TAILLE);
		
		if (i==posActu)
			gdk_draw_arc (canvas->window, gc_select, True, X*(largeur*1.0/TAILLE)+2, Y*(hauteur*1.0/TAILLE)+2, (largeur*1.0/TAILLE)-2, (largeur*1.0/TAILLE)-2, 0, 360*64);
		
		if (cellule != VIDE){
			if (!coupLegal(gUser, i, cellule) && Sudoku->afficherErreurs)
				gc = gc_rouge;
			else
				gc = gc_bleuFonce;
			if (!Sudoku->modeSolveur){
				for (j=0 ; j < Sudoku->nbCoupsOrdinateur ; j++){
						if (i == Sudoku->listeCoups[j].position){
							gc = canvas->style->black_gc;
							break;
						}
					}
				}
			
			sprintf(chaine, "%d", cellule);
			pango_layout_set_text(pLayout, chaine, 1);
			pango_attr_list_insert(attrList, pango_attr_size_new((25000/300)*largeur));
			pango_layout_set_attributes(pLayout, attrList);
			gdk_draw_layout(canvas->window, gc, X*(largeur*1.0/TAILLE) + largeur/TAILLE/4 - largeur/TAILLE/8 + largeur/TAILLE/16, Y*(hauteur*1.0/TAILLE) - largeur/TAILLE/8 + largeur/TAILLE/16, pLayout);
		}
	}
}


void survol_canvas(GtkWidget* canvas, GdkEventMotion* event, sudoku* Sudoku){
	int x = event->x, y = event->y; //On regarde les coordonnées de la souris.
	int largeur = canvas->allocation.width, hauteur = canvas->allocation.height;
	int indiceTab;
	
	
	//On traduit maintenant ces coordonnées en indice du tableau.
	indiceTab = TAILLE * ((int)(y/(largeur*1.0/(TAILLE)))) + (int)(x/(largeur*1.0/(TAILLE)));
	//~ g_print("%d ",indiceTab);
	
	if (indiceTab != posActu){
		posActu = indiceTab;
		gestionDuJeu(Sudoku);
	}
	
}



void on_key_press(GtkWidget* w, GdkEventKey* event, sudoku* Sudoku){ 

    switch (event->keyval){ 
        // Si on appuie sur une touche de raccourci :
         
        case GDK_KP_1: 
        case GDK_1: placerChiffre(Sudoku, 1);         break; 
        case GDK_KP_2: 
        case GDK_2: placerChiffre(Sudoku, 2);         break; 
        case GDK_KP_3: 
        case GDK_3: placerChiffre(Sudoku, 3);         break; 
        case GDK_KP_4: 
        case GDK_4: placerChiffre(Sudoku, 4);         break; 
        case GDK_KP_5: 
        case GDK_5: placerChiffre(Sudoku, 5);         break; 
        case GDK_KP_6: 
        case GDK_6: placerChiffre(Sudoku, 6);         break; 
        case GDK_KP_7:
        case GDK_7: placerChiffre(Sudoku, 7);         break; 
        case GDK_KP_8: 
        case GDK_8: placerChiffre(Sudoku, 8);         break; 
        case GDK_KP_9: 
        case GDK_9: placerChiffre(Sudoku, 9);         break; 
        case GDK_KP_0: 
        case GDK_0: 
        case GDK_Delete: placerChiffre(Sudoku, 0);    break; 
        case GDK_Down: posActu = (posActu + TAILLE)%(TAILLE*TAILLE);    break; 
        case GDK_Up: posActu = (posActu >= TAILLE) ? (posActu - TAILLE)%(TAILLE*TAILLE) : posActu + TAILLE*(TAILLE-1) ;    break; 
        case GDK_Right: posActu = (posActu + 1)%(TAILLE*TAILLE);    break; 
        case GDK_Left: posActu = (posActu > 0) ? (posActu - 1) : TAILLE*TAILLE -1;    break; 
        default:                                       break; 
    } 
	gestionDuJeu(Sudoku);
} 




void click_canvas(GtkWidget* w, GdkEvent* event, sudoku* Sudoku){
	
	if (!Sudoku->statut)
		return;
	
	
	if (event->button.type == GDK_BUTTON_PRESS){
		if (event->button.button == 1)
			placerChiffre(Sudoku, (gUser[posActu]+1)%(TAILLE+1));
		else if (gUser[posActu] > 0)
			placerChiffre(Sudoku, (gUser[posActu]-1)%(TAILLE+1));
		else
			placerChiffre(Sudoku, TAILLE);
	}
	
	if (event->scroll.type == GDK_SCROLL){
		if (event->scroll.direction == GDK_SCROLL_UP)
			placerChiffre(Sudoku, (gUser[posActu]+1)%(TAILLE+1));
		else if (gUser[posActu] > 0)
			placerChiffre(Sudoku, (gUser[posActu]-1)%(TAILLE+1));
		else
			placerChiffre(Sudoku, TAILLE);
		
	}
	
			
	gestionDuJeu(Sudoku);
	
}




void cb_newPartie(GtkWidget* w, sudoku* Sudoku){
	init_grille(Sudoku);
	gestionDuJeu(Sudoku);
	
}

void cb_changeDifficulte(GtkWidget* w, sudoku* Sudoku){
	
	char difficulte;
	
	GtkRadioMenuItem* radio = (GtkRadioMenuItem*) w;
	GSList* listeRadio = gtk_radio_menu_item_get_group(radio);
	int i = 0;
	while (!gtk_check_menu_item_get_active (listeRadio->data)){
		listeRadio = listeRadio->next;
		i++;
	}
	switch(i){
		case 0: difficulte = DIABOLIQUE;     break;
		case 1: difficulte = DIFFICILE;      break;
		case 2: difficulte = INTERMEDIAIRE;  break;
		case 3: difficulte = FACILE;         break;
		default:difficulte = INTERMEDIAIRE;  break;
	}
	if (difficulte != Sudoku->difficulte){
		Sudoku->difficulte = difficulte;
		cb_newPartie(w, Sudoku);
	}
}


void run_apropos(GtkWidget* w, GtkBuilder* build){
	
	gtk_widget_show_all(GTK_WIDGET(gtk_builder_get_object(build, "dialog_apropos")));
	gtk_dialog_run(GTK_DIALOG(gtk_builder_get_object(build, "dialog_apropos")));
	
	gtk_widget_hide_all(GTK_WIDGET(gtk_builder_get_object(build, "dialog_apropos")));
	
}

void cb_changeAffichage(GtkWidget* w, sudoku* Sudoku){
	Sudoku->afficherErreurs = gtk_check_menu_item_get_active((GtkCheckMenuItem*)w);
	g_print("%d ", gtk_check_menu_item_get_active((GtkCheckMenuItem*)w));
	gestionDuJeu(Sudoku);
}

void cb_afficheChiffre(GtkWidget* w, sudoku* Sudoku){
	
	if (!Sudoku->statut)
		return;
	
	int i;
	char* tab = range(0, TAILLE*TAILLE);
	coup Coup;
	//On décale le tableau de coup.
	for(i=Sudoku->nbCoupsTotal ; i > Sudoku->nbCoupsOrdinateur ; i--)
		Sudoku->listeCoups[i+1] = Sudoku->listeCoups[i];
	
	

	shuffle(tab, TAILLE*TAILLE, 30);
	for (i=0 ; i<TAILLE*TAILLE ; i++){ //On prend la premiere case vide.
		if (gUser[tab[i]] == VIDE)
			goto placerChiffre;
	}
	for (i=0 ; i<TAILLE*TAILLE ; i++){ //Si on a pas trouve de case vide, on prend la première case fausse.
		if (gUser[tab[i]] != Sudoku->grilleComplete[tab[i]])
			goto placerChiffre;
	}
	
	
	placerChiffre:
	
	Coup.position = tab[i];
	Coup.valeur = Sudoku->grilleComplete[tab[i]];
	Sudoku->listeCoups[Sudoku->nbCoupsOrdinateur] = Coup; //On ajoute le coup.
	(Sudoku->nbCoupsOrdinateur)++;
	(Sudoku->nbCoupsTotal)++;
	posActu = tab[i];
	gUser[Coup.position] = Coup.valeur;
	free(tab);
	gestionDuJeu(Sudoku);
}

void cb_correction(GtkWidget* w, sudoku* Sudoku){
	
	if (!Sudoku->statut)
		return;
	
	int i;
	
	

	for (i=0 ; i<TAILLE*TAILLE ; i++)
		cb_afficheChiffre(w, Sudoku);
	
}


void cb_vider(GtkWidget* w, sudoku* Sudoku){
	init_grille(Sudoku);
	
}
void cb_resoudre(GtkWidget* w, sudoku* Sudoku){
	char i;
	char grille[TAILLE*TAILLE];
	
	for (i=0; i<TAILLE*TAILLE ; i++){
		if (gUser[i] != VIDE && !coupLegal(gUser, i, gUser[i])){
			Sudoku->messageActuel = "Grille non valide ...";
			gestionDuJeu(Sudoku);
			return;
		}
	}
	
	memcpy(grille, gUser, TAILLE*TAILLE*sizeof(char));
	ret_bruteforce(gUser, 0, False);
	ret_bruteforce(grille, 0, True);
	if (!compareTab(gUser, grille, TAILLE*TAILLE))// Si les deux tableaux sont égaux => il n'y a qu'une seule solution.
		Sudoku->messageActuel = "Plusieurs solutions trouvées.";
	else
		Sudoku->messageActuel = "Grille résolue ! Seule solution trouvée.""Grille résolue ! Seule solution trouvée.""Grille résolue ! Seule solution trouvée.""Grille résolue ! Seule solution trouvée.""Grille résolue ! Seule solution trouvée.";
	gestionDuJeu(Sudoku);
}


void quit_fen(GtkWidget* w){
	gtk_main_quit ();
}

