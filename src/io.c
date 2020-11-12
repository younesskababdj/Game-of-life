#include <string.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>

#include "io.h"

#if MODECAIROGUI
/*
=====================
=== CAIRO VERSION ===
=====================
*/

#define MARGE_GAUCHE_GRILLE 20
#define MARGE_HAUTE_GRILLE 60
#define LARGEUR_GRILLE 450
#define HAUTEUR_GRILLE 400
#define CAIRO_LINE_WIDTH 2

extern cairo_surface_t *sfc;

cairo_surface_t *cairo_create_x11_surface0(int x, int y) {
    Display *dsp;
    Drawable da;
    int screen;
	Window rootwin;
    cairo_surface_t *sfc;

    if ((dsp = XOpenDisplay(NULL)) == NULL) {
		fprintf(stderr, "ERROR: Could not open display\n");
        exit(1);
	}
    screen = DefaultScreen(dsp);
	rootwin = RootWindow(dsp, screen);

	unsigned long background = 0x0031343f;
	da=XCreateSimpleWindow(dsp, rootwin, 1, 1, x, y, 0, 
			background, background);

	XSelectInput(dsp, da, ExposureMask|ButtonPressMask|KeyPressMask|StructureNotifyMask);
    XMapWindow(dsp, da);

	XStoreName(dsp, da, "Jeu de la vie");

    sfc = cairo_xlib_surface_create(dsp, da,
        DefaultVisual(dsp, screen), x, y);
    cairo_xlib_surface_set_size(sfc, x, y);

    return sfc;
}

void cairo_close_x11_surface(cairo_surface_t *sfc) {
   Display *dsp = cairo_xlib_surface_get_display(sfc);
   cairo_surface_destroy(sfc);
   XCloseDisplay(dsp);
}

void affiche_ligne (int c, int* ligne, int vieillissement, int hauteur, float tailleLigneGrille){
	int i;
	char ageBuffer[255];
	float tailleColonneGrille = (float) LARGEUR_GRILLE / (float) c;

	cairo_t *cr, *crcells;
	cr = cairo_create(sfc);
	crcells = cairo_create(sfc);
	
	cairo_set_source_rgb(cr, 0.6666666666666666, 0.6901960784313725, 0.7254901960784313);
	cairo_set_source_rgb(crcells, 0.6666666666666666, 0.6901960784313725, 0.7254901960784313);
	cairo_set_line_width(cr, CAIRO_LINE_WIDTH);
	
	cairo_move_to(cr, MARGE_GAUCHE_GRILLE, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille));


	for (i=0; i<c; ++i) {

		if (ligne[i] == 0) {
			cairo_line_to(cr, MARGE_GAUCHE_GRILLE + i * tailleColonneGrille, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille) + tailleLigneGrille);
			cairo_move_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * tailleColonneGrille), MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille));
			cairo_line_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * tailleColonneGrille), MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille) + tailleLigneGrille);
		} else if (ligne[i] == -1) {
			cairo_line_to(cr, MARGE_GAUCHE_GRILLE + i * tailleColonneGrille, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille) + tailleLigneGrille);
			cairo_line_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * tailleColonneGrille), MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille) + 1);
			cairo_line_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * tailleColonneGrille), MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille) + tailleLigneGrille);
			cairo_line_to(cr, MARGE_GAUCHE_GRILLE + i * tailleColonneGrille, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille) + tailleLigneGrille);
			cairo_move_to(cr, MARGE_GAUCHE_GRILLE + ((i) * tailleColonneGrille), MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille));
			cairo_line_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * tailleColonneGrille), MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille) + tailleLigneGrille);
			cairo_line_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * tailleColonneGrille), MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille));
		} else {
			cairo_line_to(cr, MARGE_GAUCHE_GRILLE + i * tailleColonneGrille, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille) + tailleLigneGrille);
			cairo_move_to(cr, MARGE_GAUCHE_GRILLE + ((i-1) * tailleColonneGrille) + 2, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille) + 2);
			cairo_rectangle(crcells, MARGE_GAUCHE_GRILLE + i * tailleColonneGrille + 3, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille + 3),
			tailleColonneGrille - 3, tailleLigneGrille - 3);
			cairo_fill(crcells);

			if (vieillissement) {
				sprintf(ageBuffer, "%d", ligne[i]);
				cairo_move_to(cr, MARGE_GAUCHE_GRILLE + ((i) * tailleColonneGrille) + tailleColonneGrille/2 - 5,
				MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille) + (tailleLigneGrille*2/3) - 3);
				cairo_set_source_rgb (cr, 0.19215686274509805, 0.20392156862745098, 0.24705882352941178);
				cairo_select_font_face(cr, "Arial",
					CAIRO_FONT_SLANT_NORMAL,
					CAIRO_FONT_WEIGHT_BOLD);
				cairo_set_font_size(cr, 15);
				cairo_show_text(cr, ageBuffer);

				cairo_set_source_rgb(cr, 0.6666666666666666, 0.6901960784313725, 0.7254901960784313);
			}

			cairo_move_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * tailleColonneGrille), MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille));
		}
	}

	cairo_fill(crcells);
	cairo_stroke(cr);
	cairo_destroy(cr);
		
	return;
}

