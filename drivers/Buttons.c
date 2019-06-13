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

void Init_BUTTONs(void)
{
	setup_clock_for_GPIO(GPIOC, ENABLE);
	setup_clock_for_GPIO(GPIOA, ENABLE);
	GPIO_InitTypeDef gpio_button;
	gpio_button.GPIO_Pin = BUTTON_PINS | OK_BUTTON;
	gpio_button.GPIO_OType = GPIO_OType_PP;
	gpio_button.GPIO_Mode = GPIO_Mode_IN;
	gpio_button.GPIO_PuPd = GPIO_PuPd_DOWN;// GPIO_PuPd_UP
	gpio_button.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &gpio_button);
	GPIO_Init(GPIOA, &gpio_button);//for  OK_BUTTON
};

void setup_Interrupt_for_button(GPIO_TypeDef* GPIOx, uint16_t pin_for_BUTTONx, FunctionalState state)
{

}


