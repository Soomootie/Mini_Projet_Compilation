#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "include/environ.h"
#include "include/bilquad.h"
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


void env_c3a(BILQUAD list){
  ENV env = Envalloc();
  QUAD elem = list.debut;
  while (elem != NULL) {
    /***Afc***/
    if (!strcmp(elem->OP, "Afc")) {
      initenv(&env, elem->RES);
      affect(env, elem->RES, atoi(elem->ARG1));
      elem = elem->SUIV;
    }
    /***Pl Mu Mo***/
    else if (!strcmp(elem->OP,"Pl") || !strcmp(elem->OP, "Mu") || !strcmp(elem->OP, "Mo")) {
      initenv(&env, elem->RES);
      initenv(&env, elem->ARG1);
      initenv(&env, elem->ARG2);
      int res = eval(elem->OP, valch(env, elem->ARG1), valch(env, elem->ARG2));
      affect(env, elem->RES, res);
      elem = elem->SUIV;
    }
    /***Af***/
    else if (!strcmp(elem->OP, "Af")) {
      initenv(&env, elem->ARG1);
      initenv(&env, elem->ARG2);
      affect(env, elem->ARG1, valch(env, elem->ARG2));
      elem = elem->SUIV;
    }
    /***Jp***/
    else if (!strcmp(elem->OP, "Jp")) {
      QUAD listStart = list.debut;
      char *dest = elem->RES;
      while (strcmp(listStart->ETIQ,dest) != 0)
        listStart = listStart->SUIV;
      elem=listStart;
    }
    /***Je***/
    else if (!strcmp(elem->OP, "Jz")) {
      QUAD listStart = list.debut;
      char *dest = elem->RES;
      if(valch(env, elem->ARG1) == 0){
        while (strcmp(listStart->ETIQ,dest) != 0){
          listStart = listStart->SUIV;
        }
        elem=listStart;
      } else {
        elem = elem->SUIV;
      }
    } else if (!strcmp(elem->OP, "St")){
      break;
    } else if (!strcmp(elem->OP, "Sk")){
        elem = elem->SUIV;
      }
  }
    ecrire_env(env);
}
