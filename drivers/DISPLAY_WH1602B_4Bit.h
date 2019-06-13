#ifndef DRIVERS_DISPLAY_WH1602B_4BIT_H_
#define DRIVERS_DISPLAY_WH1602B_4BIT_H_

// https://www.lcd-module.de/eng/pdf/zubehoer/ks0066.pdf

#include "clock_config.h"
#include "LEDs.h"
#include "USART.h"

#define DISPLAY_DELAY (5)

#define DISPLAY_PORT		GPIOE
#define DISPLAY_RS			GPIO_Pin_7
#define DISPLAY_RW			GPIO_Pin_10
#define DISPLAY_ENA			GPIO_Pin_11
#define DISPLAY_DB4			GPIO_Pin_12
#define DISPLAY_DB5			GPIO_Pin_13
#define DISPLAY_DB6			GPIO_Pin_14
#define DISPLAY_DB7			GPIO_Pin_15
#define DISPLAY_BRIGHTNESS	GPIO_Pin_9 //TIM1_CH1 PWM

#define DISPLAY_BIT_7_MASK	    (0x80)
#define DISPLAY_BIT_6_MASK	    (0x40)
#define DISPLAY_BIT_5_MASK	    (0x20)
#define DISPLAY_BIT_4_MASK	    (0x10)
#define DISPLAY_BIT_3_MASK	    (0x08)
#define DISPLAY_BIT_2_MASK	    (0x04)
#define DISPLAY_BIT_1_MASK	    (0x02)
#define DISPLAY_BIT_0_MASK	    (0x01)

#define DISPLAY_MAX_CHARACKTERS_COUNT	(32)
#define START_FIRST_LINE				(0x80)
#define START_SECOND_LINE				(0xc0)

#define BIT_7_MASK	    (0x80)
#define BIT_6_MASK	    (0x40)
#define BIT_5_MASK	    (0x20)
#define BIT_4_MASK	    (0x10)
#define BIT_3_MASK	    (0x08)
#define BIT_2_MASK	    (0x04)
#define BIT_1_MASK	    (0x02)
#define BIT_0_MASK	    (0x01)

#define EMPTY_REGISTER	(uint8_t(0x00))
#define SET_D7			(uint8_t(0x00 & BIT_5_MASK))
#define SET_D6			(uint8_t(0x00 & BIT_4_MASK))
#define SET_D5			(uint8_t(0x00 & BIT_3_MASK))
#define SET_D4			(uint8_t(0x00 & BIT_2_MASK))

void Display_example(void);

void Display_init_GPIO(void);

void Display_RW_pusle(void);

void Display_Write_Ins(char);

void Display_Write_Data(char);

void Display_Init();

#endif /* DRIVERS_DISPLAY_WH1602B_4BIT_H_ */
