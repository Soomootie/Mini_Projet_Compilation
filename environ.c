/* environ.c */
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/environ.h"
#include "iimp.yacc.h"
/*---------------------allocation memoire----------------------------*/
char *Idalloc()
{
  return((char *)malloc(MAXIDENT*sizeof(char)));
}

ENV Envalloc()
{
  return((ENV)malloc(sizeof(struct cellenv)));
}

/*-------------------------------------------------------------------*/
/*-----------------------------environnements------------------------*/

/* initialise l'environnement *prho par  var=0    */
/* la chaine var est copiee dans l' environnement */
int initenv(ENV *prho,char *var)
{ENV pos, newcell;
  pos=rech(var,*prho);/* adresse de la cellule contenant var */
  if (pos == NULL)
    /*on insere var en tete de envrnt*/
    { newcell=Envalloc();
      newcell->ID=Idalloc();
      strcpy(newcell->ID,var);
      newcell->VAL=0;
      newcell->SUIV=*prho;
      *prho=newcell;
      return (EXIT_SUCCESS);
    }
  else
    {
      return(EXIT_SUCCESS);
    }
}

// trois type , 0, 1, 2
int initenv_int(ENV *prho, char *var, int type){
  ENV pos, newcell;
  pos = rech(var, *prho);
  if (pos == NULL){
    newcell = Envalloc();
    newcell->ID = Idalloc();
    strcpy(newcell->ID, var);
    newcell->TYPE = type;
    newcell->VAL = 0;
    ENV tmp = *prho;
    ENV tmp_suiv = tmp->SUIV;
    if (tmp_suiv != NULL){
      if (type == 2){
        printf("%s %d\n",var , type );
        while (tmp_suiv->SUIV != NULL){
          tmp = tmp_suiv;
          tmp_suiv = tmp_suiv->SUIV;
        }
      } else if (type == 1){
        printf("%s %d\n",var , type );
        while (tmp_suiv->SUIV != NULL && tmp_suiv->TYPE <= 1){
          tmp = tmp_suiv;
          tmp_suiv = tmp_suiv->SUIV;
        }
      } else if (type == 0){
        printf("%s %d\n",var , type );
        while (tmp_suiv != NULL && tmp_suiv->TYPE <= 0){
          tmp = tmp->SUIV;
          tmp_suiv = tmp_suiv->SUIV;
        }
      }
      tmp->SUIV = newcell;
      newcell->SUIV = tmp_suiv;
      return EXIT_SUCCESS;
    } else {
      initenv(prho, var);
    }
  return EXIT_SUCCESS;
  }
}

/* retourne (arg1 op arg2) */
int eval(char *op, int arg1, int arg2){
  int tmp_op;
  if (!strcmp(op, "Pl"))
    tmp_op = Pl;
  if (!strcmp(op, "Mo"))
    tmp_op = Mo;
  if (!strcmp(op, "Mu"))
    tmp_op = Mu;
  switch(tmp_op){
    case Pl:
      return(arg1 + arg2);
    case Mo:
      return(arg1 - arg2);
    case Mu:
      return(arg1 * arg2);
    default:
      return(0);
  }
  return(0);
}

/* retourne l'adresse de la cellule contenant chaine. NULL si la chaine est absente */
ENV rech(char *chaine, ENV listident){
  if (listident!=NULL){
    if (listident->ID && strcmp(listident->ID,chaine)==0){
      return listident;
    } else {
	    return rech(chaine,listident->SUIV);
    }
  } else
    return NULL;
}

/* affecte val a la variable var , dans rho */
int affect(ENV rho, char *var, int val)
{ENV pos;
  pos=rech(var,rho);/* adresse de la cellule contenant var */
  if (pos != NULL)
    {(pos->VAL)=val;
      return(EXIT_SUCCESS);
    }
  else
    return(EXIT_FAILURE);
}

/* affiche l'environnement */
int ecrire_env(ENV rho)
{ if (rho==NULL)
    {printf("fin d' environnement \n");
      return(EXIT_SUCCESS);}
  else
    {
      if (rho->ID != NULL)
        printf("variable %s valeur %d \n",rho->ID,rho->VAL);
      ecrire_env(rho->SUIV);
      return(EXIT_SUCCESS);
    };
}

/* valeur de var dans rho */
int valch(ENV rho, char *var)
{ENV pos;
  pos=rech(var,rho);/* adresse de la cellule contenant var */
  if (pos != NULL)
    return(pos->VAL);
  else
    return(0);
}
