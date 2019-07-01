#include <stdio.h>
#include "glesk_ex_humid.h"

#define DATA_SIZE	5

int main(void)
{
	u8 data[DATA_SIZE];

	printf("Program start\r\n");

	ex_humid_init();

	if (ex_humid_read(data, DATA_SIZE) == 0) {
		printf("Temp: %d C\r\n", data[2]);
		printf("Humidity: %d percent\r\n", data[0]);
	} else {
		printf("Can't get data\r\n");
	}

	printf("Program end\r\n");
	return 0;
}
