#include <stdio.h>
#include "glesk_ex_flash.h"

#define FLASH_ADDR	0
#define DATA_SZ		16

int main(void)
{
	u8 buff[DATA_SZ + 1] = {0};

    printf("External flash test.\n\r");
    ex_flash_init();

	ex_flash_erase_sector(FLASH_ADDR);
	ex_flash_write(FLASH_ADDR, (u8 *)"Hello from flash", DATA_SZ);
	ex_flash_read(FLASH_ADDR, buff, DATA_SZ);

	printf("Read from flash: %s\n\r", buff);
    printf("Test finished.\n\r");
}
