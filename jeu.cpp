/**  CORPS MODULE jeu
     ------------------------
     Remarques : Nous certifions être les auteurs de ce fichier */
// inclusions
#include "jeu.h"
#include "grille.h"
#include <iostream>
#include "game-tools.h"
using namespace std;

// Types - Variables - Constantes propres au corps

// Declaration des sous-programmes utilisés dans ce corps

UnJoueur saisirJoueur();
// But : Retourne un joueur avec un prénom et un symbole

UnJoueur saisirJoueur(const UnJoueur &autreJoueur);
// But : Retourne un joueur avec un prénom et un symbole différent de autreJoueur

bool coordonneeCorrecte(unsigned int ligne, unsigned int colonne);
//But: Vérifie si la coordonnée est dans la limite de la taille de la grille
//     Retourne vrai, si elle se trouve dans les limites
//     Sinon, retourne faux

bool caseVide(const char grilleJeu[][TAILLE_GRILLE], unsigned int ligne, unsigned int colonne);
//But: vérifier si la case de la coordonnée  est vide

void verifierLigne(const char grilleJeu[][TAILLE_GRILLE], unsigned int ligne, const UnJoueur &jCourant, UnEtat &etat);
// But : verifier si le joueur courant (jCourant) gagne sur la ligne de sa coordonnée dans la grille .
//       Si le joueur gagne sur la ligne, l'état du jeu (etat) passe à gagnant.

void verifierColonne(const char grilleJeu[][TAILLE_GRILLE], unsigned int colonne, const UnJoueur &jCourant, UnEtat &etat);
// But : Vérifie si le joueur courant (jCourant) gagne sur la colonne de sa coordonnée dans la grille.
//       Si le joueur gagne sur la colonne, l'état du jeu (etat) passe à gagnant.

void verifierDiagonaleGaucheDroite(const char grilleJeu[][TAILLE_GRILLE], unsigned int ligne, unsigned int colonne, const UnJoueur &jCourant, UnEtat &etat);
// But : Vérifie si le joueur courant (jCourant) gagne sur la diagonale de gauche à droite de la coordonnée dans la grille.
//       Si le joueur gagne sur la diagonale (gauche à droite), l'état du jeu (etat) passe à gagnant.

void verifierDiagonaleDroiteGauche(const char grilleJeu[][TAILLE_GRILLE], const UnJoueur &jCourant, UnEtat &etat);
// But : Vérifie si le joueur courant (jCourant) gagne sur la diagonale de droite à gauche de la coordonnée dans la grille.
//       Si le joueur gagne sur la diagonale (droite à gauche), l'état du jeu (etat) passe à gagnant.

//Corps des sous-programmes déclarés dans l'interface jeu.h

void afficherRegles()
{
    cout << "---------------- M O R P I O N  ----------------" << endl
         << endl;
    cout << "Jeu avec 2 joueurs humains et une grille de 9 cases : 3 lignes et 3 colonnes." << endl;
    cout << "Chaque joueur joue a tour de role." << endl;
    cout << "Le but du jeu est d'aligner, avant son adversaire, 3 symboles identiques, horizontalement, verticalement ou en diagonale." << endl
         << endl;

    cout << "La partie se termine :" << endl;
    cout << "- quand l'un des joueurs a aligne ses 3 symboles, et il gagne," << endl;
    cout << "- quand la grille est complete, et il y a une egalite (pas de gagnant)" << endl;
    cout << "- quand l'un des joueurs abandonne, et c'est alors l'autre joueur qui gagne." << endl;
    cout << "Chaque joueur a donc son propre symbole." << endl
         << endl;

    cout << "Dans cette version du Morpion, une phase prealable de personnalisation permet a chaque joueur de saisir son prenom et le symbole" << endl;
    cout << "choisi pour jouer" << endl;
    cout << "Lorsqu'arrive son tour de joueur, un joueur peut :" << endl;
    cout << "- saisir la position de la case ou placer son symbole, sous la forme LigneColonne (exemple : 12 pour Ligne 1, Colonne 2)" << endl;
    cout << "- saisir A (ou a) pour abandonner le jeu" << endl
         << endl;
    cout << "------------------------------------------------" << endl
         << endl;
}

