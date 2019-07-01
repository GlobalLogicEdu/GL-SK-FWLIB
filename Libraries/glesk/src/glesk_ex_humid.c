#include "glesk_ex_humid.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#define EX_HUMID_PIN	GPIO_Pin_11
#define EX_HUMID_PORT	GPIOD
#define EX_HUMID_PCLK	RCC_AHB1Periph_GPIOD
#define EX_HUMID_MODE	GPIO_MODER_MODER11

int ex_humid_init(void)
{
	GPIO_InitTypeDef  ex_humid_gpio_init;

	ex_humid_gpio_init.GPIO_Pin = EX_HUMID_PIN;
	ex_humid_gpio_init.GPIO_Mode = GPIO_Mode_OUT;
	ex_humid_gpio_init.GPIO_OType = GPIO_OType_OD;
	ex_humid_gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
	ex_humid_gpio_init.GPIO_Speed = GPIO_Speed_100MHz;

	RCC_AHB1PeriphClockCmd(EX_HUMID_PCLK, ENABLE);
	GPIO_Init(EX_HUMID_PORT, &ex_humid_gpio_init);

	return 0;
}

int ex_humid_read(u8 *data, ssize_t len)
{
	u8 got_response = 0;
	u8 bit_iter;
	u8 byte_iter;
	u8 byte;

	if (!data || len < 5) return -1;

	GPIO_ResetBits(EX_HUMID_PORT, EX_HUMID_PIN);
	delay_us(22000);	// wait for 20ms
	GPIO_SetBits(EX_HUMID_PORT, EX_HUMID_PIN);

	// Change mode to input
	EX_HUMID_PORT->MODER &= ~EX_HUMID_MODE;
	delay_us(34);   // wait for 25us

	// If low
	if (!GPIO_ReadInputDataBit(EX_HUMID_PORT, EX_HUMID_PIN)) {
		delay_us(107);   // wait for 90us
		got_response = GPIO_ReadInputDataBit(EX_HUMID_PORT, EX_HUMID_PIN);
		while ((GPIO_ReadInputDataBit(EX_HUMID_PORT, EX_HUMID_PIN)));
	}

	if (!got_response) return -1;

	for (byte_iter = 0; byte_iter < 5; ++byte_iter) {
		byte = 0;
		for (bit_iter = 0; bit_iter < 8; ++bit_iter) {
			// Wait for high
			while (!(GPIO_ReadInputDataBit(EX_HUMID_PORT, EX_HUMID_PIN)));
			delay_us(40);   // wait for 30us

			// If low then it is zero bit
			byte = (byte << 1) | GPIO_ReadInputDataBit(EX_HUMID_PORT, EX_HUMID_PIN);

			// Wait for low
			while (GPIO_ReadInputDataBit(EX_HUMID_PORT, EX_HUMID_PIN));
		}
		data[byte_iter] = byte;
	}

	if (data[4] != (u8)(data[3] + data[2] + data[1] + data[0])) return -1;

	return 0;
}