void affiche_trait (int c, int hauteur, float tailleLigneGrille){
	cairo_t *cr;
	cr = cairo_create(sfc);
	
	cairo_set_source_rgb(cr, 0.6666666666666666, 0.6901960784313725, 0.7254901960784313);
	cairo_set_line_width(cr, CAIRO_LINE_WIDTH);
	
	cairo_move_to(cr, MARGE_GAUCHE_GRILLE, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille));

	int i;
	for (i = 0; i < c; ++i) {
		cairo_line_to(cr, MARGE_GAUCHE_GRILLE + LARGEUR_GRILLE, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille));
		cairo_move_to(cr, MARGE_GAUCHE_GRILLE, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille));
	}
	cairo_stroke(cr);
	cairo_destroy(cr);
}

void affiche_grille (grille g, int tempsEvolution, int comptageCyclique, int vieillissement){
	int i, l=g.nbl, c=g.nbc;
	char strTemps[255], strComptageCyclique[255], strVieillissement[255];
	sprintf(strTemps, "- Temps : %d", tempsEvolution);
	sprintf(strComptageCyclique, comptageCyclique ? "- Comptage : Cyclique" : "- Comptage : Non-cyclique");
	sprintf(strVieillissement, vieillissement ? "- Vieillissement : Active" : "- Vieillissement : Desactive");


	cairo_t *cr;
	cr = cairo_create(sfc);

	cairo_set_source_rgb(cr, 0.396078431372549, 0.6901960784313725, 0.9294117647058824);

	cairo_select_font_face(cr, "Arial",
		CAIRO_FONT_SLANT_NORMAL,
		CAIRO_FONT_WEIGHT_BOLD);

	cairo_set_font_size(cr, 26);
	cairo_move_to(cr, 20, 40);
	cairo_show_text(cr, "Conway's Game of Life");

	cairo_set_font_size(cr, 22);
	cairo_move_to(cr, 500, 80);
	cairo_move_to(cr, 500, 75);
	cairo_show_text(cr, "Commandes :");

	cairo_move_to(cr, 500, 265);
	cairo_show_text(cr, "Informations :");

	cairo_set_source_rgb(cr, 0.6666666666666666, 0.6901960784313725, 0.7254901960784313);

	cairo_select_font_face(cr, "Arial",
		CAIRO_FONT_SLANT_NORMAL,
		CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, 18);
	cairo_move_to(cr, 500, 100);
	cairo_show_text(cr, "- Entrée / clic gauche : Fait évoluer la grille");
	cairo_set_font_size(cr, 18);
	cairo_move_to(cr, 500, 125);
	cairo_show_text(cr, "- n : Charger une nouvelle grille");
	cairo_move_to(cr, 500, 150);
	cairo_show_text(cr, "- c : Passer en mode cyclique/non-cyclique");
	cairo_move_to(cr, 500, 175);
	cairo_show_text(cr, "- v : Activer/desactiver le vieillissement");
	cairo_move_to(cr, 500, 200);
	cairo_show_text(cr, "- d : Ouvrir la doc (doxygen & firefox requis)");
	cairo_move_to(cr, 500, 225);
	cairo_show_text(cr, "- q / clic droit : Quitter le programme");

	cairo_move_to(cr, 500, 290);
	cairo_show_text(cr, strTemps);
	cairo_move_to(cr, 500, 315);
	cairo_show_text(cr, strComptageCyclique);  
	cairo_move_to(cr, 500, 340);
	cairo_show_text(cr, strVieillissement);  

	cairo_destroy(cr);

	int hauteur = 0;
	float tailleLigne = (float) HAUTEUR_GRILLE / (float) g.nbl;
	affiche_trait(c, hauteur, tailleLigne);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i], vieillissement, hauteur, tailleLigne);
		affiche_trait(c, ++hauteur, tailleLigne);
	}
	return;
}

