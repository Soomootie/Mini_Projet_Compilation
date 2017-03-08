%{
    #include <stdio.h>
    #include <stdlib.h>
    int yylex();
    int yyerror();
%}

%union{
  int number;
  char *string;
}

%start START

%token <string> Et Sep Op Arg Dest

%type <string> C A

%%

START : C {printf("%s ",$1);}
C :
  | Et Sep Op Sep A Sep A Sep D C
A :
  | Arg
  | Dest
D :
  | Dest
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
