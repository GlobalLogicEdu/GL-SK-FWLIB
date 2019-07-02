#include "interrupts.h"
#include "drivers/USART.h"
#include "drivers/LEDs.h"
#include "drivers/clock_config.h"
#include "drivers/Buttons.h"
#include "drivers/CAN_BUS.h"

volatile uint32_t usart3_buffer_iterrator;


void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		//TODO USER_DISCO_BUTTON
		 USER_BUTTON_state =~ USER_BUTTON_state;
		 EXTI_ClearITPendingBit(EXTI_Line0);

	}
}
void EXTI9_5_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line6) == SET)
	{
		//TODO UP_BUTTON
		UP_BUTTON_state =~ UP_BUTTON_state;
		EXTI_ClearITPendingBit(EXTI_Line6);

	}
	if(EXTI_GetITStatus(EXTI_Line8) == SET)
	{
		//TODO DOWN_BUTTON
		DOWN_BUTTON_state =~ DOWN_BUTTON_state;
		EXTI_ClearITPendingBit(EXTI_Line8);

	}
	if(EXTI_GetITStatus(EXTI_Line9) == SET)
	{
		//TODO LEFT_BUTTON
		LEFT_BUTTON_state =~ LEFT_BUTTON_state;
		EXTI_ClearITPendingBit(EXTI_Line9);
	}
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line15) == SET)
	{
		//TODO OK BUTTON
		OK_BUTTON_state =~ OK_BUTTON_state;
		EXTI_ClearITPendingBit(EXTI_Line15);
	}
	if(EXTI_GetITStatus(EXTI_Line11) == SET)
	{
		//TODO RIGTH BUTTON
		RIGHT_BUTTON_state =~ RIGHT_BUTTON_state;
		EXTI_ClearITPendingBit(EXTI_Line11);
	}
}


/**
  * @brief   This function handles USART3 exception.
  * @param  None
  * @retval None
  */

void USART3_IRQHandler(void)
{
	if (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == SET)
	{

		if (USART3_RX_DATA == ALREADY_SENT)
		{
			usart3_buffer_iterrator = 0;
		}
		USART3_RX_DATA = PREPARING;
		char ch;
		USART3_BUFFER[USART3_BUFF_MAX_SIZE-1] = '\0';

		ch = USART_receive_character(USART3);
		if (ch == 0x0D) //pressed Enter
		{
			USART3_BUFFER[usart3_buffer_iterrator] = '\0';
			usart3_buffer_iterrator = 0;
			USART3_RX_DATA = READY;
			return;
		}
		if (ch == 0x7F) //pressed Backspace
		{
			if (usart3_buffer_iterrator > 0)
			{
				//calculate current length
				uint32_t length;
				length = strlen(USART3_BUFFER);
				usart3_buffer_iterrator--;
				USART3_BUFFER[usart3_buffer_iterrator] = '\0';
				// fill current line spaces
				USART_send_character(USART3, '\r');
				for (uint32_t j = 0; j < length; ++j)
				{
					USART_send_character(USART3, ' ');
				}
				//print new line without deleted character
				USART_send_character(USART3, '\r');
				USART_send_string(USART3, USART3_BUFFER);
			}
		}
		if (ch >= 0x0 && ch <= 0x1F) //processing ASCII control characters
		{
			//TODO
		}
		if (ch > 0x1F && ch < 0x7F)
		{
			USART3_BUFFER[usart3_buffer_iterrator] = ch;
			USART_send_character(USART3, ch); //echo
			if(usart3_buffer_iterrator < USART3_BUFF_MAX_SIZE)
			{
				usart3_buffer_iterrator++;
			}
		}

	}
}

void CAN1_RX0_IRQHandler(void)
{
	CanRxMsg RxMessage;
	memset(&RxMessage, 0, sizeof(RxMessage));

	if (CAN_GetITStatus(CAN1, CAN_IT_FMP0) != RESET)
	{
		CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);

		if (RxMessage.IDE == CAN_Id_Standard)
		{
			if (RxMessage.StdId == CAN_MASSEGE_ID_REQ)
			{
				CAN_transmit_data();
				for (int i=0; i < RxMessage.DLC; i++)
				USART_printf(USART3, "RxMessage.Data[%d] = %c\n\r", i,RxMessage.Data[i]);

			}
			if (RxMessage.StdId == CAN_MASSEGE_ID_RESP)
			{
				GPIO_ToggleBits(LED_PORT, LED_PINS);
			}
		}
	}
}