void efface_grille () {
	cairo_t *cr;
	cr = cairo_create(sfc);
	cairo_set_source_rgb (cr, 0.19215686274509805, 0.20392156862745098, 0.24705882352941178);
	cairo_paint(cr);
	cairo_destroy(cr);
}

void debut_jeu(grille *g, grille *gc) {
	int tempsEvolution = 1;

	int vieillissement = 0;

	int comptageCyclique = 1;
	int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_vivants_cyclique;

	XEvent e;

	int refreshGrille = 0;
	
	while(1) {
		XNextEvent(cairo_xlib_surface_get_display(sfc), &e);
		
		if (e.type==Expose && e.xexpose.count<1) {
			affiche_grille(*g, tempsEvolution, comptageCyclique, vieillissement);
		} else if (e.type == KeyPress) { // Touche pressée
			if (e.xkey.keycode == 36 || e.xkey.keycode == 104) { // Touche entrée (ou entrée numpad)
				evolue(g,gc,&tempsEvolution,compte_voisins_vivants,vieillissement);
				refreshGrille = 1;
			} else if (e.xkey.keycode == 57) { // Touche n

				int erreurInitialisation = 0;

				libere_grille(g);
				libere_grille(gc);
				do {
					char numeroGrille[10];
					char fichierGrille[100] = "grilles/grille";
					printf("Numero de la nouvelle grille a charger : ");
					scanf("%s", numeroGrille);
					strcat(fichierGrille, numeroGrille);
					strcat(fichierGrille, ".txt");
					erreurInitialisation = init_grille_from_file(fichierGrille, g);
					if (erreurInitialisation) {
						printf("Erreur : Le fichier grille \"%s\" est introuvable\n", fichierGrille);
					}
				} while (erreurInitialisation);

				tempsEvolution = 1; // Réinitialisation du temps
				alloue_grille (g->nbl, g->nbc, gc);
				refreshGrille = 1;

			} else if (e.xkey.keycode == 54) { // Touche c
				// voisinnage cyclique / non-cyclique
				if (comptageCyclique) { // On repasse à un comptage non-cyclique
					comptageCyclique = 0;
					compte_voisins_vivants = &(compte_voisins_vivants_non_cyclique);
				} else { // On repasse à un comptage cyclique
					comptageCyclique = 1;
					compte_voisins_vivants = &(compte_voisins_vivants_cyclique);
				}
				refreshGrille = 1;
			} else if (e.xkey.keycode == 55) { // Touche v
				vieillissement = !vieillissement;
				refreshGrille = 1;
			} else if (e.xkey.keycode == 40) {
				system("doxygen && firefox ./doc/html/index.html");
			} else if (e.xkey.keycode == 38) { // Touche q
				return;
			}
		} else if (e.type == ButtonPress) {
			if (e.xbutton.button == 1) { // Clic gauche (fait évoluer le jeu)
				evolue(g,gc,&tempsEvolution,compte_voisins_vivants,vieillissement);
				refreshGrille = 1;
			} else if (e.xbutton.button == 3) { // Clic droit (quitte le jeu)
				return;
			}
		} else if (e.type == DestroyNotify) {
			printf("Window killed :'(\n");
		}

		if (refreshGrille) {
			efface_grille();
			affiche_grille(*g, tempsEvolution, comptageCyclique, vieillissement);
			refreshGrille = 0;
		}
	}
	return;
}


