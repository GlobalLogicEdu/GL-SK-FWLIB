#include <stdio.h>
#include <string.h>
#include "glesk_i2c.h"

#define EEPROM_SLAVE_ADDR		0x50
#define EEPROM_PAGE_SIZE 		8
#define EEPROM_SIZE				256
#define EEPROM_PAGE_WR_DELAY_MS 2

#define DATA_SIZE	128

int main(void)
{
	u8 buff[EEPROM_SIZE] = {0x12, 0x22, 0x33, 0xaa, 0xbb, 0xcc, 0};

	printf("Start program\n\r");

	i2c_init(GLESK_I2C1);

	for (u8 i = 0; i < DATA_SIZE / EEPROM_PAGE_SIZE; ++i) {
		i2c_write(GLESK_I2C1,
				EEPROM_SLAVE_ADDR,
				(i * EEPROM_PAGE_SIZE),
				(buff + i * EEPROM_PAGE_SIZE),
				EEPROM_PAGE_SIZE);
		printf("Wrote page: %d\n\r", i);
		delay_ms(EEPROM_PAGE_WR_DELAY_MS);
	}

	i2c_read(GLESK_I2C1, EEPROM_SLAVE_ADDR, 0x00, buff, EEPROM_SIZE);
	printf("Read bytes from EEPROM: \n\r");
	for (int i = 0; i < EEPROM_SIZE; ++i) {
		printf("%x ", buff[i]);
	}

	printf("\n\rEnd program\n\r");
}
