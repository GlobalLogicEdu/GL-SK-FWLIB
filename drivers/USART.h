#ifndef DRIVERS_UART_H_
#define DRIVERS_UART_H_

#include <stm32f4xx_usart.h>
#include <string.h>
#include <stdarg.h>

#define INTERRUPT_ENABLE	ENABLE
#define INTERRUPT_DISABLE	DISABLE


#define USART3_BUFF_MAX_SIZE (256)
char USART3_BUFFER[USART3_BUFF_MAX_SIZE];
uint8_t USART3_RX_DATA;
//uint8_t USART3_RX_DATA;

typedef enum{
	PREPARING = 0,
	NOT_READY = 0,
	READY,
	ALREADY_SENT,
} RX_DATA_State_TypeDef;



void setup_USART(USART_TypeDef *USARTx, FunctionalState interrupt);

void USART_send_character(USART_TypeDef *USARTx, char ch);

void USART_send_characterLN(USART_TypeDef *USARTx, char *str);

char USART_receive_character(USART_TypeDef *USARTx);

void USART_receive_string(USART_TypeDef *USARTx, char* buff, uint32_t max_size);

void USART_send_string(USART_TypeDef *USARTx, char *str);

void USART3_BUFFER_print(void);

void USART_echo(USART_TypeDef *USARTx);

void USART_INFO_LOG(USART_TypeDef *USARTx, char *who, char *where, char *what);

void USART_DEBUG_LOG(USART_TypeDef *USARTx, char *FILE, int LINE);

void USART_printf(USART_TypeDef *USARTx, char *formater, ...);

void USART3_BUFFER_reset(void);

#endif //DRIVERS_UART_H_
