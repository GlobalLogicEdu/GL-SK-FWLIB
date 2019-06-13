#ifndef DRIVERS__LEDS_H__
#define DRIVERS__LEDS_H__

#include <stm32f4xx_gpio.h>

#define LED_PORT	GPIOD
#define GREEN_LED 	(GPIO_Pin_12)
#define ORANGE_LED 	(GPIO_Pin_13)
#define RED_LED 	(GPIO_Pin_14)
#define BLUE_LED	(GPIO_Pin_15)

#define LED_PINS 		(GREEN_LED | ORANGE_LED | RED_LED | BLUE_LED)



void setup_LED(GPIO_TypeDef* GPIOx, uint16_t pin_for_LEDx);

//void blink_led(GPIO_TypeDef* GPIOx, uint16_t pin_for_LEDx);

void error_signal(GPIO_TypeDef* GPIOx, uint16_t pin_for_LEDx); //set red LED

void success_signal(GPIO_TypeDef* GPIOx, uint16_t pin_for_LEDx); //set green LED

void exception_signal(GPIO_TypeDef* GPIOx, uint16_t pin_for_LEDx); //set orange LED

void event_signal(GPIO_TypeDef* GPIOx, uint16_t pin_for_LEDx); //set blue LED



#endif //DRIVERS__LEDS_H__
