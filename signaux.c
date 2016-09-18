#include "main.h"

void connexionSignaux(sudoku* Sudoku){

	GtkBuilder* build = Sudoku->build;
	
	//Signaux de la fenetre principale :
	g_signal_connect (gtk_builder_get_object(build, "fen1"),
					"delete-event", G_CALLBACK (quit_fen), NULL);

	
	
	/* Dans le menu :
	 * * * Action : */
	 g_signal_connect (gtk_builder_get_object(build, "menu_newPartie"),
					"activate", G_CALLBACK (cb_newPartie), Sudoku);
		
	 g_signal_connect (gtk_builder_get_object(build, "menu_quitter"),
					"activate", G_CALLBACK (quit_fen), NULL);
	
	
	
	
	
	
	
	
	/* * * Difficulté : */
	 g_signal_connect (gtk_builder_get_object(build, "menu_facile"),
					"activate", G_CALLBACK (cb_changeDifficulte), Sudoku);
	
	 g_signal_connect (gtk_builder_get_object(build, "menu_difficile"),
					"activate", G_CALLBACK (cb_changeDifficulte), Sudoku);
	
	 g_signal_connect (gtk_builder_get_object(build, "menu_intermediaire"),
					"activate", G_CALLBACK (cb_changeDifficulte), Sudoku);
	
	 g_signal_connect (gtk_builder_get_object(build, "menu_diabolique"),
					"activate", G_CALLBACK (cb_changeDifficulte), Sudoku);
					
					
	/* * * Affichage : */
	g_signal_connect (gtk_builder_get_object(build, "menu_afficherErreurs"),
					"activate", G_CALLBACK (cb_changeAffichage), Sudoku);
	
	
	
	/* * * Aide : */
	g_signal_connect (gtk_builder_get_object(build, "menu_apropos"),
					"activate", G_CALLBACK (run_apropos), build);
					
					
					
					
	/* Pour le canvas */				
	g_signal_connect (gtk_builder_get_object(build, "canvas"),
					"expose-event", G_CALLBACK (fill_canvas), Sudoku);


	gtk_widget_set_events (GTK_WIDGET(gtk_builder_get_object(build, "canvas")), GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK | GDK_SCROLL_MASK);
	g_signal_connect(gtk_builder_get_object(build, "canvas"), 
					"motion-notify-event", G_CALLBACK(survol_canvas), Sudoku);
					
	g_signal_connect(gtk_builder_get_object(build, "canvas"), 
					"button_press_event", G_CALLBACK(click_canvas), Sudoku);
					
	g_signal_connect(gtk_builder_get_object(build, "canvas"), 
					"scroll-event", G_CALLBACK(click_canvas), Sudoku);
	
	g_signal_connect (gtk_builder_get_object(build, "fen1"),
					"key-press-event", G_CALLBACK (on_key_press), Sudoku);
	
	/* Pour le deuxieme canvas */				
	g_signal_connect (gtk_builder_get_object(build, "canvas2"),
					"expose-event", G_CALLBACK (fill_canvas), Sudoku);


	gtk_widget_set_events (GTK_WIDGET(gtk_builder_get_object(build, "canvas2")), GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK | GDK_SCROLL_MASK);
	g_signal_connect(gtk_builder_get_object(build, "canvas2"), 
					"motion-notify-event", G_CALLBACK(survol_canvas), Sudoku);
					
	g_signal_connect(gtk_builder_get_object(build, "canvas2"), 
					"button_press_event", G_CALLBACK(click_canvas), Sudoku);
					
	g_signal_connect(gtk_builder_get_object(build, "canvas2"), 
					"scroll-event", G_CALLBACK(click_canvas), Sudoku);
	
	g_signal_connect (gtk_builder_get_object(build, "fen1"),
					"key-press-event", G_CALLBACK (on_key_press), Sudoku);
	


	/* Dans la barre d'outils :  */
	g_signal_connect (gtk_builder_get_object(build, "bouton_newPartie"),
					"clicked", G_CALLBACK (cb_newPartie), Sudoku);
					
	g_signal_connect (gtk_builder_get_object(build, "bouton_afficheChiffre"),
					"clicked", G_CALLBACK (cb_afficheChiffre), Sudoku);
					
	g_signal_connect (gtk_builder_get_object(build, "bouton_correction"),
					"clicked", G_CALLBACK (cb_correction), Sudoku);
					
					
	/* Dans la deucième barre d'outils :  */
	g_signal_connect (gtk_builder_get_object(build, "bouton_vider"),
					"clicked", G_CALLBACK (cb_vider), Sudoku);
					
	g_signal_connect (gtk_builder_get_object(build, "bouton_resoudre"),
					"clicked", G_CALLBACK (cb_resoudre), Sudoku);
	/*Fenetre a propos : */
	
}
