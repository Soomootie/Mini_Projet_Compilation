CFLAGS = -g -Wall -std=c99
# BISON FLAGS
BFLAGS = -d --report=all
# (F)LEX FLAGS
FFLAGS = -lfl
.l.c:
	flex -o $@ $<

.y.c:
	yacc --file-prefix=$* $(BFLAGS) $<
	mv $*.tab.c $*.c
	mv $*.tab.h $*.h
.c.o:
	gcc -c -o $@ $< $(FFLAGS)
