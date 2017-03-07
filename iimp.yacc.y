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
    struct imp iimp;
    struct liste* suivant;
  }liste;

  typedef liste* List;
  List l;
  imp _imp;

  int yylex();
  int yyerror();
  imp create_imp(List, char*, int);
  imp search(List , char *);
  List add_to_list(List, imp);
  void print_list(List);

%}

%union{
  struct liste* u_liste;
  int number;
  char * string;
}

%start START

%token <string> Af Sk If Th El Wh Do Se Pl Mo Mu Po Pf V
%token <number> I

%left Af Mu
%left Pl Mo
%right Se Do El

%type <u_liste> C E T F

%%
START : C {printf("Environnement:\n");print_list(l);}
C : V Af E {_imp = create_imp(l,$1,$3->iimp.value);
  l = add_to_list(l, _imp);}
  | Sk {printf("%s ", $1);}
  | Po C Pf {printf("%s %s",$1 , $3);}
  | If E Th C El C {printf("%s%s%s ", $1, $3, $5);}
  | Wh E Do C {printf("%s%s ", $1, $3);}
  | C Se C {;}
  ;
E : E Pl T {_imp = create_imp(l," ",$3->iimp.value + $1->iimp.value);
    $$ = add_to_list(l, _imp);}
  | E Mo T {_imp = create_imp(l, " ",$1->iimp.value - $3->iimp.value);
    $$ = add_to_list(l, _imp);}
  | T
  ;
T : T Mu F {_imp = create_imp(l, " ",$1->iimp.value * $3->iimp.value);
    $$ = add_to_list(l, _imp);}
  | F
  ;
F : Po E Pf {$$ = add_to_list(l,_imp);}
  | I {_imp = create_imp(l, " ", $1);
    $$ = add_to_list(l,_imp);}
  | V {if (l != NULL){
      _imp = create_imp(l, $1 ,l->iimp.value);
      $$ = add_to_list(l, _imp);
    } else {
      yyerror($1);
    }
  }
  ;
%%



imp search(List i, char *name){
  List tmp_l = i;
  imp tmp_i;
  while (tmp_l != NULL){
    /*printf("\n%s\n",tmp_l->iimp.name);*/
    if (!strcmp(name, tmp_l->iimp.name))
      return tmp_l->iimp;
    tmp_l = tmp_l->suivant;
  }
  return tmp_i;
}

imp create_imp(List l, char *name, int value){
  imp tmp_i ;
  tmp_i = search(l, name);
  if (tmp_i.name == NULL){
    tmp_i.name = strdup(name);
    tmp_i.value = value;
  } else {
    tmp_i.value = value;
  }
  return tmp_i;
}

List add_to_list(List l, imp i){
  List tmp_l = malloc(sizeof(List));
  tmp_l->iimp = i;
  tmp_l->suivant = l;
  return tmp_l;
}

void print_list(List l){
  List tmp_l = l;
  while (tmp_l != NULL){
    printf("La variable %s vaut %d\n", tmp_l->iimp.name, tmp_l->iimp.value);
    tmp_l = tmp_l->suivant;
  }
}

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
