#ifndef __GL_ESK_COMMON__
#define __GL_ESK_COMMON__

#include <sys/types.h>
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

#define EX_FLASH_SPI_PORT   GLESK_SPI1
#define EX_FLASH_CS_PIN     GPIO_Pin_7
#define EX_FLASH_CS_PORT    GPIOD
#define EX_FLASH_CS_PCLK    RCC_AHB1Periph_GPIOD

#define delay_ms(ms) {long i = HSE_VALUE / 1000 * ms; while (--i);}

#endif /* ifndef __GL_ESK_COMMON__ */
