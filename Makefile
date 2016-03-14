CC=g++
CFLAGS=-Wall

main: plane.o bmp.o functions.o main.o
	$(CC) $^ -o $@ $(CFLAGS)

.PHONY: clean

clean:
	rm ./*.o
