CC=gcc
CFLAGS=-Wall -Wextra -Os
BINDIR=/usr/bin

0d1n: 0d1n.c 
	$(CC) $(CFLAGS) -g -c *.c 
	$(CC) $(CFLAGS) -g -o 0d1n *.o -lcurl -Os 
	rm *.o

clean:
	rm 0d1n
