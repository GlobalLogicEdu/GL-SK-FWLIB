#include <stdio.h>
#include "glesk_uart.h"

#define UART_SPEED 9600

int main(void)
{
	char buf[20] = {0};

	printf("Hello, World!!\n\r");

	uart_init(GLESK_USART2, UART_SPEED);
	uart_write(GLESK_USART2, "1234", 5);

	uart_read(GLESK_USART3, buf, 10);

	printf("\n\rYour string is: %s\n\r", buf);

	return 0;
}
