#include "glesk_ex_eeprom.h"
#include "glesk_i2c.h"

#define EX_EEPROM_I2C_PORT			GLESK_I2C1
#define EX_EEPROM_SLAVE_ADDR		0x50
#define EX_EEPROM_PAGE_SIZE			8
#define EX_EEPROM_PAGE_WR_DELAY_MS	6

int ex_eeprom_init(void)
{
	i2c_init(EX_EEPROM_I2C_PORT);

	return 0;
}

int ex_eeprom_read(u32 addr, u8 *data, ssize_t len)
{
	if (!data || len > EX_EEPROM_SIZE) return -1;

	i2c_read(GLESK_I2C1, EX_EEPROM_SLAVE_ADDR, addr, data, len);
	return len;
}

int ex_eeprom_write(u32 addr, const u8 *data, ssize_t len)
{
	u32 curr_addr = addr;
	const u8 *curr_data = data;

	if (!data || len > EX_EEPROM_SIZE) return -1;

	// If addr is not page start write data until end of page
	if (addr % EX_EEPROM_PAGE_SIZE) {
		ssize_t write_size = EX_EEPROM_PAGE_SIZE - (addr % EX_EEPROM_PAGE_SIZE);

		i2c_write(EX_EEPROM_I2C_PORT, EX_EEPROM_SLAVE_ADDR, curr_addr,
				  curr_data, write_size);

		curr_addr += write_size;
		curr_data += write_size;
		delay_ms(EX_EEPROM_PAGE_WR_DELAY_MS);
	}

	// Write data page by page
	for (ssize_t i = 0; i < len / EX_EEPROM_PAGE_SIZE; ++i) {
		i2c_write(EX_EEPROM_I2C_PORT, EX_EEPROM_SLAVE_ADDR, curr_addr,
				  curr_data, EX_EEPROM_PAGE_SIZE);

		curr_addr += EX_EEPROM_PAGE_SIZE;
		curr_data += EX_EEPROM_PAGE_SIZE;
		delay_ms(EX_EEPROM_PAGE_WR_DELAY_MS);
	}

	// If we have not full the last writing page, write it now
	if ((len - addr) % EX_EEPROM_PAGE_SIZE) {
		ssize_t write_size = (len + addr) % EX_EEPROM_PAGE_SIZE;

		i2c_write(EX_EEPROM_I2C_PORT, EX_EEPROM_SLAVE_ADDR, curr_addr,
				  curr_data, write_size);
		delay_ms(EX_EEPROM_PAGE_WR_DELAY_MS);
	}

	return len;
}
