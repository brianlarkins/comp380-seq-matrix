all: lab1

lab1: lab1.o timer.o
	$(CC) -o $@ $^ -lm
