%{
#include "lexemes.h"
/*#include "iimp.h"*/

%}

%%

[1-9]+[0-9]* {return(I);}
"ertyu" /* Il manque ici le symbole V représentant un identificateur de variable */
":=" {return(Af);}
"Skip" {return(Sk);}
";" {return (Se);}
(if) {return(If);}
(then) {return(Th);}
(else) {return(El);}
(while) {return(Wh);}
(do) {return(Do);}
"+" {return(Pl);}
"-" {return(Mo);}
"*" {return(Mu);}
\  ;

%%
