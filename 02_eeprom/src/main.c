#include <stdio.h>
#include <string.h>
#include "glesk_ex_eeprom.h"

#define DATA_SIZE	128

int main(void)
{
	u8 buff[EX_EEPROM_SIZE] = {0x12, 0x22, 0x33, 0xaa, 0xbb, 0xcc, 0};

	printf("Start program\n\r");

	ex_eeprom_init();
	ex_eeprom_write(0x0, buff, DATA_SIZE);
	ex_eeprom_read(0x0, buff, EX_EEPROM_SIZE);

	printf("Read bytes from EEPROM: \n\r");
	for (int i = 0; i < EX_EEPROM_SIZE; ++i) {
		printf("%x ", buff[i]);
		if ((i % 8) == 7) printf("\n\r");
	}

	printf("\n\rEnd program\n\r");
}
