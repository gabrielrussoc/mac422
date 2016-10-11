CC=gcc-6
CFLAGS=-Wall -ansi -O2 -pedantic -pthread

all: corrida clear

clear:
	rm *.o

corrida: corrida.o atleta.o utilitarios.o
	$(CC) $(CFLAGS) $^ -o $@ 

corrida.o: corrida.c
	$(CC) $(CFLAGS) $< -c -o $@

atleta.o: atleta.c atleta.h
	$(CC) $(CFLAGS) $< -c -o $@

utilitarios.o: utilitarios.c utilitarios.h
	$(CC) $(CFLAGS) $< -c -o $@


