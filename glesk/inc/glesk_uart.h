#ifndef __GL_ESK_UART__
#define __GL_ESK_UART__

#include <sys/types.h>
#include "glesk_common.h"

enum {
	GLESK_USART1 = 1,
	GLESK_USART2,
	GLESK_USART3,
	GLESK_UART4,
	GLESK_UART5,
	GLESK_USART6,
	GLESK_UART7,
	GLESK_UART8,
	GLESK_UART_MAX_NUM
};

int uart_init(uint8_t uart_num, uint32_t speed);

int uart_read(uint8_t uart_num, char *str, ssize_t len);
int uart_write(uint8_t uart_num, const char *str, ssize_t len);

#endif /* ifndef __GL_ESK_UART_ */
