#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define NrArrayItems(array)		(sizeof(array)/sizeof(array[0]))
#define NrRows(array)			(sizeof(array)/sizeof(array[0]))
#define NrColumns(array)		(sizeof(array[0])/sizeof(array[0][0]))

void printcolumn(uint8_t *ptr, uint8_t NrItems)
{
	for (uint8_t i = 0; i < NrItems; i++)
	{
		printf("Value of ptr + %d: %d\n",i,*(ptr+i));
	}
}

int main()
{
	uint8_t testbuf[2][3] ={{1,2,3},
							{4,5,6}};

	uint8_t test[2][3][4] = {
    {{3, 4, 2, 3}, {0, -3, 9, 11}, {23, 12, 23, 2}},
    {{13, 4, 56, 3}, {5, 9, 3, 5}, {3, 1, 4, 9}}};

	uint8_t *myptr = &test[0][0][0];
	printcolumn(myptr, NrArrayItems(test));
}