/**  CORPS MODULE grille
     ------------------------ 
     Remarques : Nous certifions être les auteurs de ce fichier */
// inclusions
#include "grille.h"
#include <iostream>
using namespace std;

void initialiserGrille(char grilleJeu[][TAILLE_GRILLE])
{
    // Variables
    unsigned int ligne;//Ligne courante qui sera traitée
    unsigned int colonne;//Colonne courante qui sera traitée

    // Traitements
    for (ligne = 0; ligne <= TAILLE_GRILLE - 1; ligne++)
    {
        for (colonne = 0; colonne <= TAILLE_GRILLE - 1; colonne++)
        {
            grilleJeu[ligne][colonne] = ' ';
        }
    }
}

void afficherGrille(const char grilleJeu[][TAILLE_GRILLE], unsigned int tour)
{
    // Variables
    unsigned int ligne;//Ligne courante qui sera traitée
    unsigned int colonne;//Colonne courante qui sera traitée

    // Traitements

    cout << "Tour numero " << tour << endl
         << endl;

    for (ligne = 0; ligne <= TAILLE_GRILLE - 1; ligne++)
    {
        cout << "    [";
        for (colonne = 0; colonne <= TAILLE_GRILLE - 2; colonne++)
        {
            cout << grilleJeu[ligne][colonne] << "|";
        }
        cout << grilleJeu[ligne][TAILLE_GRILLE - 1] << "]" << endl;
    }

    cout << endl;
}

void insererCoordonnee(char grilleJeu[][TAILLE_GRILLE], unsigned int ligne, unsigned int colonne, char symbole)
{
    grilleJeu[ligne][colonne] = symbole;
}