#ifndef __GL_ESK_SPI__
#define __GL_ESK_SPI__

#include <sys/types.h>
#include "glesk_common.h"

enum {
	GLESK_SPI1 = 1,
	GLESK_SPI2,
	GLESK_SPI3,
	GLESK_SPI_MAX_NUM
};

int spi_init(uint8_t spi_num);
int spi_read(u8 spi_num, u8 slave_addr, u8 reg_addr, u8 *data, ssize_t len);
int spi_write(u8 spi_num, u8 slave_addr, u8 reg_addr, const u8 *data, ssize_t len);

void spi_w_byte(uint8_t spi_num, uint8_t byte);
uint8_t spi_r_byte(uint8_t spi_num);
void SPIx_EnableSlave(void);
void SPIx_DisableSlave(void);

#endif /* ifndef __GL_ESK_SPI_ */
