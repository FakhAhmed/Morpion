/**  MODULE grille
     permettant la manipulation de grille
     ----------------------------------------------------------------------
But :
    On met à disposition :
    - Une constante TAILLE_GRILLE = 3
    - Des primitives (= sous-programmes) permettant de :
        ...À partir d'une grille donnée (grilleJeu), initialiser la grille en la remplissant d'espace.
        ...Afficher la grille du jeu ainsi que le tour actuel.
        ...Insérer un symbole dans la grille de jeu à partir d'une ligne et d'une colonne donnée.
---------

 Date de dernière modification : 09/01/2022
 Auteur : Samuel HENTRICS LOISTINE, Ahmed FAKHFAKH
 Remarques : Nous certifions être les auteurs de ce fichier
*/

/* Permet de manipuler la grille */

#ifndef GRILLE_H
#define GRILLE_H
#include <iostream>
using namespace std;

/* *****************************************************
    LES VARIABLES DE LA GRILLE
   *****************************************************

   La variable globale "tailleGrille", permet de connaitre la taille de la grille
*/
const unsigned int TAILLE_GRILLE = 3; // Taille de la grille du jeu

/* *************************************************** */

void initialiserGrille(char grilleJeu[][TAILLE_GRILLE]);
// But : A partir d'une grille donnée (grilleJeu), initialiser la grille en la remplissant d'espace

void afficherGrille(const char grilleJeu[][TAILLE_GRILLE], unsigned int tour);
// But : Affiche la grille du jeu ainsi que le tour actuel.

void insererCoordonnee(char grilleJeu[][TAILLE_GRILLE], unsigned int ligne, unsigned int colonne, char symbole);
// But : Insère un symbole dans la grille de jeu à partir d'une ligne et d'une colonne donnée.

#endif // GRILLE_H
