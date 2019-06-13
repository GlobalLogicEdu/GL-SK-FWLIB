#include "clock_config.h"
#include "peripheral_pinout.h"
#include "USART.h"

#include <stdio.h>
#include <string.h>

static char USART_printf_buffer[256];

//char buff[USART3_BUFF_MAX_SIZE];
//uint8_t DATA_IS_READY;

static IRQn_Type select_USART_NVIC_channel(USART_TypeDef *USARTx)
{
	switch ((int)USARTx) {
		case (int)USART1:
			return USART1_IRQn;
		case (int)USART2:
			return USART2_IRQn;
		case (int)USART3:
			return USART3_IRQn;
		case (int)UART4:
			return UART4_IRQn;
		case (int)UART5:
			return UART5_IRQn;
		case (int)USART6:
			return USART6_IRQn;
		default:
			return	100;
	}
}

static void setup_NVIC_for_USART(USART_TypeDef *USARTx)
{
	  NVIC_InitTypeDef NVIC_InitStructure;
	  IRQn_Type IRQ_channel;
	  IRQ_channel = select_USART_NVIC_channel(USARTx);
	  NVIC_InitStructure.NVIC_IRQChannel = IRQ_channel;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
}

void setup_USART(USART_TypeDef *USARTx, FunctionalState interrupt)
{
	USART_Cmd(USARTx, DISABLE);

	setup_clock_for_USART(USARTx, ENABLE);
	setup_pinout_for_USART(USARTx);
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	if(interrupt == ENABLE)
	{
		USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
		setup_NVIC_for_USART(USARTx);
	}
	USART_Init(USARTx, &USART_InitStructure);
	USART_Cmd(USARTx, ENABLE);

}

void USART_send_character(USART_TypeDef *USARTx, char ch)
{
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}
	USART_SendData(USARTx, (uint16_t)ch);
}

void USART_send_string(USART_TypeDef *USARTx, char *str)
{
	while(*str != '\0')
	{
		USART_send_character(USARTx, *str++);
	}
}

void USART_send_characterLN(USART_TypeDef *USARTx, char *str)
{
	while(*str != '\0')
	{
		USART_send_character(USARTx, *str++);
	}
	USART_send_character(USARTx, '\n');
	USART_send_character(USARTx, '\r');
}

void USART_DEBUG_LOG(USART_TypeDef *USARTx, char *FILE, int LINE)
{
	char line_number[5]; sprintf(line_number, "%u"
			"", LINE);
	USART_send_string(USARTx, FILE);
	USART_send_character(USARTx, '\t');
	USART_send_string(USARTx, line_number);
	USART_send_character(USARTx, '\n');
	USART_send_character(USARTx, '\r');
}

void USART_INFO_LOG(USART_TypeDef *USARTx, char *who, char *where, char *what)
{
	USART_send_string(USARTx, who); 	USART_send_character(USARTx, '\t');
	USART_send_string(USARTx, where); 	USART_send_character(USARTx, '\t');
	USART_send_string(USARTx, what); 	USART_send_character(USARTx, '\t');

	USART_send_character(USARTx, '\n');
	USART_send_character(USARTx, '\r');
}

char USART_receive_character(USART_TypeDef *USARTx)
{
	return USART_ReceiveData(USARTx);
}

void USART_echo(USART_TypeDef *USARTx)
{
	char ch;
	ch = USART_receive_character(USARTx);
	if(ch)
	{
		if(ch == 0x0D) //press Enter
		{
			USART_send_string(USARTx, "\n\r");
		}
		else
		{
			USART_send_character(USARTx, ch);
		}
	}
}

void USART_receive_string(USART_TypeDef *USARTx, char* buff, uint32_t max_size)
{
	char ch;
	uint32_t i = 0;
	buff[max_size-1] = '\0';
	if (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == SET)
	while (i < max_size)
	{
		ch = USART_receive_character(USARTx);
		if(ch == 0x0D)
		{
			buff[i] = '\0';
			break;
		}
		if(i <= max_size)
		{
			buff[i++] = ch;
		}
	}
}

void USART3_BUFFER_print(void)
{
	if(USART3_RX_DATA == READY)
	{
		USART_send_characterLN(USART3, "");
		USART_send_characterLN(USART3, USART3_BUFFER);
		USART3_RX_DATA = ALREADY_SENT;
	}
}

void USART3_BUFFER_reset(void)
{
	memset(USART_printf_buffer, 0, USART3_BUFF_MAX_SIZE);
}

void USART_printf(USART_TypeDef *USARTx, char *formater, ...)
{
	va_list argumerts_list;
	va_start (argumerts_list, formater);
	vsprintf(USART_printf_buffer, formater, argumerts_list);
	USART_send_string(USARTx, USART_printf_buffer);

}
