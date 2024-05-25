CC = gcc
CFLAGS = -Wall -Wextra -std=c11

OBJS = main.o manager.o festivalier.o concert.o salle.o utils.o

all: main

main: $(OBJS)
		$(CC) $(CFLAGS) -o main $(OBJS) -lncurses

main.o: main.c manager.h festivalier.h
manager.o: manager.c manager.h salle.h concert.h
festivalier.o: festivalier.c festivalier.h concert.h salle.h
concert.o: concert.c concert.h salle.h
salle.o: salle.c salle.h
utils.o: utils.c utils.h

clean:
		rm -f *.o main
