# Makefile for generating dynamic library (shared object)
# NOTE: change LIB_PATH to your current working directory

#LIB_PATH = /home/joel/Desktop/BeagleBone/development/BBBio_lib/dynVersion	# Ubuntu
#LIB_PATH = /home/debian/Desktop/development/BBBio_lib/dynVersion		# BBB
LIB_PATH = /home/debian/Desktop/work/test_PyWrap				# BB_Green

all: main.out

main.out: libmaxdriver.so main.o
	gcc -L. -Wl,-rpath=${LIB_PATH} -o main.out main.o -lmaxdriver

main.o:
	gcc -c main.c -o main.o

libmaxdriver.so: BBBiolib.o maxdriver.o
	gcc -shared -o libmaxdriver.so maxdriver.o BBBiolib.o

maxdriver.o:
	gcc -c -o maxdriver.o -fpic -std=c11 maxdriver.c

BBBiolib.o: BBBiolib.c
	gcc -c -o BBBiolib.o -fpic BBBiolib.c

clean: 
	rm -rf *o -rf *out -rf *a


