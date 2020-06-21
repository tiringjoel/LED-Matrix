
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "BBBiolib.h"
#include "maxdriver.h"

S_MAX mymax;

int main(void)
{
	printf("main routine started..\n");
	uint8_t connector = 8;
	uint8_t pin = 14;
	int del = 999;
	iolib_init();
	//iolib_setdir(connector,pin, BBBIO_DIR_IN);
	iolib_setdir(connector,pin, BBBIO_DIR_OUT);
	printf("Direction set...\n");

	pin_high(connector,pin);
	printf("Pin high...\n");
	iolib_delay_ms(del);
	iolib_delay_ms(del);
	iolib_delay_ms(del);
	iolib_delay_ms(del);
	iolib_delay_ms(del);
	pin_low(connector,pin);
	printf("Pin low...\n");
	iolib_free();
	printf("freed Pin...\n");
	return(0);
}


