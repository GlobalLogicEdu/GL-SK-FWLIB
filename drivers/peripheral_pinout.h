#ifndef DRIVERS_PERIPHERAL_PINOUT_H_
#define DRIVERS_PERIPHERAL_PINOUT_H_

#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "clock_config.h"

/*-----------------------------------USART PINOUT-----------------------------------*/
#define USART1_PORT		GPIOB
#define USART1_TX 		GPIO_Pin_6			//port B
#define USART1_RX 		GPIO_Pin_7			//port B
#define USART1_TX_AF 	GPIO_PinSource6		//port B (Alternative Function)
#define USART1_RX_AF 	GPIO_PinSource7		//port B (Alternative Function)

#define USART2_PORT		GPIOA
#define USART2_TX 		GPIO_Pin_2			//port A
#define USART2_RX 		GPIO_Pin_3			//port A
#define USART2_TX_AF 	GPIO_PinSource2		//port A (Alternative Function)
#define USART2_RX_AF 	GPIO_PinSource3		//port A (Alternative Function)

#define USART3_PORT		GPIOD
#define USART3_TX		GPIO_Pin_8			//port D
#define USART3_RX 		GPIO_Pin_9			//port D
#define USART3_TX_AF	GPIO_PinSource8		//port D (Alternative Function)
#define USART3_RX_AF	GPIO_PinSource9		//port D (Alternative Function)

#define UART4_PORT		GPIOA
#define UART4_TX 		GPIO_Pin_0			//port A
#define UART4_RX 		GPIO_Pin_1			//port A
#define UART4_TX_AF		GPIO_PinSource0		//port A (Alternative Function)
#define UART4_RX_AF		GPIO_PinSource1		//port A (Alternative Function)

#define UART5_PORT_TX	GPIOC
#define UART5_PORT_RX	GPIOD
#define UART5_TX 		GPIO_Pin_12			//port C
#define UART5_RX 		GPIO_Pin_2			//port D
#define UART5_TX_AF		GPIO_PinSource12	//port C (Alternative Function)
#define UART5_RX_AF 	GPIO_PinSource2		//port D (Alternative Function)

#define USART6_PORT		GPIOC
#define USART6_TX 		GPIO_Pin_6 			//port C
#define USART6_RX 		GPIO_Pin_7 			//port C
#define USART6_TX_AF	GPIO_PinSource6 	//port C (Alternative Function)
#define USART6_RX_AF	GPIO_PinSource7 	//port C (Alternative Function)
/*--------------------------------------------------------------------------------*/

/*-----------------------------------I2C PINOUT-----------------------------------*/
#define I2C1_PORT		GPIOB				//port B
#define I2C1_SDA		GPIO_Pin_9			//port B
#define I2C1_SCL		GPIO_Pin_6			//port B
#define I2C1_SDA_AF		GPIO_PinSource9		//port B (Alternative Function)
#define I2C1_SCL_AF		GPIO_PinSource6		//port B (Alternative Function)
#define PWM_CTRL_ONOFF	GPIO_Pin_7			//port B ENABLE or DISABALE  PWM controller PCA9685PW
#define PWM_CTRL_PORT	GPIOB			//port B ENABLE or DISABALE  PWM controller PCA9685PW

#define I2C2_PORT		GPIOB				//port B
#define I2C2_SDA		GPIO_Pin_11			//port B
#define I2C2_SCL		GPIO_Pin_10			//port B
#define I2C2_SDA_AF		GPIO_PinSource11	//port B (Alternative Function)
#define I2C2_SCL_AF		GPIO_PinSource10	//port B (Alternative Function)

#define I2C3_PORT_SDA	GPIOC				//port B
#define I2C3_PORT_SCL	GPIOA				//port A
#define I2C3_SDA		GPIO_Pin_9			//port B
#define I2C3_SCL		GPIO_Pin_8			//port A
#define I2C3_SDA_AF		GPIO_PinSource9		//port B (Alternative Function)
#define I2C3_SCL_AF		GPIO_PinSource8		//port A (Alternative Function)
/*-------------------------------------------------------------------------------*/

/*-----------------------------------CAN PINOUT-----------------------------------*/
#define CAN1_PORT		GPIOD
#define CAN1_RX			GPIO_Pin_0
#define CAN1_TX			GPIO_Pin_1
#define CAN1_RX_AF		GPIO_PinSource0
#define CAN1_TX_AF		GPIO_PinSource1


#define CAN2_PORT		GPIOD
#define CAN2_RX			GPIO_Pin_0
#define CAN2_TX			GPIO_Pin_1
#define CAN2_RX_AF		GPIO_PinSource0
#define CAN2_TX_AF		GPIO_PinSource1
/*-------------------------------------------------------------------------------*/


void setup_pinout_for_USART(USART_TypeDef *USARTx);
void setup_pinout_for_I2C(I2C_TypeDef *USARTx);
void setup_pinout_for_CAN(CAN_TypeDef *CANx);

#endif /* DRIVERS_PERIPHERAL_PINOUT_H_ */
