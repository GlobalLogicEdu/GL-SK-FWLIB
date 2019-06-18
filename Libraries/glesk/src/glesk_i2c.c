#include "glesk_i2c.h"

struct i2c_config {
	uint8_t init;
	void *base;
} i2c[GLESK_I2C_MAX_NUM];

static void * __attribute__((unused)) i2c_get_base(uint8_t i2c_num)
{
	switch (i2c_num){
	case 1:
		return I2C1;
	case 2:
		return I2C2;
	case 3:
		return I2C3;
	default:
		return 0;
	}
}

static int wait_for_status(u8 i2c_num, uint32_t flags) {
	u32 timeout = HSI_VALUE;

	while(I2C_GetFlagStatus(i2c[i2c_num].base, flags) == RESET) {
		if (!(timeout--)) return -1;
	}

	return 0;
}

static int wait_for_idle(u8 i2c_num) {
	u32 timeout = HSI_VALUE;

	while(I2C_GetFlagStatus(i2c[i2c_num].base, I2C_FLAG_BUSY) == SET) {
		if (!(timeout--)) return -1;
	}

	return 0;
}

int i2c_init(uint8_t i2c_num)
{
	GPIO_InitTypeDef  i2c_gpio_init;
	I2C_InitTypeDef   i2c_init;

	void *i2c_base;

	if (i2c_num > 8) return -1;
	if (i2c[i2c_num].init) return 0;

	i2c_gpio_init.GPIO_Mode = GPIO_Mode_AF;
	i2c_gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
	i2c_gpio_init.GPIO_OType = GPIO_OType_OD;
	i2c_gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;

	i2c_init.I2C_Mode = I2C_Mode_I2C;
	i2c_init.I2C_DutyCycle = I2C_DutyCycle_2;
	i2c_init.I2C_OwnAddress1 = 0x00; 			// master
	i2c_init.I2C_Ack = I2C_Ack_Enable;
	i2c_init.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	i2c_init.I2C_ClockSpeed = 50000;  			// 50kHz (max 400)

	switch (i2c_num) {
	case 1:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

		GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);

		i2c_gpio_init.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_9;
		GPIO_Init(GPIOB, &i2c_gpio_init);
		break;
	case 2:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, DISABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

		GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_I2C2);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_I2C2);

		i2c_gpio_init.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
		GPIO_Init(GPIOB, &i2c_gpio_init);
		break;
	case 3:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C3, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C3, ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C3, DISABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

		GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_I2C3);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_I2C3);

		i2c_gpio_init.GPIO_Pin = GPIO_Pin_8;
		GPIO_Init(GPIOA, &i2c_gpio_init);
		i2c_gpio_init.GPIO_Pin = GPIO_Pin_9;
		GPIO_Init(GPIOC, &i2c_gpio_init);
		break;
	default:
		return -1;
	}

	// Init I2C
	i2c_base = i2c_get_base(i2c_num);

	I2C_Init(i2c_base, &i2c_init);
	I2C_Cmd(i2c_base, ENABLE);

	// Save config
	i2c[i2c_num].init = 1;
	i2c[i2c_num].base = i2c_base;

	return 0;
}

int i2c_read(u8 i2c_num, u8 slave_addr, u8 reg_addr, u8 *data, ssize_t len)
{
	ssize_t bytes_to_rcv = len;
	u8 *buf = data;

	I2C_GenerateSTART(i2c[i2c_num].base, ENABLE);
	wait_for_status(i2c_num, I2C_FLAG_SB);

	I2C_Send7bitAddress(i2c[i2c_num].base, slave_addr << 1, I2C_Direction_Transmitter);
	wait_for_status(i2c_num, I2C_FLAG_ADDR);

	// Unstretch the clock
	I2C_ReadRegister(i2c[i2c_num].base, I2C_Register_SR2);

	I2C_SendData(i2c[i2c_num].base, reg_addr);
	wait_for_status(i2c_num, I2C_FLAG_BTF);

	//Generate Start
	I2C_GenerateSTART(i2c[i2c_num].base, ENABLE);
	wait_for_status(i2c_num, I2C_FLAG_SB);

	//Send I2C Device Address and clear ADDR
	I2C_Send7bitAddress(i2c[i2c_num].base, slave_addr << 1, I2C_Direction_Receiver);
	wait_for_status(i2c_num, I2C_FLAG_ADDR);

	// Unstretch the clock
	I2C_ReadRegister(i2c[i2c_num].base, I2C_Register_SR2);

	while ((bytes_to_rcv--) > 1) {
		wait_for_status(i2c_num, I2C_FLAG_RXNE);
		*buf = I2C_ReceiveData(i2c[i2c_num].base);
		buf++;
	}

	I2C_AcknowledgeConfig(i2c[i2c_num].base, DISABLE);

	I2C_GenerateSTOP(i2c[i2c_num].base, ENABLE);

	wait_for_status(i2c_num, I2C_FLAG_RXNE);
	*buf = I2C_ReceiveData(i2c[i2c_num].base);

	wait_for_idle(i2c_num);
	I2C_AcknowledgeConfig(i2c[i2c_num].base, ENABLE);

	return len;
}

int i2c_write(u8 i2c_num, u8 slave_addr, u8 reg_addr, const u8 *data, ssize_t len)
{
	ssize_t bytes_to_send = len;
	u8 *buf = (u8 *)data;

	I2C_GenerateSTART(i2c[i2c_num].base, ENABLE);
	wait_for_status(i2c_num, I2C_FLAG_SB);

	I2C_Send7bitAddress(i2c[i2c_num].base, slave_addr << 1, I2C_Direction_Transmitter);
	wait_for_status(i2c_num, I2C_FLAG_ADDR);

	// Unstretch the clock
	I2C_ReadRegister(i2c[i2c_num].base, I2C_Register_SR2);

	// Send reg addr
	I2C_SendData(i2c[i2c_num].base, reg_addr);
	wait_for_status(i2c_num, I2C_FLAG_TXE);

	// Writing Data
	while (bytes_to_send--) {
		I2C_SendData(i2c[i2c_num].base, *buf++);
		wait_for_status(i2c_num, I2C_FLAG_TXE);
	}

	// Wait for the data to be transmitted
	wait_for_status(i2c_num, I2C_FLAG_BTF);

	I2C_GenerateSTOP(i2c[i2c_num].base, ENABLE);
	wait_for_idle(i2c_num);

	return len;
}
