/** @file
 *	@brief Fonctions d'input/output (entrées/sorties) du programme
 */
#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

#if MODECAIROGUI

    #define SIZEX 900
    #define SIZEY 500

    /** 
     * Création d'une surface Xlib Cairo
     * @param[in] x Largeur de la surface (en pixels)
     * @param[in] y Hauteur de la surface (en pixels)
     */
    cairo_surface_t *cairo_create_x11_surface0(int x, int y);

    /**
     * Destruction d'une surface Xlib Cairo et fermeture de la connexion à X
     * @param[in] sfc Surface Cairo à détruire
     */
    void cairo_close_x11_surface(cairo_surface_t *sfc);

    /**
     * Affichage d'un trait horizontal
     * @param[in] c           Nombre de cellules du trait
     * @param[in] hauteur     Numéro de la hauteur du trait à tracer (en partant du haut de la grille)
     * @param[in] tailleLigne Hauteur de la ligne (en pixels)
     */
    void affiche_trait (int c, int hauteur, float tailleLigne);

    /**
     * Affichage d'une ligne de la grille
     * @param[in] c              Nombre de cellules de la ligne
     * @param[in] ligne          Tableau indiquant pour chaque cellule si elle est vivante ou morte
     * @param[in] vieillissement Indique si le vieillissement est activé (1) ou désactivé (0)
     * @param[in] hauteur        Numéro de la hauteur du trait à tracer (en partant du haut de la grille)
     * @param[in] tailleLigne    Hauteur de la ligne (en pixels)
     */
    void affiche_ligne (int c, int* ligne, int vieillissement, int hauteur, float tailleLigne);

    /**
     * Effacement de la grille sur l'interface graphique
     */
    void efface_grille ();

#else

    /**
     * Affichage d'un trait horizontal
     * @param[in] c Nombre de cellules du trait
     */
    void affiche_trait (int c);

    /**
     * Affichage d'une ligne de la grille
     * @param[in] c              Nombre de cellules de la ligne
     * @param[in] ligne          Tableau indiquant pour chaque cellule si elle est vivante ou morte
     * @param[in] vieillissement Indique si le vieillissement est activé (1) ou désactivé (0)
     */
    void affiche_ligne (int c, int* ligne, int vieillissement);

    /**
     * Affichage d'une grille
     * @param[in] g                Grille à afficher
     * @param[in] tempsEvolution   Entier représentant le temps (pas) d'évolution de la grille en cours
     * @param[in] comptageCyclique Indique si le comptage est en mode cyclique (1) ou non-cyclique (0)
     * @param[in] vieillissement   Indique si le vieillissement est activé (1) ou désactivé (0)
     */
    void affiche_grille (grille g, int tempsEvolution, int comptageCyclique, int vieillissement);

    /**
     * Effacement d'une grille
     * @param[in] g Grille à effacer
     */
    void efface_grille (grille g);

#endif

/**
 * Débute le jeu
 * @param[in,out] g  Pointeur sur la grille (principale)
 * @param[in,out] gc Pointeur sur la seconde grille allouée aux mêmes nombres de lignes et colonnes que la première et qui permettra plus tard l'évolution de la grille de g vers gc
 */
void debut_jeu(grille *g, grille *gc);

#endif
