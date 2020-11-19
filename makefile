#Compilateur
CC = gcc

# Dossiers principaux
RepertoiresDesHeaders = include
ReperoireDesObjets = obj
RepertoireDesEx = bin
RepertoireDesSources = src
RepertoireDesLib = lib
CPPFLAGS = -I/usr/include/cairo -Iinclude
LDFLAGS = -lcairo -lm -lX11 -ljeu -L lib/
MODE=CAIROGUI

# Options de compilation
CFLAGS = $(CPPFLAGS) -Wall -g


vpath %.h $(RepertoiresDesHeaders)
vpath %.c $(RepertoireDesSources)
vpath %.o $(ReperoireDesObjets)

main: main.o jeu.o io.o grille.o
	@mkdir -p $(RepertoireDesEx)
	@mkdir -p $(RepertoireDesLib)

	ar -crv $(RepertoireDesLib)/libjeu.a $(ReperoireDesObjets)/jeu.o $(ReperoireDesObjets)/grille.o
	ranlib $(RepertoireDesLib)/libjeu.a

	$(CC) -DMODE$(MODE) $(CFLAGS) -o $(RepertoireDesEx)/$@ $(ReperoireDesObjets)/main.o $(ReperoireDesObjets)/jeu.o $(ReperoireDesObjets)/io.o $(ReperoireDesObjets)/grille.o $(LDFLAGS)
	@echo "\n=== Compilation terminée avec succès ==="
	@echo "Lancez le programme avec ./bin/main <numéro de grille>"

%.o: %.c
	@mkdir -p $(ReperoireDesObjets)
	$(CC) -DMODE$(MODE) $(CFLAGS) -o $(ReperoireDesObjets)/$@ -c $<

dist:
	@mkdir -p dist
	tar -J -cvf dist/gameoflife_KABBADJ_Youness.tar.xz grilles include src makefile Doxyfile
	@echo "\n=== Archive créée avec succès (-_-) ==="
	


clean:
	rm -f $(ReperoireDesObjets)/*.o
	rm -f $(RepertoireDesEx)/*
	rm -f $(RepertoireDesLib)/*.a
	rm -rf dist/
	rm -rf doc/
	@echo "\n=== Artefacts de compilation éliminés avec succès ==="

