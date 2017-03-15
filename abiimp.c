#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "include/environ.h"
#include "include/bilquad.h"
#include "include/abiimp.h"

char * p[3] = {"ET", "CT", "VA"};
int number = 0;

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

BILQUAD l_c3a(Noeud *n){
  BILQUAD tmp = bilquad_vide();
  BILQUAD g = bilquad_vide();
  BILQUAD d = bilquad_vide();
  char *etiq = malloc(sizeof(char));
  char *arg1 = malloc(sizeof(char));
  char *arg2 = malloc(sizeof(char));
  char *res = malloc(sizeof(char));
  if (n == NULL)
    return tmp;
  if (!strcmp(":=", n->data)){
    sprintf(etiq, "%s%d", p[0] , number++ );
    sprintf(arg1, "%s", n->gauche->data);
    tmp = concatq(tmp, l_c3a(n->droit));
    sprintf(arg2, "%s", tmp.fin->RES);
    tmp = concatq(tmp, creer_bilquad(creer_quad(etiq, "Af",arg1 , arg2, "" )));
    return tmp;
  }
  if (!strcmp(";", n->data)){
    tmp = concatq(tmp, l_c3a(n->gauche));
    tmp = concatq(tmp, l_c3a(n->droit));
    return tmp;
  }
  if(!strcmp("skip", n->data)){
    sprintf(etiq, "%s%d", p[0] , number++ );
    tmp = concatq(tmp, creer_bilquad(creer_quad(etiq, "Sk", "", "","")));
    return tmp;
  }
  if (!strcmp("+", n->data)){
    sprintf(etiq, "%s%d", p[0] , number++ );
    tmp = concatq(tmp, l_c3a(n->gauche));
    sprintf(arg1, "%s", tmp.fin->RES);
    tmp = concatq(tmp, l_c3a(n->droit));
    sprintf(res, "%s%d", p[2], number++);
    sprintf(arg2, "%s", tmp.fin->RES);
    tmp = concatq(tmp, creer_bilquad(creer_quad(etiq, "Pl", arg1, arg2, res)));
    return tmp;
  }
  if (!strcmp("-", n->data)){
    sprintf(etiq, "%s%d", p[0] , number++ );
    tmp = concatq(tmp, l_c3a(n->gauche));
    sprintf(arg1, "%s", tmp.fin->RES);
    tmp = concatq(tmp, l_c3a(n->droit));
    sprintf(res, "%s%d", p[2], number++);
    sprintf(arg2, "%s", tmp.fin->RES);
    tmp = concatq(tmp, creer_bilquad(creer_quad(etiq, "Mo", arg1, arg2, res)));
    return tmp;
  }
  if (!strcmp("*", n->data)){
    sprintf(etiq, "%s%d", p[0] , number++ );
    tmp = concatq(tmp, l_c3a(n->gauche));
    sprintf(arg1, "%s", tmp.fin->RES);
    tmp = concatq(tmp, l_c3a(n->droit));
    sprintf(res, "%s%d", p[2], number++);
    sprintf(arg2, "%s", tmp.fin->RES);
    tmp = concatq(tmp, creer_bilquad(creer_quad(etiq, "Mu", arg1, arg2, res)));
    return tmp;
  }
  if (!strcmp("if", n->data)){
    tmp = concatq(tmp, l_c3a(n->gauche));
    g = concatq(g, l_c3a(n->droit->gauche));
    d = concatq(d, l_c3a(n->droit->droit));
    sprintf(etiq, "%s%d", p[0] , number++ );
    d = concatq(d, creer_bilquad(creer_quad(etiq, "Sk", "", "", "")));
    sprintf(etiq, "%s%d", p[0] , number++ );
    sprintf(arg1,"%s" ,tmp.fin->RES);
    sprintf(res, "%s", d.debut->ETIQ);
    g = concatq(creer_bilquad(creer_quad(etiq, "Jz", arg1,"", res)),g);
    sprintf(etiq, "%s%d", p[0] , number++ );
    sprintf(res, "%s", d.fin->ETIQ);
    d = concatq(creer_bilquad(creer_quad(etiq, "Jp", "","", res)),d);
    tmp = concatq(tmp, g);
    tmp = concatq(tmp,d);
    return tmp;
  }
  if (!strcmp("while", n->data)){
    tmp = concatq(tmp, l_c3a(n->gauche));
    g = concatq(g, l_c3a(n->droit));
    sprintf(etiq, "%s%d", p[0] , number++ );
    sprintf(res, "%s", tmp.debut->ETIQ);
    g = concatq(g, creer_bilquad(creer_quad(etiq, "Jp", "","", res)));
    sprintf(etiq, "%s%d", p[0] , number++ );
    char *e_tmp = strdup(etiq);
    sprintf(arg1, "%s", tmp.fin->RES);
    sprintf(etiq, "%s%d", p[0] , number++ );
    g = concatq(g, creer_bilquad(creer_quad(etiq, "Sk", "", "", "")));
    sprintf(res,"%s" ,g.fin->ETIQ);
    g = concatq(creer_bilquad(creer_quad(e_tmp, "Jz", arg1,"", res)),g);
    tmp = concatq(tmp, g);

    return tmp;
  }
  /* teste si la chaine data est un entier. */
  bool valid = true;
  for (int i = 0; i < strlen(n->data); i++) {
    if (!isdigit(n->data[i])){
      valid = false;
      break;
    }
  }
  if (valid == true){
    sprintf(arg1, "%s", n->data);
    sprintf(etiq ,"%s%d", p[0], number++);
    sprintf(res, "%s%d", p[1], number++);
    tmp = concatq(tmp, creer_bilquad(creer_quad(etiq,"Afc", arg1 , "", res )));
    return tmp;
  }
  if (valid == false){
    sprintf(res, "%s", n->data);
    sprintf(etiq, "%s%d", p[0] , number++);
    tmp = concatq(tmp, creer_bilquad(creer_quad(etiq,"Sk", "" , "", res )));
    return tmp;
  }
  return tmp;
}

char * etiq_fin(){
  char *tmp = malloc(sizeof(char));
  sprintf(tmp, "%s%d", p[0], number);
  return tmp;
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
    /***Jz***/
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
