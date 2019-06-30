#include "glesk_ex_flash.h"
#include "glesk_spi.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

// Uncomment to debug
//#define EX_FLASH_DEBUG

#ifdef EX_FLASH_DEBUG
	#include <stdio.h>
#endif /* ifdef EX_FLASH_DEBUG */

#define EX_FLASH_SPI_PORT   GLESK_SPI1
#define EX_FLASH_CS_PIN     GPIO_Pin_7
#define EX_FLASH_CS_PORT    GPIOD
#define EX_FLASH_CS_PCLK    RCC_AHB1Periph_GPIOD

#define DUMMY	0x00	// Dummy byte
#define RDB		0x03	// Read Memory at 25 MHz
#define HSRD	0x0B	// Read Memory at 50 MHz
#define E4KB	0x20	// Erase 4 KByte of memory array
#define E32KB	0x52	// Erase 32 KByte block of memory array
#define E64KB	0xD8	// Erase 64 KByte block of memory array
#define EALL	0x60	// Erase Full Memory Array
#define PRB		0x02	// To Program One Data Byte
#define AAIWP	0xAD	// Auto Address Increment Programming
#define RDSR	0x05	// Read-Status-Register
#define EWSR	0x50	// Enable-Write-Status-Register
#define WRSR	0x01	// Write-Status-Register
#define WREN	0x06	// Write-Enable
#define WRDI	0x04	// Write-Disable
#define RDID	0x90	// Read-ID
#define JDID	0x9F	// JEDEC ID read
#define EBSY	0x70	// Enable SO to output RY/BY# status during AAI programming
#define DBSY	0x80	// Disable SO to output RY/BY# status during AAI programming

#define BP0	0x04
#define BP1	0x08
#define BP2	0x10
#define BP3	0x20

#define MANUF_ID_ADDR	0x00
#define DEV_ID_ADDR		0x01

// Chip Select enable
static void cs_enable()
{
	GPIO_ResetBits(EX_FLASH_CS_PORT, EX_FLASH_CS_PIN);
}

// Chip Select disable
static void cs_disable()
{
	GPIO_SetBits(EX_FLASH_CS_PORT, EX_FLASH_CS_PIN);
}

static void send_byte(u8 out)
{
	spi_write(EX_FLASH_SPI_PORT, &out, 1);
}

static u8 get_byte(void)
{
	u8 out;
	spi_read(EX_FLASH_SPI_PORT, &out, 1);
	return out;
}

// Read Status Register
static u16 read_sr(void)
{
	u16 byte = 0;

	cs_enable();
	send_byte(RDSR);
	byte = get_byte();
	cs_disable();

	return byte;
}

// Write a byte to Status Register.
static void write_sr(u8 byte)
{
	cs_enable();
	send_byte(EWSR);

	// TODO: remove enable_disable here
	cs_disable();
	cs_enable();

	// Write to Status Register
	send_byte(WRSR);
	send_byte(byte);
	cs_disable();
}

// Set write enable
static void write_enable(void)
{
	cs_enable();
	send_byte(WREN);
	cs_disable();
}

static void wait_busy(void)
{
	// Wait until not busy
	while ((read_sr() & 0x03) == 0x03)
		read_sr();
}

// Read Manufacture or Device ID
static u8 __attribute__((unused)) read_id(u8 id_addr)
{
	u16 byte;

	cs_enable();
	send_byte(RDID);
	send_byte(DUMMY);
	send_byte(DUMMY);
	send_byte(id_addr);
	byte = get_byte();
	cs_disable();

	return byte;
}

static u8 read_byte(u32 addr)
{
	u8 byte = 0;

	cs_enable();
	send_byte(RDB);
	send_byte(((addr & 0xFFFFFF) >> 16));
	send_byte(((addr & 0xFFFF) >> 8));
	send_byte(addr & 0xFF);
	byte = get_byte();
	cs_disable();

	return byte;
}

