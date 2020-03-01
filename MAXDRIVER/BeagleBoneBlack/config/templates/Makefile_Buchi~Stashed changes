#-----------------------
#Makefile
#(c) H.Buchmann FHNW 2018
#we are in work
#-----------------------
VPATH=../src 

TARGET=${PWD}/../target-root/
PREFIX=../tc/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
SYSROOT=${TARGET}
CFLAGS=-std=c99  -march=armv7-a -mfloat-abi=hard -mfpu=vfpv3-d16 -D_POSIX_C_SOURCE=199309L -fpic
CPPFLAGS=-I${TARGET}/usr/include/arm-linux-gnueabihf/
CC=${PREFIX}gcc -O2 --sysroot=${SYSROOT}
LD=${PREFIX}ld 
LDFLAGS=-shared
TARGET_LIB=libmaxdriver.so

#--------------------------- link rule
%:      %.o 
	${LD} \
	--sysroot=${SYSROOT} \
	--build-id \
	--eh-frame-hdr \
	-dynamic-linker /lib/ld-linux-armhf.so.3 \
	-X \
	--hash-style=gnu \
	-m armelf_linux_eabi \
	-o ${@} \
	${SYSROOT}/usr/lib/gcc/arm-linux-gnueabihf/4.9/../../../arm-linux-gnueabihf/crt1.o \
	${SYSROOT}/usr/lib/gcc/arm-linux-gnueabihf/4.9/../../../arm-linux-gnueabihf/crti.o \
	${SYSROOT}/usr/lib/gcc/arm-linux-gnueabihf/4.9/crtbegin.o \
	-L${SYSROOT}/usr/lib/gcc/arm-linux-gnueabihf/4.9 \
	-L${SYSROOT}/usr/lib/gcc/arm-linux-gnueabihf/4.9/../../../arm-linux-gnueabihf \
	-L${SYSROOT}/usr/lib/gcc/arm-linux-gnueabihf/4.9/../../.. \
	-L${SYSROOT}/usr/lib/arm-linux-gnueabihf \
	-L${SYSROOT}/lib/arm-linux-gnueabihf \
	${^} \
	-rpath-link=${SYSROOT}/lib/arm-linux-gnueabihf/ \
	-lstdc++ -lm -lgcc_s -lgcc -lc -lgcc_s -lgcc \
	${SYSROOT}/usr/lib/gcc/arm-linux-gnueabihf/4.9/crtend.o \
	${SYSROOT}/usr/lib/gcc/arm-linux-gnueabihf/4.9/../../../arm-linux-gnueabihf/crtn.o

hello-world-c: hello-world-c.o
hello-world-c.o: hello-world-c.c hello-world-c.o

main.out: libmaxdriver.so main.o
#	gcc -L. -Wl,-rpath=${LIB_PATH} -o main.out main.o -lmaxdriver

main.o:
#	gcc -c main.c -o main.o

libmaxdriver.so: BBBiolib.o maxdriver.o

maxdriver.o: maxdriver.c maxdriver.h
#	gcc -c -o maxdriver.o -fpic -std=c11 maxdriver.c

BBBiolib.o: BBBiolib.c BBBiolib.h
#	gcc -c -o BBBiolib.o -fpic BBBiolib.c

clean:
	rm -rf *.o hello-world-c








