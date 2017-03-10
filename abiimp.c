#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "include/environ.h"
#include "include/abiimp.h"

Noeud *create_noeud(Noeud *g, Noeud* d, char *data){
  Noeud *N_tmp = malloc(sizeof(Noeud));
  N_tmp->droit = d;
  N_tmp->gauche = g;
  N_tmp->data = strdup(data);
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

int env_tree(Noeud *n, ENV *e){
  if (n == NULL)
    return 0;
  if (!strcmp(":=", n->data)){
    initenv(e, n->gauche->data);
    affect(*e, n->gauche->data, env_tree(n->droit, e));
  }
  if (!strcmp(";", n->data)){
    env_tree(n->gauche, e);
    return env_tree(n->droit, e);
  }
  if (!strcmp("while", n->data)){
    while(env_tree(n->gauche, e))
      env_tree(n->droit, e);
    return 0;
  }
  if (!strcmp("if", n->data)){
    if (env_tree(n->gauche, e))
      env_tree(n->droit->gauche, e);
    else
      env_tree(n->droit->droit, e);
    return 0;
  }
  if (!strcmp("+", n->data))
    return env_tree(n->gauche, e) + env_tree(n->droit, e);
  if (!strcmp("-", n->data))
    return env_tree(n->gauche, e) - env_tree(n->droit, e);
  if (!strcmp("*", n->data))
    return env_tree(n->gauche, e) * env_tree(n->droit, e);
  bool valid = true;
  for (int i = 0; i < strlen(n->data); i++) {
    if (!isdigit(n->data[i])){
      valid = false;
      break;
    }
  }
  if (valid == true)
    return atoi(n->data);
  if (valch(*e, n->data) != 0)
    return valch(*e, n->data);
}
