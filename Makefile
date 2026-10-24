TARGET = t3c

CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2 -g
LIBS = -lcrypto

SRCS = src/main.c src/chiffrement.c src/choixMode.c src/generation.c src/trietrecherche.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -Isrc -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
