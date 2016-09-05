CC=gcc
CFLAGS=-Wall -ansi -O2 -pedantic
LIBS=-lreadline

all: ep1sh ep1 clear

clear:
	rm *.o

ep1sh: ep1sh.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

ep1: ep1.o process.o queue.o schedule.o
	$(CC) $(CFLAGS) $^ -o $@ 

process.o: process.c process.h
	$(CC) $(CFLAGS) $< -c -o $@

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) $< -c -o $@

schedule.o: schedule.c schedule.h process.h queue.h
	$(CC) $(CFLAGS) $< -c -o $@

