#ifndef DRIVERS_I2C_H_
#define DRIVERS_I2C_H_

#include <stm32f4xx_i2c.h>
#include "clock_config.h"
#include "peripheral_pinout.h"

void setup_I2C(I2C_TypeDef* I2Cx);

void I2C_transmit_byte(I2C_TypeDef* I2Cx, uint8_t address, uint8_t data);

void I2C_receive_byte(I2C_TypeDef* I2Cx,uint8_t address, uint8_t *data);

void I2C_transmit_byte_to_reg(I2C_TypeDef* I2Cx, uint8_t address, uint8_t reg, uint8_t data);

void I2C_receive_byte_from_reg(I2C_TypeDef* I2Cx,uint8_t address, uint8_t reg, uint8_t *data);

void I2C_send_byte_array_to_reg(I2C_TypeDef* I2Cx, uint8_t address, uint8_t reg, uint8_t *array, uint16_t size);

void I2C_receive_byte_array_from_reg(I2C_TypeDef* I2Cx, uint8_t address, uint8_t reg, uint8_t *array, uint16_t size);


#endif /* DRIVERS_I2C_H_ */
