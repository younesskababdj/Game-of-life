#Le compilateur utilisé 
CC = gcc


#Les Flags de compilation 
CFLAGS = -I$(INC_DIR) -Wall

INC_DIR = include
BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
DOC_DIR = doxyfile


main: main.o jeu.o io.o grille.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(OBJ_DIR)/main.o $(OBJ_DIR)/jeu.o $(OBJ_DIR)/io.o $(OBJ_DIR)/grille.o


%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/$@ -c $<


#La cible dist pour créer le tar 
dist:
	@mkdir -p dist
	tar -J -cvf dist/KabbadjYouness-GoL-2.tar.xz  grilles include src makefile Doxyfile 

#La cible clean pour la supression des fichiers inutiles 
clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(BIN_DIR)/*
