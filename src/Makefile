CC=g++
CFLAGS=-Wall -ggdb -fPIC
GTK=`pkg-config --cflags --libs gtk+-3.0`

CLASSES=window.o \
		renderer.o \
		plane.o \
		gui.o
		
default: fractal

libfract.so.1.0: $(CLASSES)
	$(CC) -shared -Wl,-soname,libfract.so.1 \
		-o $@ $(CLASSES) $(GTK)
	ln -sf $@ libfract.so.1
	ln -sf $@ libfract.so

fractal: libfract.so.1.0
	$(CC) main.o -Wl,-rpath=./ -L./ -lfract $(CFLAGS) -o $@ $(GTK)

fractal_static: main.o gui.o plane.o renderer.o window.o
	$(CC) $^ -o $@ $(CFLAGS) $(GTK)

main.o: main.cpp
	$(CC) $^ -c $(CFLAGS) $(GTK)

gui.o: gui.cpp
	$(CC) $^ -c $(CFLAGS) $(GTK)

renderer.o: renderer.cpp
	$(CC) $^ -c $(CFLAGS) $(GTK)

plane.o: plane.cpp
	$(CC) $^ -c $(CFLAGS) $(GTK)

window.o: window.cpp
	$(CC) $^ -c $(CFLAGS) $(GTK)

clean:
	rm -f ./*.o
