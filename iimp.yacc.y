%{
/* author BOUTET Clément */
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "include/abiimp.h"
  int yylex();
  int yyerror();

%}

%union{
  struct Noeud * noeud;
  int number;
  char * string;
}

%start START

%token <string> Af Sk If Th El Wh Do Se Pl Mo Mu Po Pf V
%token <number> I

%left Af Mu
%left Pl Mo
%left Do El
%left Se

%type <noeud> C E T F

%%
START : C {print_tree($1);}
C : V Af E { Noeud *fils_gauche = create_noeud(NULL,NULL,$1);
  $$ = create_noeud(fils_gauche, $3, $2);}
  | Sk {$$ = create_noeud(NULL, NULL, $1);}
  | Po C Pf {$$ = create_noeud(NULL, $2, NULL);}
  | If E Th C El C {$$ = create_noeud(NULL, NULL, NULL);}
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
F : Po E Pf {$$ = create_noeud(NULL, NULL, NULL);}
  | I {char *tmp = malloc(sizeof(char)); sprintf(tmp,"%d",$1);
    $$ = create_noeud(NULL,NULL,tmp);}
  | V {$$ = create_noeud($$,NULL,$1);}
  ;
%%

int yyerror(char *s){
  fprintf(stderr,"*** ERROR : %s\n",s);
  return 0;
}

int main(int argc, char **argv){
  /*liste l;*/
  yyparse();
  printf("\nLe programme est correct!\n");
  return 0;
}
