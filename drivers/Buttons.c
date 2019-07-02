#include "Buttons.h"
#include "clock_config.h"


void Init_BUTTON(GPIO_TypeDef* GPIOx, uint16_t pin_for_BUTTONx)
{
	setup_clock_for_GPIO(GPIOx, ENABLE);
	GPIO_InitTypeDef gpio_button;
	gpio_button.GPIO_Pin = pin_for_BUTTONx;
	gpio_button.GPIO_OType = GPIO_OType_OD;
	gpio_button.GPIO_Mode = GPIO_Mode_IN;
	gpio_button.GPIO_PuPd = GPIO_PuPd_DOWN;// GPIO_PuPd_UP
	gpio_button.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx, &gpio_button);
};

void Init_ONBOARD_BUTTONs(void)
{
	setup_clock_for_GPIO(GPIOC, ENABLE);
	setup_clock_for_GPIO(GPIOA, ENABLE);
	GPIO_InitTypeDef gpio_button;
	gpio_button.GPIO_Pin = BUTTON_PINS;
	gpio_button.GPIO_OType = GPIO_OType_PP;
	gpio_button.GPIO_Mode = GPIO_Mode_IN;
	gpio_button.GPIO_PuPd = GPIO_PuPd_DOWN;// GPIO_PuPd_UP
	gpio_button.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &gpio_button);
	gpio_button.GPIO_Pin = USER_DISCO_BUTTON | OK_BUTTON;
	GPIO_Init(GPIOA, &gpio_button);//for  OK_BUTTON and USER_DISCO_BUTTON

	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource15);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource6);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource8);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource9);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource11);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

	EXTI_InitStruct.EXTI_Line = EXTI_Line6 | EXTI_Line8 | EXTI_Line9;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;

	NVIC_Init(&NVIC_InitStruct);
	EXTI_Init(&EXTI_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	EXTI_InitStruct.EXTI_Line = EXTI_Line11 | EXTI_Line15;

	NVIC_Init(&NVIC_InitStruct);
	EXTI_Init(&EXTI_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;

	NVIC_Init(&NVIC_InitStruct);
	EXTI_Init(&EXTI_InitStruct);
};




