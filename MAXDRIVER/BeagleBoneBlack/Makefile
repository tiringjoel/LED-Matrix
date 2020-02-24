CC = gcc -fPIC -shared
CFLAGS = -c -Wall
LIB = -liobb

all: bbbmaxdriver.so

bbbmaxdriver.so: maxdriver.o
	$(CC) maxdriver.o $(LIB) -o bbbmaxdriver.so

maxdriver.o: maxdriver.c
	$(CC) $(CFLAGS) maxdriver.c

clean: 
	rm -rf *o bbbmaxdriver


