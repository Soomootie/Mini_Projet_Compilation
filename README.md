# Mini_Projet_Compilation

Projet intermédiaire de Licence 3 Informatique

# Auteur

Clément BOUTET


# FILES

iimp.lex.l, iimp.yacc.y, Makefile,
iC3A.lex.l, iC3A.yacc.y, utils.c, utils.h

# Consignes

Voir le fichier "sujet.pdf"

lancer à la main
make F=iimp && make F=iC3A
./iimp < EXEMPLES/pex1.ip > res.c3a
./iC3A < res.c3a
cat arbre.imp | cat res.c3a | cat test.y86 > final.y86
cat final.y86
