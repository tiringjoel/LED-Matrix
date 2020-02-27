# Makefile for generating static library

all: main.out

main.out: libmaxdriver.a main.o
	gcc -o main.out main.o -L. -lmaxdriver

main.o:
	gcc -c main.c -o main.o

libmaxdriver.a: BBBiolib.o maxdriver.o
	ar rcs libmaxdriver.a BBBiolib.o maxdriver.o

maxdriver.o:
	gcc -c maxdriver.c -o maxdriver.o

BBBiolib.o:
	gcc -c BBBiolib.c -o BBBiolib.o

clean: 
	rm -rf *o -rf *out -rf *a


