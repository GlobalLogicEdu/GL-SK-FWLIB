#include "clock_config.h"
static RCC_ClocksTypeDef RCC_Clocks;

void setup_clock_to_168MHz(void)
{

	RCC_HSEConfig(RCC_HSE_ON);
	while( RCC_WaitForHSEStartUp() == ERROR ){}
	RCC_PLLConfig(RCC_PLLSource_HSE, M_DIVIDER, N_MULIPLICATOR, P_DIVIDER, Q_DIVIDER);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div4);
	RCC_PCLK2Config(RCC_HCLK_Div2);
	RCC_PLLCmd(ENABLE);
	/*SysTick config*/

//	RCC_ClocksTypeDef RCC_Clocks;
//	RCC_GetClocksFreq(&RCC_Clocks);
//	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

	/*SysTick config*/
}


void delay_milis1(uint32_t milisecond)
{
//	RCC_GetClocksFreq(&RCC_Clocks);
//	timing_dalay = RCC_Clocks.HCLK_Frequency/1000 * milisecond;
//	while(timing_dalay--);
}

void delay_milis(uint32_t milisecond)
{
//	RCC_GetClocksFreq(&RCC_Clocks);
//	timing_dalay = RCC_Clocks.HCLK_Frequency/10000000 * microsecond;
//	while(timing_dalay--);
//	timing_dalay = microsecond;
//	while(timing_dalay);
	RCC_GetClocksFreq(&RCC_Clocks);
	timing_dalay = RCC_Clocks.HCLK_Frequency/10000 * milisecond;
	while(timing_dalay--);
}

void setup_clock_for_GPIO(GPIO_TypeDef* GPIOx, FunctionalState state)
{
	switch ((int)GPIOx) {
		case (int)GPIOA:
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, state); //APB1
			break;
		case (int)GPIOB:
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, state); //APB1
			break;
		case (int)GPIOC:
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, state); //APB1
			break;
		case (int)GPIOD:
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, state); //APB1
			break;
		case (int)GPIOE:
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, state); //APB1
			break;
		default:
			break;
	}
}

void setup_clock_for_USART(USART_TypeDef *USARTx, FunctionalState state)
{
	switch ((int)USARTx) {
		case (int)USART1:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 ,state);  //APB2
			break;
		case (int)USART2:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 ,state);  //APB1
			break;
		case (int)USART3:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 ,state);  //APB1
			break;
		case (int)UART4:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4 ,state);  //APB1
			break;
		case (int)UART5:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5 ,state);  //APB1
			break;
		case (int)USART6:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6 ,state); //APB2
			break;

		default:
			break;
	}
}

void setup_clock_for_I2C(I2C_TypeDef *I2Cx, FunctionalState state)
{
	switch ((int)I2Cx) {
		case (int)I2C1:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, state); //APB1
			break;
		case (int)I2C2:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, state); //APB1
			break;
		case (int)I2C3:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C3, state); //APB1
			break;
		default:
			break;
	}
}

void setup_clock_for_TIMERs(TIM_TypeDef *TIMx, FunctionalState state)
{
	switch ((int)TIMx) {
		case (int)TIM1:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, state); //APB2
			break;
		case (int)TIM2:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, state); //APB1
			break;
		case (int)TIM3:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, state); //APB1
			break;
		case (int)TIM4:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, state); //APB1
			break;
		case (int)TIM5:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, state); //APB1
			break;
		case (int)TIM6:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, state); //APB1
			break;
		case (int)TIM7:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, state); //APB1
			break;
		case (int)TIM8:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, state); //APB2
			break;
		case (int)TIM9:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, state); //APB2
			break;
		case (int)TIM10:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, state); //APB2
			break;
		case (int)TIM11:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, state); //APB2
			break;
		case (int)TIM12:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, state); //APB1
			break;
		case (int)TIM13:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, state); //APB1
			break;
		case (int)TIM14:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, state); //APB1
			break;
		default:
			break;
	}

}

void setup_clock_for_CAN(CAN_TypeDef *CANx, FunctionalState state)
{
	switch ((int)CANx) {
		case (int)CAN1:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, state); //APB1
			break;
		case (int)CAN2:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, state); //APB1
		default:
			break;
	}
}
