/*
 Programme : MORPION
 But :  Le but du jeu est d’aligner, avant son adversaire, 3 symboles identiques, horizontalement, verticalement ou en diagonale. 
 Date de dernière modification : 09/01/2022
 Auteur : Samuel HENTRICS LOISTINE, Ahmed FAKHFAKH
 Remarques :  Nous certifions être les auteurs de ce fichier
*/

#include <iostream>
#include "game-tools.h"
#include "jeu.h"
using namespace std;

// Variables

UnEtat etatJeu; // Etat du jeu actuel
UnJoueur joueur1; 
UnJoueur joueur2;
UnJoueur joueurGagnant;
UnJoueur joueurCourant;

char grille[TAILLE_GRILLE][TAILLE_GRILLE];
unsigned int numTour; // Numéro du tour actuel
const unsigned int MAX_NB_TOUR = TAILLE_GRILLE * TAILLE_GRILLE;

string coordonnee;
unsigned int coordLig;
unsigned int coordCol;

// Sous-programmes du main.cpp

void initialiserPartie();
// But : Prépare la partie : le numéro de tour, l’état du jeu, la grille ainsi que les joueurs

void jouerPartie();
// But : Permet de jouer la partie entre les deux joueurs tant que :
//          - un des joueurs décide d’abandonner
//          - un des joueurs gagne la partie
//          - il y a égalité car le nombre de tours maximum est atteint


void finaliserPartie();
// But : Permet de finaliser la partie en affichant la grille finale ainsi que le résultat de la partie.

// Main.cpp

int main(void)
{
    initialiserPartie();
    jouerPartie();
    finaliserPartie();
}

void initialiserPartie()
{
    // () >> initialisationVariables >> numTour, etatJeu, grille
    numTour = 1;
    etatJeu = enCours;
    initialiserGrille(grille);

    // () >> affichageJoueur >> joueur1, joueur2
    afficherRegles();
    personnalisation(joueur1, joueur2);

    // () >> effacerEcran >> ()
    effacer();
}

void jouerPartie()
{
    while (true)
    {
        // grille, numTour >> afficherGrille >> ()
        afficherGrille(grille, numTour);

        // joueur1, joueur2, numTour >> determinerJoueurCourant >> joueurCourant
        joueurCourant = determinerJoueur(joueur1, joueur2, numTour);

        // grille, etatJeu, joueurCourant >> saisirCoordonnee >> coordLig, coordCol
        saisirCoordonnee(grille, etatJeu, joueurCourant, coordLig, coordCol);

        // etatJeu >> verifierAbandonner >> [joueurGagnant]
        if (etatJeu == abandon)
        {
            // joueur1, joueur2, numTour >> determinerGagnant >> [joueurGagnant]
            joueurGagnant = determinerJoueur(joueur1, joueur2, numTour + 1);
            break;
        }

        // grille, coordLig, coordCol, joueurCourant >> insererCoordonnee >> grille
        insererCoordonnee(grille, coordLig, coordCol, joueurCourant.symbole);

        // numTour, grille, coordLig, coordol, joueurCourant >> verifierGrille >> [etatJeu]
        if (numTour >= TAILLE_GRILLE * 2 - 1)
        {
            verifierGagnant(grille, coordLig, coordCol, joueurCourant, etatJeu);
            
            if (etatJeu == gagnant)
            {
                joueurGagnant = joueurCourant;
                break;
            }
        }


        // numTour, MAX_NB_TOUR >> nbToursMaxAtteint >> [etatJeu]
        if (numTour == MAX_NB_TOUR)
        {
            etatJeu = egalite;
            break;
        }

        // numTour >> incrementerNumTour >> numTour
        numTour++;

        // () >> effacerEcran >> ()
        effacer();
    }

    // () >> effacerEcran >> ()
    effacer();
}

void finaliserPartie()
{
    // grille, numTour >> afficherGrille >> ()
    afficherGrille(grille, numTour);

    // etatJeu, [numTour], [joueurGagnant], [joueurCourant] >> resultatJeu >> ()
    resultat(etatJeu, numTour, joueurCourant, joueurGagnant);
}