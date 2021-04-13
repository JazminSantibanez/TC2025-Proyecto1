CC = gcc
CFLAGS = -g -Wall

final: src/main.c libheaders.so
	gcc src/main.c $(shell pwd)/lib/dynamic/libheaders.so -o bin/main.out

libheaders.so: queries.o
	gcc -shared -o lib/dynamic/libheaders.so lib/dynamic/*.o

queries.o: lib/src/queries.c lib/src/functions.c
	gcc -fPIC -c lib/src/queries.c -o lib/dynamic/queries.o
	gcc -fPIC -c lib/src/functions.c -o lib/dynamic/functions.o

clean:
	rm lib/dynamic/*.o lib/dynamic/*.so bin/main.out