static void write_byte(u32 addr, u8 byte)
{
	write_enable();
	cs_enable();
	send_byte(PRB);
	send_byte(((addr & 0xFFFFFF) >> 16));
	send_byte(((addr & 0xFFFF) >> 8));
	send_byte(addr & 0xFF);
	send_byte(byte);
	cs_disable();
}

int ex_flash_init(void)
{
	GPIO_InitTypeDef  ex_flash_gpio_init;
	u8 sr;

	// Init SPI port for external flash
	spi_init(EX_FLASH_SPI_PORT);

	// Init CS pin
	ex_flash_gpio_init.GPIO_Mode = GPIO_Mode_OUT;
	ex_flash_gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
	ex_flash_gpio_init.GPIO_OType = GPIO_OType_PP;
	ex_flash_gpio_init.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	ex_flash_gpio_init.GPIO_Pin = EX_FLASH_CS_PIN;

	RCC_AHB1PeriphClockCmd(EX_FLASH_CS_PCLK, ENABLE);
	GPIO_Init(EX_FLASH_CS_PORT, &ex_flash_gpio_init);

	cs_disable();

#ifdef EX_FLASH_DEBUG
	printf("Manufacture id: %x\n\r", read_id(MANUF_ID_ADDR));
	printf("Device id: %x\n\r", read_id(DEV_ID_ADDR));

	printf("Read 0x00 before erasing: %x\n\r", read_byte(0x00));
	printf("Read 0x01 before erasing: %x\n\r", read_byte(0x01));

	printf("Status register: %x\n\r", read_sr());

#endif /* #ifdef EX_FLASH_DEBUG */

	// Disable write protection
	write_enable();
	sr = read_sr();
	sr &= ~(BP0 | BP1 | BP2 | BP3);
	write_sr(sr);

#ifdef EX_FLASH_DEBUG
	read_sr();

	printf("Status register after clear protection: %x\n\r", read_sr());

	ex_flash_erase_sector(0x00);
	wait_busy();

	printf("Read 0x00 after erasing: %x\n\r", read_byte(0x00));
	printf("Read 0x01 after erasing: %x\n\r", read_byte(0x01));

	write_byte(0x00, 0xab);
	wait_busy();

	write_byte(0x01, 0xcd);
	wait_busy();

	printf("Read 0x00 after writing: %x\n\r", read_byte(0x00));
	printf("Read 0x01 after writing: %x\n\r", read_byte(0x01));
#endif /* ifdef EX_FLASH_DEBUG */

	return 0;
}

int ex_flash_read(u32 addr, u8 *data, ssize_t len)
{
	if (!data) return -1;

	for (u32 i = 0; i < len; ++i) {
		data[i] = read_byte(addr + i);
	}

	return len;
}

int ex_flash_write(u32 addr, const u8 *data, ssize_t len)
{
	if (!data) return -1;

	for (u32 i = 0; i < len; ++i) {
		write_byte(addr + i, data[i]);
	}
	wait_busy();

	return len;
}

void ex_flash_erase_sector(u32 addr)
{
	write_enable();
	cs_enable();
	send_byte(E4KB);
	send_byte(((addr & 0xFFFFFF) >> 16));
	send_byte(((addr & 0xFFFF) >> 8));
	send_byte(addr & 0xFF);
	cs_disable();
	wait_busy();
}

void ex_flash_erase_block_32k(u32 addr)
{
	write_enable();
	cs_enable();
	send_byte(E32KB);
	send_byte(((addr & 0xFFFFFF) >> 16));
	send_byte(((addr & 0xFFFF) >> 8));
	send_byte(addr & 0xFF);
	cs_disable();
	wait_busy();
}

void ex_flash_erase_block_64k(u32 addr)
{
	write_enable();
	cs_enable();
	send_byte(E64KB);
	send_byte(((addr & 0xFFFFFF) >> 16));
	send_byte(((addr & 0xFFFF) >> 8));
	send_byte(addr & 0xFF);
	cs_disable();
	wait_busy();
}

void ex_flash_erase_chip(void)
{
	write_enable();
	cs_enable();
	send_byte(EALL);
	cs_disable();
	wait_busy();
}
