#include <stdio.h>
#include "glesk_ex_temp.h"

int main(void)
{
	float temp;

	printf("Program start\r\n");
	ex_temp_init();

	ex_temp_read(&temp);
	printf("Temperature: %d.%d C\n\r", (u32)temp,
			(u32)((temp - (float)((u32)temp)) * 100.0));

	printf("Program end\r\n\r\n");
	return 0;
}
