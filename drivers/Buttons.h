#ifndef DRIVERS_BUTTONS_H_
#define DRIVERS_BUTTONS_H_

#include <stm32f4xx_gpio.h>


#define UP_DOWN_LEFT_RIGHT_PORT		GPIOC
#define CENTER_BUTTON_PORT			GPIOA
#define USER_BUTTON_PORT			GPIOA

#define USER_DISCO_BUTTON			(GPIO_Pin_0)
#define UP_BUTTON 					(GPIO_Pin_6)
#define DOWN_BUTTON 				(GPIO_Pin_8)
#define LEFT_BUTTON					(GPIO_Pin_9)
#define RIGHT_BUTTON 				(GPIO_Pin_11)
#define CENTER_BUTTON				(GPIO_Pin_15)

//#define USER_DISCO_BUTTON_EXTI_LINE				(GPIO_Pin_0)
//#define UP_BUTTON_EXTI_LINE						(GPIO_Pin_6)
//#define DOWN_BUTTON_EXTI_LINE					(GPIO_Pin_8)
//#define LEFT_BUTTON_EXTI_LINE					(GPIO_Pin_9)
//#define RIGHT_BUTTON_EXTI_LINE					(GPIO_Pin_11)
//#define CENTER_BUTTON_EXTI_LINE					(GPIO_Pin_15)

#define BUTTON_PINS 	(UP_BUTTON | DOWN_BUTTON | LEFT_BUTTON | RIGHT_BUTTON)
#define OK_BUTTON 		(CENTER_BUTTON)

uint8_t UP_BUTTON_state;
uint8_t DOWN_BUTTON_state;
uint8_t LEFT_BUTTON_state;
uint8_t RIGHT_BUTTON_state;

uint8_t OK_BUTTON_state;
uint8_t USER_BUTTON_state;

void Init_BUTTON(GPIO_TypeDef* GPIOx, uint16_t pin_for_BUTTONx);

void setup_Interrupt_for_button(GPIO_TypeDef* GPIOx, uint16_t pin_for_BUTTONx, FunctionalState state);

void Init_ONBOARD_BUTTONs(void);



#endif //DRIVERS_BUTTONS_H_
