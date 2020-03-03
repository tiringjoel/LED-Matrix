CC = gcc -fPIC -shared
CFLAGS = -c -Wall
LD_LIBRARY_PATH = /home/joel/Desktop/BeagleBone/development/BBBio_lib/dynVersion/BBBiolib

all: libmaxdriver.so

libmaxdriver.so: maxdriver.o BBBiolib.o
	gcc -shared -o libmaxdriver.so maxdriver.o BBBiolib.o

maxdriver.o: maxdriver.c
	gcc -c -o maxdriver.o -fpic maxdriver.c 

BBBiolib.o: BBBiolib.c
	gcc -c -o BBBiolib.o -fpic BBBiolib.c

#libmaxdriver.so: maxdriver.o
#	$(CC) maxdriver.o $(LIB) -o libmaxdriver.so

#maxdriver.o: maxdriver.c
#	$(CC) $(CFLAGS) maxdriver.c

# Holzer stuff

#libmaxdriver.so: maxdriver.o
#	$(CC) maxdriver.o $(LIB) -o libmaxdriver.so

#maxdriver.so: maxdriver.c maxdriver.h
#	$(CC) $(CFLAGS) maxdriver.c

clean: 
	rm -rf *o libmaxdriver


