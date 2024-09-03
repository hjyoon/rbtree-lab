CC = gcc
CFLAGS = -Wall -Wextra

all: helloworld

helloworld: main.o
	$(CC) $(CFLAGS) -o main main.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f main *.o