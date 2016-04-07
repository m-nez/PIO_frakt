CC=g++
CFLAGS=-Wall -ggdb
GTK=`pkg-config --cflags --libs gtk+-3.0`

fract: main.o gui.o plane.o renderer.o
	$(CC) $^ -o $@ $(CFLAGS) $(GTK)

main.o: main.cpp
	$(CC) $^ -c $(CFLAGS) $(GTK)

gui.o: gui.cpp
	$(CC) $^ -c $(CFLAGS) $(GTK)

renderer.o: renderer.cpp
	$(CC) $^ -c $(CFLAGS) $(GTK)

plane.o: plane.cpp
	$(CC) $^ -c $(CFLAGS) $(GTK)

.PHONY: clean

clean:
	rm ./*.o