void personnalisation(UnJoueur &j1, UnJoueur &j2)
{
    cout << "--- Phase de personnalisation ---" << endl
         << endl;

    // joueur1
    j1 = saisirJoueur();

    cout << endl << endl;
    // joueur2
    j2 = saisirJoueur(j1);

    cout << endl;
}

UnJoueur determinerJoueur(const UnJoueur &j1, const UnJoueur &j2, unsigned int tour)
{
    // Variables
    UnJoueur jCourant; // Joueur courant déterminé grâce au numéro du tour

    // Traitements
    if (tour % 2 == 1)
    {
        jCourant = j1;
    }
    else
    {
        jCourant = j2;
    }
    return jCourant;
}

void saisirCoordonnee(char grilleJeu[][TAILLE_GRILLE], UnEtat &etat, const UnJoueur &jCourant,
                      unsigned int &coordLigne, unsigned int &coordColonne)
{
    // Variables
    string coordonnee; // Coordonnee saisie par le joueur

    // Traitements
    cout << "---> " << jCourant.prenom << ", entrez :" << endl
         << endl;

    cout << "     Une coordonnee (LigneColonne, ex. : 12 pour Ligne 1, Colonne 2)," << endl;
    cout << "     ou bien A(bandonner)." << endl
         << endl;

    while (true)
    {
        cout << "     Votre choix ? ";
        cin >> coordonnee;

        if (toupper(coordonnee[0]) == 'A')
        {
            etat = abandon;
            break;
        }
        else
        {
            coordLigne = int(coordonnee[0]) - 49;
            coordColonne = int(coordonnee[1]) - 49;
            if (coordonneeCorrecte(coordLigne, coordColonne))
            {
                if (caseVide(grilleJeu, coordLigne, coordColonne))
                {
                    break;
                }
            }
        }
    }
}

void resultat(const UnEtat &etat, unsigned int tour, const UnJoueur &jCourant, const UnJoueur &jGagnant)
{
    cout << "--- Fin de la partie ---" << endl
         << endl;

    switch (etat)
    {
    case abandon:
        cout << "Partie gagnee par " << jGagnant.prenom << " suite a l'abandon de " << jCourant.prenom << " au Tour numero " << tour;
        break;

    case gagnant:
        cout << "Partie gagnee par " << jGagnant.prenom << " au Tour numero " << tour;
        break;

    case egalite:
        cout << "Egalite (pas de gagnant) car grille complete";
        break;

    default:
        cout << "Erreur";
        break;
    }
    cout << endl << endl;
}

void verifierGagnant(const char grilleJeu[][TAILLE_GRILLE], unsigned int ligne, unsigned int colonne, const UnJoueur &jCourant, UnEtat &etat)
{
    // grilleJeu, ligne, jCourant >> verifierLigne >> [etat]
    verifierLigne(grilleJeu, ligne, jCourant, etat);

    if (etat != gagnant)
    {
        // grilleJeu, colonne, jCourant >> verifierColonne >> [etat]
        verifierColonne(grilleJeu, colonne, jCourant, etat);
    }

    if (etat != gagnant)
    {
        // grilleJeu, ligne, colonne, jCourant >> verifierDiagonaleGaucheDroite >> [etat]
        verifierDiagonaleGaucheDroite(grilleJeu, colonne, ligne, jCourant, etat);
    }

    if (etat != gagnant)
    {
        // grilleJeu, jCourant >> verifierDiagonaleDroiteGauche >> [etat]
        verifierDiagonaleDroiteGauche(grilleJeu, jCourant, etat);
    }
}

// Corps des sous-programmes déclarés dans ce corps

UnJoueur saisirJoueur()
{
    // Variables
    UnJoueur joueur;//Contient les informations sur un joueur

    // Traitements

    // () >> saisiePrenomJoueur >> joueur
    cout << "JOUEUR 1, entrez votre prenom : ";
    cin >> joueur.prenom;

    // () >> saisieSymboleJoueur >> joueur
    cout << joueur.prenom << ", entrez votre symbole (1 lettre ou 1 chiffre) : ";
    cin >> joueur.symbole;

    return joueur;
}

