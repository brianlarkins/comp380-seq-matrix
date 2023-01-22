all: lab1

CC=gcc
CFLAGS=-g

lab1: lab1.o wctimer.o
	$(CC) -o $@ $^ -lm

clean:
	rm -f *.o lab1
