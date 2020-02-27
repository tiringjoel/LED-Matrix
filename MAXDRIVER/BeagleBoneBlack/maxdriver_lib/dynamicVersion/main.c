
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "BBBiolib.h"
#include "maxdriver.h"

S_MAX mymax;

int main(void)
{
	printf("main routine started..\n");
	initMax(&mymax, 8, 12, 13, 14, 4);
	("Max intialized..\n");
	uint8_t connector = 8;
	uint8_t pin = 12;
	int del;
	iolib_init();
	iolib_setdir(8,11, BBBIO_DIR_IN);
	iolib_setdir(connector,pin, BBBIO_DIR_OUT);
	printf("Direction set...\n");

	int count = 0;
	while(count < 50)
	{
		count ++ ;
		if (is_high(connector,pin))
		{
			del=100; // fast speed
		}
		if (is_low(connector,pin))
		{
			del=500; // slow speed
		}

		pin_high(connector,pin);
		iolib_delay_ms(del);
		pin_low(connector,pin);
		iolib_delay_ms(del);
		printf("Pin written...\n");

	}
	iolib_free();
	return(0);
}


