#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Dimensions of the LED Matrix
#define ROWLENGTH				(8)
#define COLLENGTH				(32)

#define NrArrayItems(array)		(sizeof(array)/sizeof(array[0]))
#define NrRows(array)			(sizeof(array)/sizeof(array[0]))
#define NrColumns(array)		(sizeof(array[0])/sizeof(array[0][0]))

uint8_t registers[8] = {0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8};

/* Print Functions for Terminal */
void printByte(uint8_t *value)
{
	printf("Byte: %d\n",*value);
}

void printRegister(uint8_t regindex)
{
	switch(regindex)
	{
		case 0:
			printf("reg_digit%d\n",0);
		break;
		case 1:
			printf("reg_digit%d\n",1);
		break;
		case 2:
			printf("reg_digit%d\n",2);
		break;
		case 3:
			printf("reg_digit%d\n",3);
		break;
		case 4:
			printf("reg_digit%d\n",4);
		break;	
		case 5:
			printf("reg_digit%d\n",5);
		break;
		case 6:
			printf("reg_digit%d\n",6);
		break;
		case 7:
			printf("reg_digit%d\n",7);
		break;
		default:
			printf("No Valid Register, Regindex: %d\n",regindex);
			break;
	}
}

void printLatch(void){
	printf("Data latched from Shift Register\n");
}

void shiftBufferOut(uint8_t *rdptr)
{	
	uint8_t regcounter = 0;
	for (uint16_t i = 0; i < (ROWLENGTH*COLLENGTH); i++)
	{
		if (!(i%8))
		{
			printRegister(regcounter);
		}
		printByte(rdptr);
		if (!((i+1)%32))
		{
			printLatch();
			regcounter++;
		}
		rdptr--;
	}
}

void shiftBufferRight(uint8_t *rdptr)
{
	uint8_t regcounter = 0;
	for (uint16_t i = 0; i < (ROWLENGTH*COLLENGTH); i++)
	{
		if (!(i%8))
		{
			printRegister(regcounter);
		}
		if (!((i+1)%32))
		{
			printByte(rdptr+31);
		}else{
			printByte(rdptr-1);
		}
		if (!((i+1)%32))
		{
			printLatch();
			regcounter++;
		}
		rdptr--;
	}
}

void shiftBufferLeft(uint8_t *rdptr)
{
	uint8_t regcounter = 0;
	for (uint16_t i = 0; i < (ROWLENGTH*COLLENGTH); i++)
	{
		if (!(i%8))
		{
			printRegister(regcounter);
		}
		if (!(i%32))
		{
			printByte(rdptr-31);
		}else{
			printByte(rdptr+1);
		}
		if (!((i+1)%32))
		{
			printLatch();
			regcounter++;
		}
		rdptr--;
	}
}

int main()
{	
	printf("*************************Arrays and Pointer*************************\n");
	uint8_t ledbuf[ROWLENGTH][COLLENGTH];
	uint8_t counter = 0;

	for (uint8_t i = 0; i < ROWLENGTH; i++)
	{
		for (uint8_t j = 0; j < COLLENGTH; j++)
		{
			ledbuf[i][j] = counter;
			counter++;
		}
	}

	uint8_t *ptr = &ledbuf[ROWLENGTH-1][COLLENGTH-1];

	shiftBufferOut(ptr);
	shiftBufferRight(ptr);
	shiftBufferLeft(ptr);
	return 0;
}