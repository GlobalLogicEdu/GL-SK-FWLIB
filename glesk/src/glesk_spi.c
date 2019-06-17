#include "glesk_spi.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_gpio.h"

struct spi_config {
	uint8_t init;
	void *base;
} spi[GLESK_SPI_MAX_NUM];

static void * __attribute__((unused)) spi_get_base(uint8_t spi_num)
{
	switch (spi_num){
	case 1:
		return SPI1;
	case 2:
		return SPI2;
	case 3:
		return SPI3;
	default:
		return 0;
	}
}

int spi_init(uint8_t spi_num)
{
	GPIO_InitTypeDef  spi_gpio_init;
	SPI_InitTypeDef   spi_init;

	void *spi_base;

	if (spi_num > 8) return -1;
	if (spi[spi_num].init) return 0;

	spi_gpio_init.GPIO_Mode = GPIO_Mode_AF;
	spi_gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
	spi_gpio_init.GPIO_OType = GPIO_OType_PP;
	spi_gpio_init.GPIO_PuPd  = GPIO_PuPd_NOPULL;

	spi_init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
	spi_init.SPI_CPHA = SPI_CPHA_1Edge;
	spi_init.SPI_CPOL = SPI_CPOL_Low;
	spi_init.SPI_DataSize = SPI_DataSize_8b;
    spi_init.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spi_init.SPI_FirstBit = SPI_FirstBit_MSB;
	spi_init.SPI_Mode = SPI_Mode_Master;
    spi_init.SPI_NSS = SPI_NSS_Soft;

	switch (spi_num) {
	case 1:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

		GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);

		spi_gpio_init.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5; // MISO & MOSI
		GPIO_Init(GPIOB, &spi_gpio_init);

		spi_gpio_init.GPIO_Pin = GPIO_Pin_5; // SCK
		GPIO_Init(GPIOA, &spi_gpio_init);

        // TODO: temp
        spi_gpio_init.GPIO_Pin = GPIO_Pin_7; // CS
        spi_gpio_init.GPIO_Mode = GPIO_Mode_OUT;
        GPIO_Init(GPIOD, &spi_gpio_init);
        spi_slave_disable();
		break;
	default:
		return -1;
	}

	// Init SPI
	spi_base = spi_get_base(spi_num);

	SPI_Init(spi_base, &spi_init);
	SPI_Cmd(spi_base, ENABLE);

	// Save config
	spi[spi_num].init = 1;
	spi[spi_num].base = spi_base;

	return 0;
}

void spi_w_byte(uint8_t spi_num, uint8_t byte)
{
    SPI_I2S_SendData(spi[spi_num].base, byte);

    // Wait until byte will be transmitted
    while (SPI_I2S_GetFlagStatus(spi[spi_num].base, SPI_I2S_FLAG_TXE) == RESET);
    while (SPI_I2S_GetFlagStatus(spi[spi_num].base, SPI_I2S_FLAG_BSY) == SET);

    // Flush Rx
    while (SPI_I2S_GetFlagStatus(spi[spi_num].base, SPI_I2S_FLAG_RXNE) == SET)
        SPI_I2S_ReceiveData(spi[spi_num].base);
}

uint8_t spi_r_byte(uint8_t spi_num)
{
    // Send dummy to continue receiving data
    do {
        SPI_I2S_SendData(spi[spi_num].base, 0);
        while (SPI_I2S_GetFlagStatus(spi[spi_num].base, SPI_I2S_FLAG_BSY) == SET);
    } while (SPI_I2S_GetFlagStatus(spi[spi_num].base, SPI_I2S_FLAG_RXNE) == RESET);

    return SPI_I2S_ReceiveData(spi[spi_num].base);
}

void spi_slave_enable()
{
    GPIO_ResetBits(GPIOD, GPIO_Pin_7);
}

void spi_slave_disable()
{
    GPIO_SetBits(GPIOD, GPIO_Pin_7);
}

int spi_read(u8 spi_num, u8 slave_addr, u8 reg_addr, u8 *data, ssize_t len)
{
	return -1;
}

int spi_write(u8 spi_num, u8 slave_addr, u8 reg_addr, const u8 *data, ssize_t len)
{
	return -1;
}
