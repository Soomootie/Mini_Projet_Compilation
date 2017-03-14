/* arbre.c */
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/bilquad.h"
#include "include/environ.h"
/*-------------------------------------------------------------------*/
/* ----------------------------types---------------------------------*/
/* QUAD,BILQUAD: definis dans bilquad.h                              */
/*-------------------------------------------------------------------*/
/*---------------------quadruplets-----------------------------------*/

/* retourne un quadruplet (avec etiquette etiq) */
QUAD creer_quad(char *etiq,char *op,char *arg1,char *arg2,char *res)
{QUAD qd;int lres;
  qd=(struct cellquad *)malloc(sizeof(struct cellquad));
  if (etiq !=NULL)
    {qd->ETIQ=Idalloc();
      strcpy(qd->ETIQ,etiq);}
  if (op !=NULL)
    {qd->OP=Idalloc();
      strcpy(qd->OP,op);}
  if (arg1 !=NULL)
    {qd->ARG1=Idalloc();
      strcpy(qd->ARG1,arg1);}
  if (arg2 !=NULL)
    {qd->ARG2=Idalloc();
      strcpy(qd->ARG2, arg2);}
  if (res!= NULL)
    {lres=strlen(res);
      qd->RES=(char *)malloc(lres*sizeof(char));
      strcpy(qd->RES,res);}
  return(qd);
}

/* retourne une biliste vide  */
BILQUAD bilquad_vide()
{BILQUAD bq;
  bq.debut=NULL;bq.fin=NULL;
  return(bq);
}

/* retourne une biliste a un element  */
BILQUAD creer_bilquad(QUAD qd)
{BILQUAD bq;
  bq.debut=qd;bq.fin=qd;
  return(bq);
}

/* fonction aux  pour la fonction rechbq */
QUAD rechq(char *chaine, QUAD qd)
{QUAD qcour;
  qcour=qd;
  if (qcour!=NULL)
    {if (strcmp(qcour->ETIQ,chaine)==0)
        return qcour;
      else
	return rechq(chaine,qcour->SUIV);
    }
  else
    return NULL;
}

/*retourne le quad etiquete par chaine, NULL s'il n'y en a pas */
QUAD rechbq(char *chaine, BILQUAD bq)
{return(rechq(chaine,bq.debut));}


BILQUAD concatq(BILQUAD bq1, BILQUAD bq2)
/* retourne la concatenation; ne detruit pas bqi; ne copie pas *bqi */
/* peut creer une boucle ! */
{BILQUAD bq;
  if (bq1.fin!= NULL)
    if (bq2.debut!=NULL)
       { bq1.fin->SUIV=bq2.debut;
        bq.debut=bq1.debut;
        bq.fin=bq2.fin;
        return(bq);}
    else
      return(bq1);
  else
    return(bq2);
}

/* traduit entier (= codop) vers chaine (= nom operation)  */
/* les codes d'op sont definis dans environ.h              */
/*
char *nomop(int codop)
{switch(codop)
    {case(Af): printf("%d", codop);return("Af");
    case(Sk): printf("%d", codop);return("Sk");
    case(Pl): printf("%d", codop);return("Pl");
    case(Mo): printf("%d", codop);return("Mo");
    case(Mu): printf("%d", codop);return("Mu");
    case(Afc): printf("%d", codop);return("Afc");
    case(St): printf("%d", codop);return("St");
    case(Jp): printf("%d", codop);return("Jp");
    case(Jz): printf("%d", codop);return("Jz");
    default:printf("%d", codop);return(NULL);
    };
}*/

/* affiche le quadruplet (pour generer code); puis saute a la ligne */
void ecrire_quad(QUAD qd)
{ if(strcmp(qd->ETIQ,"") == 0)       /* etiquette= mot vide */
    {printf("%-10s:","");}
  else
    {printf("%-10s:",qd->ETIQ);}
  if (qd->OP != NULL){
    printf("%-6s",qd->OP);
  }
    printf("%-6s:","");
  if (qd->ARG1!=NULL)
    {printf("%-10s:",qd->ARG1);}
  else
    {printf("%-10s:","");}
  if (qd->ARG2!=NULL)
    {printf("%-10s:",qd->ARG2);}
  else
    {printf("%-10s:","");}
  if (qd->RES!=NULL)
    {printf("%-10s\n",qd->RES);}
  else
    {printf("\n");}
  }

/* affiche la biliste de quad */
void ecrire_bilquad(BILQUAD bq)
{QUAD qcour;
  qcour=bq.debut;
  QUAD tmp = qcour - 0x100000d;
  while(qcour!=NULL)
    {
  if (qcour < tmp){
    break;
  }
	ecrire_quad(qcour);
      qcour=qcour->SUIV;}
}
