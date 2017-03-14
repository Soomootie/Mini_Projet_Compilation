%{
 #include <stdio.h>
 #include "iimp.yacc.h"
%}

%%
"(" yylval.string = strdup(yytext); return Po;
")" yylval.string = strdup(yytext); return Pf;
":=" yylval.string = strdup(yytext); return Af;
"skip" yylval.string = strdup(yytext); return Sk;
"if" yylval.string = strdup(yytext); return If;
"then" yylval.string = strdup(yytext); return Th;
"else" yylval.string = strdup(yytext); return El;
"while" yylval.string = strdup(yytext); return Wh;
"do" yylval.string = strdup(yytext); return Do;
";" yylval.string = strdup(yytext); return Se;
"+" yylval.string = strdup(yytext); return Pl;
"-" yylval.string = strdup(yytext); return Mo;
"*" yylval.string = strdup(yytext); return Mu;
[1-9]+[0-9]* yylval.number = atoi(yytext); return I;
[a-zA-Z]+[0-9]* yylval.string = strdup(yytext); return V;
.|\n ;

%%

int yywrap(){
  return -1;
}
