#include "main.h"

void affichageFenetre(sudoku* Sudoku){
	GtkBuilder*  build	= NULL;
	GError*  p_err		 = NULL;

	/* Initialisation de GTK+ */
	gtk_init (NULL, NULL);


	/* Creation d'un nouveau GtkBuilder */
	build = gtk_builder_new ();

	if (build != NULL)
	{
		/* Chargement du XML dans build */
		gtk_builder_add_from_file (build, "interface.glade", &p_err);

		if (p_err == NULL)
		{
			Sudoku->build = build;
			
			GtkWidget * p_win = (GtkWidget *) gtk_builder_get_object(build, "fen1"); //p_win pointe vers la fenetre


			connexionSignaux(Sudoku);
			gtk_widget_show_all (p_win); //On affiche la fenetre
			gestionDuJeu(Sudoku);
			gtk_main ();				 //Et enfin la boucle d'evenenement.
			return (void)0;
			
		}

	}
	printf("Erreur lors du chargement de l'interface.\n");
	printf("Verifiez que le fichier 'interface.glade' est bien present dans le dossier et que vous avez les droits de lecture et d'execution dessus.");
}

void run_chargement(GtkBuilder* build){
	gtk_widget_show_all(GTK_WIDGET(gtk_builder_get_object(build, "fen_chargement")));
}

void quit_chargement(GtkBuilder* build){
	gtk_widget_hide_all(GTK_WIDGET(gtk_builder_get_object(build, "fen_chargement")));
}

void pushStatusBar(GtkBuilder* build, char* txt){
	
	gtk_statusbar_push (
	GTK_STATUSBAR(gtk_builder_get_object(build, "statusBar")), 
	gtk_statusbar_get_context_id (
			GTK_STATUSBAR(gtk_builder_get_object(build, "statusBar")), "Info"), 
	txt
	);
}
