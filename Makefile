CC = gcc
CFLAGS = -g -Wall -std=c99
# (F)LEX FLAGS
LFLAGS = -lfl
# YACC FLAGS
YFLAGS = -d --report=all
# .H FILES
INC_DIR = include

run:
ifneq ($(F),)
	@$(MAKE) -s $(F)
endif

.c.o:
	@$(CC) -c -o $@ $<

.l.c:
	@echo -e "\033[32;02mCompiling flex file:" $^ "\033[00m"
	@echo -e "\033[32;02mOutput file:" $@ "\033[00m\033[34;01m"
	@flex -o $@ $^
	@echo -e "\033[00m"

.y.c:
	@echo -e "\n\033[32;02mCompiling yacc file:" $^ "\033[00m"
	@echo -e "\033[32;02mOutput file:" $@ "\033[00m\033[34;01m"
	@yacc -o $(F).c $(YFLAGS) $<
	@mv $(F).h $*.h
	@mv $(F).c $@
	@echo -e "\033[00m"

$(F): $(F).yacc.o $(F).lex.o abiimp.o
	@echo -e "\033[32;02mCompiling output file:" $^ "\033[00m"
	@echo -e "\033[32;02mOutput file:" $@ "\033[00m\033[34;01m"
	@$(CC) -o $@ $^

exe:
ifneq ($(F),)
	@$(MAKE) -s $(F)
	@read -p "Entrez un fichier pour lancer l'éxécutable : " file;\
	if [ "$$file" != "" ] ; then clear ; echo -n $$(cat $$file) | ./$(F).exe;fi
else
	@echo -e "\033[36;02mVeulliez saisir : make F=<executable> exe\033[00m"
endif

clean:
	@rm -f *.exe *.o *.output *.dot *.png *.yacc.h
