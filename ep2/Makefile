CC=gcc
CFLAGS=-Wall -ansi -O2 -pedantic -pthread

all: ep2 clear

clear:
	rm *.o

ep2: ep2.o corrida.o utilitarios.o
	$(CC) $(CFLAGS) $^ -o $@

ep2.o: ep2.c
	$(CC) $(CFLAGS) $< -c -o $@

corrida.o: corrida.c corrida.h
	$(CC) $(CFLAGS) $< -c -o $@

utilitarios.o: utilitarios.c utilitarios.h
	$(CC) $(CFLAGS) $< -c -o $@


