#include <stdio.h>
#include <stdlib.h>
#include "include/abiimp.h"

Noeud *create_noeud(Noeud *g, Noeud* d, char *data){
  Noeud *N_tmp = malloc(sizeof(Noeud));
  N_tmp->droit = d;
  N_tmp->gauche = g;
  N_tmp->data = data;
  return N_tmp;
}

void print_tree(Noeud *n){
  if (n == NULL)
    return;
  printf("%s ", n->data);
  if (n->droit != NULL && n->gauche != NULL){
    print_tree(n->gauche);
    print_tree(n->droit);
  }
}
