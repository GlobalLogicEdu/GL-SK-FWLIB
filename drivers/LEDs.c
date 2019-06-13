#include "clock_config.h"
#include "LEDs.h"


void setup_LED(GPIO_TypeDef* GPIOx, uint16_t pin_for_LEDx)
{
	setup_clock_for_GPIO(GPIOx, ENABLE);
	GPIO_InitTypeDef gpio_led;
	gpio_led.GPIO_Pin = pin_for_LEDx;
	gpio_led.GPIO_OType = GPIO_OType_PP;
	gpio_led.GPIO_Mode = GPIO_Mode_OUT;
	gpio_led.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_led.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx, &gpio_led);
	GPIO_ResetBits(GPIOx, pin_for_LEDx);
}

void error_signal(GPIO_TypeDef* GPIOx, uint16_t pin_for_LEDx)
{
	GPIO_SetBits(GPIOx, pin_for_LEDx);
}

void success_signal(GPIO_TypeDef* GPIOx, uint16_t pin_for_LEDx)
{
	GPIO_SetBits(GPIOx, pin_for_LEDx);
}

void exception_signal(GPIO_TypeDef* GPIOx, uint16_t pin_for_LEDx)
{
	GPIO_SetBits(GPIOx, pin_for_LEDx);
}

void event_signal(GPIO_TypeDef* GPIOx, uint16_t pin_for_LEDx)
{
	GPIO_SetBits(GPIOx, pin_for_LEDx);
}
