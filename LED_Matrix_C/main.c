#include <stdio.h>
#include <stdint.h>



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