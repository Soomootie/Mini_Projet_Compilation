#ifndef __ABIIMP__
#define __ABIIMP__

typedef struct Noeud Noeud;
struct Noeud{
  char *data;
  Noeud *droit;
  Noeud *gauche;
};

Noeud *create_noeud(Noeud *, Noeud *, char *);
void print_tree(Noeud *);

#endif
