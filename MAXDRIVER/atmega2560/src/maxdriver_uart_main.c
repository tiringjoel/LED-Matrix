/*
 * maxdriver_uart_main.c
 *
 * Created: 20.06.2020 11:29:07
 *  Author: Joel
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include "usart.h"
#include "maxdriver.h"

#define CLKPIN					(0)
#define CSPIN					(1)
#define DATAPIN					(2)
#define NRMAX					(4)
#define ROWLENGTH				(8)
#define COLLENGTH				(32)
#define BUFF_SIZE				(25)

S_MAX mymax;

void init_io(void){
	// init max
	DDRC = (1<<DDC0) + (1<<DDC1) + (1<<DDC2);
	initMax(&mymax,&PORTC,CLKPIN,CSPIN,DATAPIN,NRMAX);
	
	// init uart
	uart_init(BAUD_CALC(9600));
	stdout = &uart0_io;
	stdin = &uart0_io;
	sei();
	uart_puts("hello from maxdriver\r\n");
}

void fillBuffer(uint8_t* buf, uint8_t* data, uint8_t* position)
{
	for (uint8_t i=0; i<8; i++)
	{
		*(buf + *(position) + i) = *data & (1<<i);
	}
	*(position) += 8;
	uart_puts("Position: ");
	uart_putint(*(position));
	uart_puts("\r\n");
}

int main(void)
{
	init_io();
	
	uint8_t ledbuf[ROWLENGTH][COLLENGTH];
	uint8_t data = 0;
	uint8_t writepos = 0;
	
	// empty buffer
	for (uint16_t i=0; i<256; i++)
	{
		*(&ledbuf[0][0] + i) = 0;
	}
	shiftBufferOut(&mymax,&ledbuf[0][0]);
	
	while(1)
	{
		if (uart_AvailableBytes())
		{
			data = uart_getint();
			uart_putint(data);
			uart_puts("\r\n");
			fillBuffer(&ledbuf[0][0],&data,&writepos);
			shiftBufferOut(&mymax,&ledbuf[0][0]);
		}
		_delay_ms(250);
	}
}

