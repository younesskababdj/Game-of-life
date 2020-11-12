#Compilateur

CC = gcc

# Dossiers principaux
RepertoireDesHeaders = include
RepertoireDesObjets = obj
RepertoiredesEx = bin
RepertoireDesSources = src
CPPFLAGS += -I/usr/include/cairo -Iinclude
LDFLAGS += -lcairo -lm -lX11

# Options de compilation
CFLAGS = $(CPPFLAGS) -Wall -g


vpath %.h $(RepertoireDesHeaders)
vpath %.c $(RepertoireDesSources)
vpath %.o $(RepertoireDesObjets)

main: main.o jeu.o io.o grille.o
	@mkdir -p $(RepertoiredesEx)
	$(CC) $(CFLAGS) -o $(RepertoiredesEx)/$@ $(RepertoireDesObjets)/main.o $(RepertoireDesObjets)/jeu.o $(RepertoireDesObjets)/io.o $(RepertoireDesObjets)/grille.o $(LDFLAGS)
	@echo "\n=== Compilation terminée avec succès ==="
	@echo "Lancez le programme avec ./bin/main <numéro de grille>"

%.o: %.c
	@mkdir -p $(RepertoireDesObjets)
	$(CC) $(CFLAGS) -o $(RepertoireDesObjets)/$@ -c $<

dist:
	@mkdir -p dist
	tar -J -cvf dist/FleschBoris-GoL-v0.2.tar.xz grilles include src makefile Doxyfile
	@echo "\n=== Archive créée avec succès ==="


clean:
	rm -f $(RepertoireDesObjets)/*.o
	rm -f $(RepertoiredesEx)/*
	rm -rf dist/
	rm -rf doc/
	@echo "\n=== Artefacts de compilation éliminés avec succès ==="
