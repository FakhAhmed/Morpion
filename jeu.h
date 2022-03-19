/**  MODULE Fractions
     permettant la manipulation 
     ----------------------------------------------------------------------
But :
    On met à disposition :
    - Un type UnEtat, composé :
        ...enCours
        ...abandon
        ...gagnant
        ...egalite

    - Un type UnJoueur, composé :
        ... prenom  : prenom  du joueur
        ... symbole : symbole du joueur

    - Des primitives (= sous-programmes) permettant de :
        ...Affiche à l'écran les règles du jeu
        ...Permet de personnaliser le prénom et le symbole des joueurs j1 et j2
        ...Retourne un joueur entre le joueur j1 et j2 selon le numéro de tour.
        ...Saisie de la coordonnée par le joueur courant (jCourant) qui sera mise dans la grille de jeu (grilleJeu). Si le joueur saisie A (ou a), l'état du jeu (etat) passe à 'abandon'.
        ...Retourne le résultat de fin de jeu,
        ...Essaye toutes les combinaisons dont le joueur peut gager à partir d'une coordonnée donnée (ligne et colonne)
        
---------

 Date de dernière modification : 09/01/2022
 Auteur : Samuel HENTRICS LOISTINE, Ahmed FAKHFAKH
 Remarques : Nous certifions être les auteurs de ce fichier
*/

#ifndef JEU_H
#define JEU_H

#include "grille.h"
#include <iostream>
using namespace std;

// Définition de la structure UnEtat
enum UnEtat
{
    enCours,
    abandon,
    gagnant,
    egalite
};

//Definition de type UnJoueur
struct UnJoueur
{
    string prenom; // Prenom du joueur
    char symbole;  // Symbole du joueur
};

//Declaration des sous-programmes

void afficherRegles();
// But : Affiche à l'écran les règles du jeu

void personnalisation(UnJoueur &j1, UnJoueur &j2);
// But : Permet de personnaliser le prénom et le symbole des joueurs j1 et j2

UnJoueur determinerJoueur(const UnJoueur &j1, const UnJoueur &j2, unsigned int tour);
// But : Retourne un joueur entre le joueur j1 et j2 selon le numéro de tour

void saisirCoordonnee(char grilleJeu[][TAILLE_GRILLE], UnEtat &etat, const UnJoueur &jCourant, unsigned int &coordLigne, unsigned int &coordColonne);
// But : Saisie de la coordonnée par le joueur courant (jCourant) qui sera mise dans la grille de jeu (grilleJeu)
//       Si le joueur saisie A (ou a), l'état du jeu (etat) passe à 'abandon'.

void resultat(const UnEtat &etat, unsigned int tour, const UnJoueur &jCourant, const UnJoueur &jGagnant);
// But : Retourne le résultat de fin de jeu,
//       Si etat = abandon, un joueur (jGagnant) gagne car l'autre joueur (jCourant) a quitté le jeu puis on affiche à quel tour le joueur a gagné (tour)
//       Si etat = gagnant, un joueur (jGagnant) a gagné puis on affiche à quel tour le joueur a gagné (tour)
//       Si etat = egalite, aucun joueur n'a gagné : il y a égalité
// Pré-condition : etat ne peut avoir que pour valeur : abandon, gagnant ou egalite

void verifierGagnant(const char grilleJeu[][TAILLE_GRILLE], unsigned int ligne, unsigned int colonne, const UnJoueur &jCourant, UnEtat &etat);
// But : Essaye toutes les combinaisons dont le joueur peut gager à partir d'une coordonnée donnée (ligne et colonne)
//       Le joueur peut gagner soit en ligne, en colonne ou bien par diagonale (de droite à gauche ou de gauche à droite) 
//       Si le joueur gagne sur une de ses combinaisons, etat prend "gagnant".

#endif // JEU_H
