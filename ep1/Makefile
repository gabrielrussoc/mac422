CC=gcc
CFLAGS=-Wall -ansi -O2 -pedantic -pthread
LIBS=-lreadline

all: ep1sh ep1 clear

clear:
	rm *.o

ep1sh: ep1sh.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

ep1: ep1.o process.o queue.o schedule.o utility.o heap.o
	$(CC) $(CFLAGS) $^ -o $@ 

process.o: process.c process.h
	$(CC) $(CFLAGS) $< -c -o $@

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) $< -c -o $@

schedule.o: schedule.c schedule.h process.h queue.h
	$(CC) $(CFLAGS) $< -c -o $@

utility.o: utility.c utility.h queue.h heap.h
	$(CC) $(CFLAGS) $< -c -o $@

heap.o: heap.c heap.h process.h
	$(CC) $(CFLAGS) $< -c -o $@
