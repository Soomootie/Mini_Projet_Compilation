%{
/* author BOUTET Clément */
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  typedef struct imp{
    char *name;
    int value;
  }imp;

  typedef struct liste{
    struct imp i;
    struct liste* suivant;
  }liste;

  typedef liste *Liste;
  Liste l;
  int yylex();
  int yyerror();
  imp create_imp(Liste, char*, int);
  imp search(Liste , char *);
%}

%union{
  int number;
  char * string;
}

%start START

%token <string> Af Sk If Th El Wh Do Se Pl Mo Mu Po Pf
%token <string> V
%token <number> I

%left Af Mu
%left Pl Mo
%right Se Do El

%type <number> C
%type <string> E T
%type <string> F

%%
START : C
C : V Af E {printf("%s %s ", $1, $2);/* liste l */}
  | Sk {printf("%s ", $1);}
  | Po C Pf {printf("%s %s",$1 , $3);}
  | If E Th C El C {printf("%s%s%s ", $1, $3, $5);}
  | Wh E Do C {printf("%s%s ", $1, $3);}
  | C Se C {printf("%s ",$2);}
  ;
E : E Pl T {printf("%s ",$2);}
  | E Mo T {printf("%s ",$2);}
  | T
  ;
T : T Mu F {printf("%s ",$2);}
  | F
  ;
F : Po E Pf
  | I {printf("%d ",$1);}
  | V {printf("%s ",$1); $$ = $1;}
  ;
%%



imp search(Liste i, char *name){
  Liste tmp_i = i;
  while (tmp_i != NULL){
    if (!strcmp(name, tmp_i->i.name))
      return tmp_i->i;
    tmp_i = tmp_i->suivant;
  }
  return tmp_i->i;
}

imp create_imp(Liste i, char *name, int value){
  imp tmp_i ;
  tmp_i = search(i, name);
  if (strcmp(tmp_i.name,name)){
    tmp_i.name = strdup(name);
    tmp_i.value = value;
  } else {
    tmp_i.value = value;
  }
  return tmp_i;
}



int yyerror(char *s){
  fprintf(stderr,"*** ERROR : %s\n",s);
  exit(0);
  return 0;
}

int main(int argc, char **argv){
  liste l;
  yyparse();
  printf("\nLe programme est correct!\n");
  return 0;
}
