CC=g++

all: build clearafter

build: main.o
	$(CC) main.o -o main

main.o: 
	$(CC) -c main.cpp -o main.o -Wall

#Clear temporary files after compiling
clearafter:
	#Option -r: Remove recursive and
	#Option -f: ignore nonexistent files, never prompt
	rm -rf *.o
	rm -rf *~ #Remove temporary files

clean: clearafter
	rm -f main

clear: clearafter
	rm -f main
