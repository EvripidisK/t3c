# Nom de l'exécutable final
TARGET = t3c

# Compilateur et options de compilation
CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2 -g
LIBS = -lcrypto

# Liste des fichiers sources (.c)
SRCS = main.c chiffrement.c choixMode.c generation.c trietrecherche.c

# Génération automatique de la liste des fichiers objets (.o)
OBJS = $(SRCS:.c=.o)

# Règle principale (par défaut)
all: $(TARGET)

# Règle pour lier les objets et créer l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Règle générique pour compiler les fichiers .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers temporaires (.o) et de l'exécutable
clean:
	rm -f $(OBJS) $(TARGET)

# Déclaration des cibles factices
.PHONY: all clean

