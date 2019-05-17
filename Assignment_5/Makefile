CC=gcc
CFLAGS=-fsanitize=address -fsanitize=undefined -Wall -Wextra -Wshadow -g

all: sfrobu new

new: new.c
	$(CC) -o new new.c $(CFLAGS)

sfrobu: sfrobu.c
	$(CC) -o sfrobu sfrobu.c $(CFLAGS)

clean:
	rm sfrobu -f

