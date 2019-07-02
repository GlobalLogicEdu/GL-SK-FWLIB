#include "peripheral_pinout.h"

void setup_pinout_for_USART(USART_TypeDef *USARTx)
{
	GPIO_InitTypeDef UART_GPIO;
	UART_GPIO.GPIO_OType 	= GPIO_OType_OD;
	UART_GPIO.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	UART_GPIO.GPIO_Speed 	= GPIO_Speed_50MHz;
	UART_GPIO.GPIO_Mode 	= GPIO_Mode_AF;
	switch ((int)USARTx) {
		case (int)USART1:
			UART_GPIO.GPIO_Pin = USART1_TX | USART1_RX;
			setup_clock_for_GPIO(USART1_PORT, ENABLE);
			GPIO_Init(USART1_PORT, &UART_GPIO);
			GPIO_PinAFConfig(USART1_PORT, USART1_TX_AF, GPIO_AF_USART1);
			GPIO_PinAFConfig(USART1_PORT, USART1_RX_AF, GPIO_AF_USART1);
			break;

		case (int)USART2:
			UART_GPIO.GPIO_Pin = USART2_TX | USART2_RX;
			setup_clock_for_GPIO(USART2_PORT, ENABLE);
			GPIO_Init(USART2_PORT, &UART_GPIO);
			GPIO_PinAFConfig(USART2_PORT, USART2_TX_AF, GPIO_AF_USART2);
			GPIO_PinAFConfig(USART2_PORT, USART2_RX_AF, GPIO_AF_USART2);
			break;

		case (int)USART3:
			UART_GPIO.GPIO_Pin = USART3_TX | USART3_RX;
			setup_clock_for_GPIO(USART3_PORT, ENABLE);
		 	GPIO_Init(USART3_PORT, &UART_GPIO);
		 	GPIO_PinAFConfig(USART3_PORT, USART3_TX_AF, GPIO_AF_USART3);
		 	GPIO_PinAFConfig(USART3_PORT, USART3_RX_AF, GPIO_AF_USART3);
			break;

		case (int)UART4:
			UART_GPIO.GPIO_Pin = UART4_TX | UART4_RX;
			setup_clock_for_GPIO(UART4_PORT, ENABLE);
			GPIO_Init(UART4_PORT, &UART_GPIO);
			GPIO_PinAFConfig(UART4_PORT, UART4_TX_AF, GPIO_AF_UART4);
			GPIO_PinAFConfig(UART4_PORT, UART4_RX_AF, GPIO_AF_UART4);
			break;

		case (int)UART5:
			UART_GPIO.GPIO_Pin = UART5_TX;
			setup_clock_for_GPIO(UART5_PORT_TX, ENABLE);
			GPIO_Init(UART5_PORT_TX, &UART_GPIO);
			UART_GPIO.GPIO_Pin = UART5_RX;
			setup_clock_for_GPIO(UART5_PORT_RX, ENABLE);
			GPIO_Init(UART5_PORT_RX, &UART_GPIO);
			GPIO_PinAFConfig(UART5_PORT_TX, UART4_TX_AF, GPIO_AF_UART5);
			GPIO_PinAFConfig(UART5_PORT_RX, UART4_RX_AF, GPIO_AF_UART5);
			break;

		case (int)USART6:
			UART_GPIO.GPIO_Pin = USART6_TX | USART6_RX;
			setup_clock_for_GPIO(USART6_PORT, ENABLE);
			GPIO_Init(USART6_PORT, &UART_GPIO);
			GPIO_PinAFConfig(USART6_PORT, USART6_TX_AF, GPIO_AF_USART6);
			GPIO_PinAFConfig(USART6_PORT, USART6_RX_AF, GPIO_AF_USART6);
			break;

		default:
			break;
	}
}
void setup_pinout_for_I2C(I2C_TypeDef *I2Cx)
{
	GPIO_InitTypeDef I2C_GPIO;
	I2C_GPIO.GPIO_OType = GPIO_OType_OD;
	I2C_GPIO.GPIO_PuPd 	= GPIO_PuPd_UP;
	I2C_GPIO.GPIO_Speed	= GPIO_Speed_50MHz;
	I2C_GPIO.GPIO_Mode 	= GPIO_Mode_AF;
	switch ((int)I2Cx) {
		case (int)I2C1:
			I2C_GPIO.GPIO_Pin = I2C1_SDA | I2C1_SCL;
			setup_clock_for_GPIO(I2C1_PORT, ENABLE);
			GPIO_Init(I2C1_PORT, &I2C_GPIO);
			GPIO_PinAFConfig(I2C1_PORT, I2C1_SDA_AF, GPIO_AF_I2C1);
			GPIO_PinAFConfig(I2C1_PORT, I2C1_SCL_AF, GPIO_AF_I2C1);
			I2C_GPIO.GPIO_Pin = PWM_CTRL_ONOFF;
			setup_clock_for_GPIO(PWM_CTRL_PORT, ENABLE);
			GPIO_Init(PWM_CTRL_PORT, &I2C_GPIO);
			break;

		case (int)I2C2:
			I2C_GPIO.GPIO_Pin = I2C2_SDA | I2C2_SCL;
			setup_clock_for_GPIO(I2C2_PORT, ENABLE);
			GPIO_Init(I2C2_PORT, &I2C_GPIO);
			GPIO_PinAFConfig(I2C2_PORT, I2C2_SDA_AF, GPIO_AF_I2C2);
			GPIO_PinAFConfig(I2C2_PORT, I2C2_SCL_AF, GPIO_AF_I2C2);
			break;

		case (int)I2C3:
			I2C_GPIO.GPIO_Pin = I2C3_SDA;
			setup_clock_for_GPIO(I2C3_PORT_SDA, ENABLE);
			setup_clock_for_GPIO(I2C3_PORT_SCL, ENABLE);
			GPIO_Init(I2C3_PORT_SDA, &I2C_GPIO);
			I2C_GPIO.GPIO_Pin = I2C3_SCL;
			GPIO_Init(I2C3_PORT_SCL, &I2C_GPIO);
			GPIO_PinAFConfig(I2C3_PORT_SDA, I2C3_SDA_AF, GPIO_AF_I2C3);
			GPIO_PinAFConfig(I2C3_PORT_SCL, I2C2_SCL_AF, GPIO_AF_I2C3);
			break;

		default:
			break;
	}
}

