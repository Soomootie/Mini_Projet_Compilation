%{
/* author BOUTET Clément */
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  int yylex();
  int yyerror();
  FILE *fd;
%}

%code requires {
  #include "include/utils.h"
  #include "include/environ.h"
}

%union{
  Noeud * noeud;
  int number;
  char * string;
}

%start START

%token <string> Af Sk If Th El Wh Do Se Pl Mo Mu Po Pf V
%token <number> I

%left Af Mu
%left Pl Mo
%left El
%left Se Do

%type <noeud> C E T F

%%
START : C {
          fprintf(fd, "\nArbre de syntaxe abstraite: \n");
          print_tree($1, fd);
          fprintf(fd, "\n\n");
          BILQUAD qd = bilquad_vide();
          qd = concatq(qd, imp_c3a($1));
          qd = concatq(qd, creer_bilquad(creer_quad(etiq_fin(), "St", "","","")));
          ecrire_bilquad(qd);}
C : V Af E { Noeud *fils_gauche = create_noeud(NULL,NULL,$1);
  $$ = create_noeud(fils_gauche, $3, $2);}
  | Sk {$$ = create_noeud(NULL, NULL, $1);}
  | Po C Pf {
    $$ = $2;}
  | If E Th C El C {
    Noeud *fils_droit = create_noeud($4, $6, "");
    $$ = create_noeud($2, fils_droit, $1);}
  | Wh E Do C {$$ = create_noeud($2, $4, $1);}
  | C Se C {$$ = create_noeud($1, $3, $2);}
  ;
E : E Pl T {$$ = create_noeud($1, $3 , $2);}
  | E Mo T {$$ = create_noeud($1, $3, $2);}
  | T
  ;
T : T Mu F {$$ = create_noeud($1, $3, $2);}
  | F
  ;
F : Po E Pf {$$ =$2;}
  | I {char *tmp = malloc(sizeof(char)); sprintf(tmp,"%d",$1);
    $$ = create_noeud(NULL,NULL,tmp);}
  | V {$$ = create_noeud(NULL,NULL,$1);}
  ;
%%

int yyerror(char *s){
  fprintf(stderr,"*** ERROR : %s\n",s);
  return 0;
}

int main(int argc, char **argv){
  fd = fopen("arbre.imp", "w");
  yyparse();
  return 0;
}
