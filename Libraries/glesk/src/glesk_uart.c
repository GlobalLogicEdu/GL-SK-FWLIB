#include "glesk_uart.h"
#include "stm32f4xx.h"

struct uart_config {
	uint8_t init;
	uint8_t speed;
	void *base;
} uart[GLESK_UART_MAX_NUM];

static void * __attribute__((unused)) uart_get_base(uint8_t uart_num)
{
	switch (uart_num){
	case 1:
		return USART1;
	case 2:
		return USART2;
	case 3:
		return USART3;
	case 4:
		return UART4;
	case 5:
		return UART5;
	case 6:
		return USART6;
	case 7:
		return UART7;
	case 8:
		return UART8;
	default:
		return 0;
	}
}

int uart_init(uint8_t uart_num, uint32_t speed)
{
	GPIO_InitTypeDef uart_gpio_init;
	USART_InitTypeDef uart_init;

	void *uart_base;

	if (uart_num > 8) return -1;
	if (uart[uart_num].init) return 0;

	uart_gpio_init.GPIO_Mode = GPIO_Mode_AF;
	uart_gpio_init.GPIO_OType = GPIO_OType_PP;
	uart_gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
	uart_gpio_init.GPIO_Speed = GPIO_Speed_100MHz;

	uart_init.USART_WordLength = USART_WordLength_8b;
	uart_init.USART_StopBits = USART_StopBits_1;
	uart_init.USART_Parity = USART_Parity_No;
	uart_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uart_init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	switch (uart_num) {
	case 1:
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

		uart_gpio_init.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
		GPIO_Init(GPIOA, &uart_gpio_init);
		break;
	case 2:
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

		GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

		uart_gpio_init.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
		GPIO_Init(GPIOA, &uart_gpio_init);
		break;
	case 3:
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

		GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);

		uart_gpio_init.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
		GPIO_Init(GPIOD, &uart_gpio_init);
		break;
	case 4:
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

		GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);

		uart_gpio_init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
		GPIO_Init(GPIOA, &uart_gpio_init);
		break;
	case 5:
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);

		GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);

		uart_gpio_init.GPIO_Pin = GPIO_Pin_2;
		GPIO_Init(GPIOD, &uart_gpio_init);
		uart_gpio_init.GPIO_Pin = GPIO_Pin_12;
		GPIO_Init(GPIOC, &uart_gpio_init);
		break;
	case 6:
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

		GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);

		uart_gpio_init.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_Init(GPIOA, &uart_gpio_init);
		break;
	case 7:
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);

		GPIO_PinAFConfig(GPIOE, GPIO_PinSource7, GPIO_AF_UART7);
		GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_UART7);

		uart_gpio_init.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
		GPIO_Init(GPIOA, &uart_gpio_init);
		break;
	case 8:
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8, ENABLE);

		GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_UART8);
		GPIO_PinAFConfig(GPIOE, GPIO_PinSource1, GPIO_AF_UART8);

		uart_gpio_init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
		GPIO_Init(GPIOA, &uart_gpio_init);
		break;
	default:
		return -1;
	}

	// Init USART
	uart_base = uart_get_base(uart_num);
	uart_init.USART_BaudRate = speed;

	USART_Init(uart_base, &uart_init);
	USART_Cmd(uart_base, ENABLE);

	// Save config
	uart[uart_num].init = 1;
	uart[uart_num].speed = speed;
	uart[uart_num].base = uart_base;

	return 0;
}

int uart_read(uint8_t uart_num, char *str, ssize_t len)
{
	ssize_t bytes_to_read = len;

	while (bytes_to_read) {
		if (str == NULL) return 0;

		while (USART_GetFlagStatus(uart[uart_num].base, USART_FLAG_RXNE) == RESET);
		*str = USART_ReceiveData(uart[uart_num].base);

		while (USART_GetFlagStatus(uart[uart_num].base, USART_FLAG_TC) == RESET);
		USART_SendData(uart[uart_num].base, *str++);

		--bytes_to_read;
	}

	return len;
}

int uart_write(uint8_t uart_num, const char *str, ssize_t len)
{
	ssize_t bytes_to_read = len;

	while (bytes_to_read) {
		if (str == NULL) return 0;

		while (USART_GetFlagStatus(uart[uart_num].base, USART_FLAG_TC) == RESET);
		USART_SendData(uart[uart_num].base, *str++);

		--bytes_to_read;
	}

	return len;
}
