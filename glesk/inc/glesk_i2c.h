#ifndef __GL_ESK_I2C__
#define __GL_ESK_I2C__

#include <sys/types.h>
#include "glesk_common.h"

enum {
	GLESK_I2C1 = 1,
	GLESK_I2C2,
	GLESK_I2C3,
	GLESK_I2C_MAX_NUM
};

int i2c_init(uint8_t i2c_num);
int i2c_read(u8 i2c_num, u8 slave_addr, u8 reg_addr, u8 *data, ssize_t len);
int i2c_write(u8 i2c_num, u8 slave_addr, u8 reg_addr, const u8 *data, ssize_t len);

#endif /* ifndef __GL_ESK_I2C_ */
