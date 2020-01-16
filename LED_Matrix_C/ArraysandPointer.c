#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define ROWLENGTH				(8)
#define COLLENGTH				(32)
#define NRMAX					(4)

#define NrArrayItems(array)		(sizeof(array)/sizeof(array[0]))
#define NrRows(array)			(sizeof(array)/sizeof(array[0]))
#define NrColumns(array)		(sizeof(array[0])/sizeof(array[0][0]))

uint8_t registers[8] = {0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8};

/* write Functions for MAX7219 */
void writeBit(uint8_t *value)
{
	
}

void writeRegister(uint8_t regindex)
{

}

void LatchData(void)
{

}

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

void shiftBufferOut(uint8_t buffer[ROWLENGTH][COLLENGTH])
{	
	uint8_t *rdptr = &buffer[ROWLENGTH-1][COLLENGTH-1];
	uint8_t regcounter = 0;
	for (uint8_t i = 0; i < (ROWLENGTH*COLLENGTH)-1; i++)
	{
		if (!(i%8))
		{
			printRegister(regcounter);
		}
		printByte(rdptr-i);
		if (!((i+1)%32))
		{

			printLatch();
			regcounter++;
		}
		
	}
}	

int main()
{	
	printf("*************************Arrays and Pointer*************************\n");
	uint8_t ledbuf[ROWLENGTH][COLLENGTH];
	uint8_t counter = 0;

	for (uint8_t i = 0; i < 8; i++)
	{
		for (uint8_t j = 0; j < 32; j++)
		{
			ledbuf[i][j] = counter;
			counter++;
		}
	}

	uint8_t *ptr = &ledbuf[ROWLENGTH-1][COLLENGTH-1];
	printf("Address pointer points to: %x\n",ptr);
	printf("Value stored in this address: %d\n",*ptr);

	shiftBufferOut(ledbuf);
	return 0;
}