#ifndef __GL_ESK_COMMON__
#define __GL_ESK_COMMON__

#include "stm32f4xx.h"

#ifndef NULL
	#define NULL (void *)0
#endif /* ifndef NULL */

#ifndef PRINTF_UART_NUM
	#define PRINTF_UART_NUM GLESK_USART3
#endif /* ifndef PRINTF_UART_NUM */

#ifndef PRINTF_UART_SPEED
	#define PRINTF_UART_SPEED 115200
#endif /* ifndef PRINTF_UART_SPEED */

#define delay_ms(ms) {long i = HSE_VALUE / 1000 * ms; while (--i);}

#endif /* ifndef __GL_ESK_COMMON__ */
