CC=g++
CFLAGS=-Wall

main: plane.o bmp.o functions.o main.o
	$(CC) $^ -o $@

.PHONY: clean

clean:
	rm ./*.o