void setup_pinout_for_CAN(CAN_TypeDef *CANx)
{
	GPIO_InitTypeDef CAN_GPIO;
	CAN_GPIO.GPIO_OType = GPIO_OType_OD;
	CAN_GPIO.GPIO_PuPd 	= GPIO_PuPd_UP;
	CAN_GPIO.GPIO_Speed	= GPIO_Speed_50MHz;
	CAN_GPIO.GPIO_Mode 	= GPIO_Mode_AF;
	switch ((int)CANx) {
		case (int)CAN1:
				CAN_GPIO.GPIO_Pin = CAN1_TX | CAN1_RX;
			setup_clock_for_GPIO(CAN1_PORT, ENABLE);
			GPIO_Init(CAN1_PORT, &CAN_GPIO);
			GPIO_PinAFConfig(CAN1_PORT, CAN1_TX_AF, GPIO_AF_CAN1);
			GPIO_PinAFConfig(CAN1_PORT, CAN1_RX_AF, GPIO_AF_CAN1);
			break;
		case (int) CAN2:
			CAN_GPIO.GPIO_Pin = CAN2_TX | CAN2_RX;
			setup_clock_for_GPIO(CAN1_PORT, ENABLE);
			GPIO_Init(CAN2_PORT, &CAN_GPIO);
			GPIO_PinAFConfig(CAN2_PORT, CAN2_TX_AF, GPIO_AF_CAN1);
			GPIO_PinAFConfig(CAN2_PORT, CAN2_RX_AF, GPIO_AF_CAN1);
			break;
		default:
			break;
	}


}

