%{
  #include <stdio.h>
  #include <stdlib.h>
  int yylex();
  int yyerror();
%}
%union{
  int number;
  char * string;
}

%start START
%token <string> Af Sk If Th El Wh Do Se Pl Mo Mu
%token <number> Po Pf
%token <string> V
%token <number> I
%left Af Mu
%left Pl Mo
%right Se Do El
%type <number> C

%%
START : C
C : V Af E {printf("%s %s ", $1, $2);}
  | Sk {printf("%s ", $1);}
  | Po C Pf
  | If E Th C El C {printf("%s%s%s ", $1, $3, $5);}
  | Wh E Do C {printf("%s%s ", $1, $3);}
  | C Se C {printf("%s ",$2);}
  ;
E : E Pl T {printf("%s ",$2);}
  | E Mo T {printf("%s ",$2);}
  | T
  ;
T : T Mu F {printf("* ");}
  | F
  ;
F : Po E Pf
  | I {printf("%d ",$1);}
  | V {printf("%s ",$1);}
  ;
%%
int yyerror(char *s){
  fprintf(stderr,"*** ERROR : %s\n",s);
  exit(0);
  return 0;
}
int main(int argc, char **argv){
  yyparse();
  printf("\nLe programme est correct!\n");
  return 0;
}
