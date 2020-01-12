/*
 * LED_Matrix_ATMEGA2560.c
 *
 * Created: 08.01.2020 22:34:29
 * Author : Joel
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "max7219.h"
#include "ledmatrix.h"
#include "max7219ptr.h"


bool mybuffer[ROWLENGTH][COLLENGTH];

int main(void)
{
	max7219ptrtest();
	//initMax();
    while (1) 
    {
		//testfncmatrix();
    }
}