#else

/*
====================
=== TEXT VERSION ===
====================
*/

void affiche_trait (int c) {
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne, int vieillissement) {
	int i;
	if (vieillissement) {
		for (i=0; i<c; ++i) {
			if (ligne[i] == 0 ) printf ("|   ");
			else if (ligne[i] == -1) printf("| X "); // Non-viable
			else printf ("| %d ", ligne[i]);
		}
	} else {
		for (i=0; i<c; ++i) {
			if (ligne[i] == 0 ) printf ("|   ");
			else if (ligne[i] == -1) printf("| X "); // Non-viable
			else printf ("| 0 ");
		}
	}
	printf("|\n");
	return;
}

void affiche_grille (grille g, int tempsEvolution, int comptageCyclique, int vieillissement){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	printf("\e[K");
	printf("Temps : %d | ", tempsEvolution);
	printf("Comptage : ");
	comptageCyclique ? printf("Cyclique") : printf("Non-cyclique");
	printf(" | ");
	printf("Vieillissement : ");
	vieillissement ? printf("Active") : printf("Desactive");

	printf("\n\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i], vieillissement);
		affiche_trait(c);
	}
	printf("\n");
	return;
}

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 7);
}

void debut_jeu(grille *g, grille *gc){
	int tempsEvolution = 1;

	int passerProchaineEvolution = 0;

	int vieillissement = 0;

	int comptageCyclique = 1;
	int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_vivants_cyclique;

	char c = getchar();
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
			case '\n' :
			{ // touche "entree" pour évoluer
				if (passerProchaineEvolution) {
					passerProchaineEvolution = 0;
				} else {
					evolue(g,gc,&tempsEvolution,compte_voisins_vivants,vieillissement);
					efface_grille(*g);
					affiche_grille(*g, tempsEvolution, comptageCyclique, vieillissement);
				}
				break;
			}
			case 'n' :
			{ // touche 'n' pour charger dynamiquement une nouvelle grille
				int erreurInitialisation = 0;

				libere_grille(g);
				libere_grille(gc);
				do {
					char numeroGrille[10];
					char fichierGrille[100] = "grilles/grille";
					printf("Numero de la nouvelle grille a charger : ");
					scanf("%s", numeroGrille);
					strcat(fichierGrille, numeroGrille);
					strcat(fichierGrille, ".txt");
					erreurInitialisation = init_grille_from_file(fichierGrille, g);
					if (erreurInitialisation) {
						printf("Erreur : Le fichier grille \"%s\" est introuvable\n", fichierGrille);
					}
				} while (erreurInitialisation);

				tempsEvolution = 1; // Réinitialisation du temps
				alloue_grille (g->nbl, g->nbc, gc);
				affiche_grille(*g, tempsEvolution, comptageCyclique, vieillissement);

				printf("\n\e[2A");
				printf("\n");

				/* On empêche l'évolution au clic sur "Entrée"
				lors du chargement de la nouvelle grille */
				passerProchaineEvolution = 1;

				break;
			}
			case 'c' :
			{
				// voisinnage cyclique / non-cyclique
				if (comptageCyclique) { // On repasse à un comptage non-cyclique
					comptageCyclique = 0;
					compte_voisins_vivants = &(compte_voisins_vivants_non_cyclique);
				} else { // On repasse à un comptage cyclique
					comptageCyclique = 1;
					compte_voisins_vivants = &(compte_voisins_vivants_cyclique);
				}

				printf("\e[A");
				printf("\e[K");
				printf("\n");
				break;
			}
			case 'v' :
			{
				// activation / désactivation du vieillissement
				vieillissement = !vieillissement;

				printf("\e[A");
				printf("\e[K");
				printf("\n");
				break;
			}
			default :
			{ // touche non traitée
				printf("\e[A");
				printf("\e[K");
				printf("\n");
				break;
			}
		}
		c = getchar();
	}
	printf("A bientot !\n");
	return;
}

#endif
