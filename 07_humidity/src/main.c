#include <stdio.h>
#include "glesk_ex_humid.h"

int main(void)
{
	u8 humid;
	u8 temp;

	printf("Program start\r\n");

	ex_humid_init();

	if (ex_humid_read(&humid, &temp) == 0) {
		printf("Humidity: %d percent\r\n", humid);
		printf("Temp: %d C\r\n", temp);
	} else {
		printf("Can't get data\r\n");
	}

	printf("Program end\r\n\r\n");
	return 0;
}
