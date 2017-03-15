%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include "include/utils.h"
    int yylex();
    int yyerror();
    bool is_create = false;
%}

%code requires {
  #include "include/bilquad.h"
}

%union{
  int number;
  char *string;
  BILQUAD bq;
}

%start START

%token <string> Et Sep Arg Dest Op NLINE

%type <bq> C
%type <string> A D


%%

START : C {ecrire_bilquad($1);
    c3a_y86($1);
      }
C : Et Sep Op Sep A Sep A Sep D NLINE C
  { QUAD qd = creer_quad($1, $3, $5, $7, $9);
      $$ = creer_bilquad(qd);
      $$ = concatq($$, $11);
  }
  |  {$$ = bilquad_vide();}
A : Arg
  | Dest
  | {$$ = "";}
D : Dest
  | Et
  |{$$ = "";}
  ;

%%


int yyerror(char *s){
  fprintf(stderr,"*** ERROR : %s\n",s);
  return 0;
}

int main(int argc, char **argv){
  yyparse();
  return 0;
}
