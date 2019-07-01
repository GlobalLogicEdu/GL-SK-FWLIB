#include "CAN_BUS.h"

void setup_CAN(void)
{
	setup_clock_for_CAN(CAN1, ENABLE);
	setup_pinout_for_CAN(CAN1);
	CAN_BUS_init();
}

void CAN_BUS_init(void)
{
    CAN_InitTypeDef CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;

    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = DISABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = ENABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;//CAN_Mode_LoopBack;//CAN_Mode_Normal//CAN_Mode_Silent_LoopBack
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStructure.CAN_BS1 = CAN_BS1_9tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
    CAN_InitStructure.CAN_Prescaler = 1;
    CAN_Init(CAN1, &CAN_InitStructure);

//	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0401 << 5;
//	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
//	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xFFFF;
//	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0xFFFF;
	CAN_FilterInitStructure.CAN_FilterNumber = 0;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);

//	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
//
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

}

void CAN_transmit_data(void)
{
	CanTxMsg TxMessage;
	TxMessage.StdId = CAN_MASSEGE_ID_REQ;

	TxMessage.ExtId = 0x00;

	TxMessage.IDE = CAN_Id_Standard;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 3;

	TxMessage.Data[0] = 0x31;
	TxMessage.Data[1] = 0x32;
	TxMessage.Data[2] = 0x33;

	CAN_Transmit(CAN1, &TxMessage);

}

void CAN_receive_data(void)
{
	CanRxMsg RxMessage;
	RxMessage.DLC = 	0x00;
	RxMessage.ExtId = 	0x00;
	RxMessage.FMI = 	0x00;
	RxMessage.IDE = 	0x00;
	RxMessage.RTR = 	0x00;
	RxMessage.StdId = 	0x00;
	RxMessage.Data [0] = 0x00;
	RxMessage.Data [1] = 0x00;
	RxMessage.Data [2] = 0x00;
	RxMessage.Data [3] = 0x00;
	RxMessage.Data [4] = 0x00;
	RxMessage.Data [5] = 0x00;
	RxMessage.Data [6] = 0x00;
	RxMessage.Data [7] = 0x00;

	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);


	USART_printf(USART3, "DATA[0] = %x\n\r", RxMessage.Data[0]);
	USART_printf(USART3, "DATA[1] = %x\n\r", RxMessage.Data[1]);
	USART_printf(USART3, "DATA[2] = %x\n\r", RxMessage.Data[2]);
	CAN_FIFORelease(CAN1, CAN_FIFO0);
}

void CAN_example(void)
{
	setup_USART(USART3, INTERRUPT_DISABLE);
	setup_LED(LED_PORT, LED_PINS);
	setup_CAN();
	while(1)
	{
		CAN_transmit_data();
		CAN_receive_data();
		delay_milis(500);
	}

}
