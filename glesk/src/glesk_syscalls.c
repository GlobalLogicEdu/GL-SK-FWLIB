#include "glesk_uart.h"

int _write(int fd, char *str, int len)
{
	int ret;

	if (fd != 1) return -1;

	ret = uart_init(PRINTF_UART_NUM, PRINTF_UART_SPEED);
	if (ret < 0) return -1;

	ret = uart_write(PRINTF_UART_NUM, str, len);
	if (ret < 0) return -1;

	return len;
}
