CC = gcc
CFLAGS = -g -Wall

MainF: src/main.c 
	gcc -c queries.

clean:
	rm lib/dynamic/*.o lib/dynaic/*.so bin/dynamic/mainF