CC             = gcc
CFLAGS         = -Wall -g -std=c99

all: simple newfunctions

simple: ../ringbuffer.c simple.c
	$(CC) $(CFLAGS) -o simple simple.c ../ringbuffer.c

newfunctions: ../ringbuffer.c newfunctions.c
	$(CC) $(CFLAGS) -o newfunctions newfunctions.c ../ringbuffer.c

clean:
	rm -f simple
	rm -f newfunctions