UnJoueur saisirJoueur(const UnJoueur &autreJoueur)
{
    // Variables
    UnJoueur joueur;//Le joueur qui sera retourné par cette fonction ayant un prénom et un symbole différent de autreJoueur

    // Traitements

    // autreJoueur >> saisiePrenomJoueur >> joueur
    do
    {
        cout << "JOUEUR 2, entrez votre prenom, autre que '" << autreJoueur.prenom << "' : ";
        cin >> joueur.prenom;
    } while (joueur.prenom == autreJoueur.prenom);

    // autreJoueur >> saisieSymboleJoueur >> joueur
    do
    {
        cout << joueur.prenom << ", entrez votre symbole (1 lettre ou 1 chiffre), autre que '" << autreJoueur.symbole << "' : ";
        cin >> joueur.symbole;
    } while (joueur.symbole == autreJoueur.symbole);

    return joueur;
}

bool coordonneeCorrecte(unsigned int ligne, unsigned int colonne)
{
    return (ligne <= 2 && colonne <= 2);
}

bool caseVide(const char grilleJeu[][TAILLE_GRILLE], unsigned int ligne, unsigned int colonne)
{
    return (grilleJeu[ligne][colonne] == ' ');
}

void verifierLigne(const char grilleJeu[][TAILLE_GRILLE], unsigned int ligne, const UnJoueur &jCourant, UnEtat &etat)
{
    //variables locales
    unsigned int caseCourante;//Case courante qui vérifiera les conditions d’arrêt (soit, la case n’a pas le symbole du joueur, soit, toutes les cases ont été traités et le joueur a gagné)
    //traitements
    caseCourante = 0;
    while (true)
    {
        if (grilleJeu[ligne][caseCourante] != jCourant.symbole)
        {
            break;
        }
        if (caseCourante == TAILLE_GRILLE - 1)
        {
            etat = gagnant;
            break;
        }
        caseCourante++;
    }
}

void verifierColonne(const char grilleJeu[][TAILLE_GRILLE], unsigned int colonne, const UnJoueur &jCourant, UnEtat &etat)
{
    // Variables
    unsigned int caseCourante;//Case courante qui vérifiera les conditions d’arrêt (soit, la case n’a pas le symbole du joueur, soit, toutes les cases ont été traités et le joueur a gagné)

    // Traitements
    caseCourante = 0;
    while (true)
    {
        if (grilleJeu[caseCourante][colonne] != jCourant.symbole)
        {
            break;
        }
        if (caseCourante == 2)
        {
            etat = gagnant;
            break;
        }
        caseCourante++;
    }
}

void verifierDiagonaleGaucheDroite(const char grilleJeu[][TAILLE_GRILLE], unsigned int ligne, unsigned int colonne, const UnJoueur &jCourant, UnEtat &etat)
{
    // Variables
    unsigned int caseCourante;//Case courante qui vérifiera les conditions d’arrêt (soit, la case n’a pas le symbole du joueur, soit, toutes les cases ont été traités et le joueur a gagné)

    // Traitements
    if (colonne == ligne)
    {
        caseCourante = 0;
        while (true)
        {
            if (grilleJeu[caseCourante][caseCourante] != jCourant.symbole)
            {
                break;
            }
            if (caseCourante == 2)
            {
                etat = gagnant;
                break;
            }
            caseCourante++;
        }
    }
}

void verifierDiagonaleDroiteGauche(const char grilleJeu[][TAILLE_GRILLE], const UnJoueur &jCourant, UnEtat &etat)
{
    //variables locales
    unsigned int caseCol;//Case de la colonne courante qui vérifiera la conditions d’arrêt : la case n’a pas le symbole du joueur grâce à aussi la variable caseLigne
    unsigned int caseLigne;//Case de la ligne courante qui vérifiera les conditions d’arrêt (soit, la case n’a pas le symbole du joueur grâce à aussi la variable caseCol, soit, toutes les cases ont été traités et le joueur a gagné)
    //traitements
    caseCol = TAILLE_GRILLE - 1;
    caseLigne = 0;
    while (true)
    {
        if (grilleJeu[caseLigne][caseCol] != jCourant.symbole)
        {
            break;
        }
        if (caseLigne == TAILLE_GRILLE - 1)
        {
            etat = gagnant;
            break;
        }
        caseCol--;
        caseLigne++;
    }
}