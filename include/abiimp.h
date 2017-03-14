#ifndef __ABIIMP__
#define __ABIIMP__
#include "environ.h"
#include "bilquad.h"
typedef struct Noeud Noeud;
struct Noeud{
  char *data;
  Noeud *droit;
  Noeud *gauche;
};

Noeud *create_noeud(Noeud *, Noeud *, char *);
void print_tree(Noeud *);
int env_tree(Noeud *, ENV *);
void env_c3a(BILQUAD);

#endif
