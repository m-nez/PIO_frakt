CC=g++ -std=c++11
CFLAGS=-ggdb -Wall
BUILD_DIR=../build
INCLUDE_DIR=../include
LIBS=-lgtest -lfract -lgtest_main
GTK = `pkg-config --cflags --libs gtk+-3.0`
TESTS:=$(wildcard ./*.cpp) #All cpp files in test directory must be tests

default: run

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $*.o -I $(INCLUDE_DIR) -L $(BUILD_DIR) $(LIBS) $(GTK)

test: $(TESTS:.cpp=.o)
	$(CC) -Wl,-rpath=$(BUILD_DIR) $^ -L$(BUILD_DIR) $(LIBS) $(GTK) \
		-I $(INCLUDE_DIR) -o $@

.PHONY: run

run: test
	./test

.PHONY: clean

clean:
	rm -f ./*.o
