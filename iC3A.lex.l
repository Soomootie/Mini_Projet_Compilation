%{
  #include <stdio.h>
  #include "iC3A.yacc.h"
%}

OP (Pl|Mo|Mu|Af|Afc|Sk|Jp|Jz|St)
ET [ET]+[0-9]+
DEST [a-zA-Z]*[0-9]*
ARG [+]*[-]*[0-9]*

%%

":" return Sep;
{OP} return Op;
{ET} return Et;
{ARG} return Arg;
{DEST} return Dest;
\n return 1;
. {;}

%%

int yywrap(){
  return -1;
}
