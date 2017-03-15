#ifndef __UTILS__H__
#define __UTILS__H__
#include "environ.h"
#include "bilquad.h"

/* Structure representant un arbre binaire. */
typedef struct Noeud Noeud;
struct Noeud{
  char *data;
  Noeud *droit;
  Noeud *gauche;

};
/* Initialise un noeud , avec pour data le char *. */
Noeud *create_noeud(Noeud *, Noeud *, char *);
/* Affiche l'arbre à partir du noeud. */
void print_tree(Noeud *);
/* Produit l'environnement imp à partir de l'arbre (noeud). */
int env_imp(Noeud *, ENV *);
/* Produit l'environnement c3a à partir d'un bilquad. */
ENV env_c3a(BILQUAD);
/* Produit le code c3a à partir d'un code imp. */
BILQUAD imp_c3a(Noeud *);
/* Permet de créer la dernière étiquette du code c3a. */
char *etiq_fin();
/* Produit le code y86 à partir du code c3a. */
void c3a_y86(BILQUAD);
/* Copie Init dans un fichier. */
void debut_y86(FILE *);
/* Copie dans un fichier , MUL , MULPLUS ...
 * Initialise Data avec les variables de l'environnement. */
void fin_y86(FILE *, ENV *);

#endif
