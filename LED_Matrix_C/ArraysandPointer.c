#include <stdint.h>
#include <stdbool.h>

# define NrArrayItems(arr)		sizeof(arr)/sizeof(arr[0])

void printptrarr(uint8_t *ptr[])
{
	for (uint8_t i = 0; i < NrArrayItems(ptr); i++)
	{
		printf("Value of ptr[%d]: %d\n",i,*ptr[i]);
	}
}

int main()
{
	uint8_t testbuf[2][3] ={{1,2,3},
							{4,5,6}};

	uint8_t *mycolptr[] = {&testbuf[0][0],&testbuf[1][0]};
	printptrarr(mycolptr);
}