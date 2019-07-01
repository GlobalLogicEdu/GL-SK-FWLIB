#ifndef DRIVERS_DISPLAY_WH1602B_4BIT_H_
#define DRIVERS_DISPLAY_WH1602B_4BIT_H_
/*
 	 * https://www.lcd-module.de/eng/pdf/zubehoer/ks0066.pdf
 	 * http://embedded.ifmo.ru/sdk/sdk61/components/lcd/WH1602B-YGK-CP.pdf
*/
#include "clock_config.h"
#include "LEDs.h"
#include "USART.h"
#include <stdio.h>



#define DISPLAY_DELAY (1)

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
#define DISPLAY_MAX_FIRST_LINE			(16) // see documentation (if set to 16 display will shift characters to right)
#define DISPLAY_MAX_SECOND_LINE			(16)


#define BIT_7_MASK	    (0x80)
#define BIT_6_MASK	    (0x40)
#define BIT_5_MASK	    (0x20)
#define BIT_4_MASK	    (0x10)
#define BIT_3_MASK	    (0x08)
#define BIT_2_MASK	    (0x04)
#define BIT_1_MASK	    (0x02)
#define BIT_0_MASK	    (0x01)

// Display instruction (documentation page 28)
#define EMPTY_INSTRUCTION					(0x00)

#define GO_TO_START_FIRST_LINE				(0x80)
#define GO_TO_START_SECOND_LINE				(0xc0)

#define ONE_LINE_MODE						(0x20 | EMPTY_INSTRUCTION)
#define TWO_LINE_MODE						(0x20 | BIT_3_MASK)

#define DISPLAY_OFF							(0x08 | EMPTY_INSTRUCTION)
#define DISPLAY_ON							(0x08 | BIT_2_MASK)
#define CURSOR_OFF							(0x08 | EMPTY_INSTRUCTION)
#define CURSOR_ON							(0x08 | BIT_1_MASK)
#define CURSOR_BLINK_OFF					(0x08 | EMPTY_INSTRUCTION)
#define CURSOR_BLINK_ON						(0x08 | BIT_0_MASK)

#define DISPLAY_CLEAR						(BIT_0_MASK)

#define DECREMENT_MODE						(0x04 | EMPTY_INSTRUCTION)
#define INCREMENT_MODE						(0x04 | BIT_1_MASK)

#define ENTIRE_SHIFT_OFF					(0x04 | EMPTY_INSTRUCTION)
#define ENTIRE_SHIFT_ON						(0x04 | BIT_0_MASK)

// end  Display instruction


#define EMPTY_REGISTER	(uint8_t(0x00))
#define SET_D7			(uint8_t(0x00 & BIT_5_MASK))
#define SET_D6			(uint8_t(0x00 & BIT_4_MASK))
#define SET_D5			(uint8_t(0x00 & BIT_3_MASK))
#define SET_D4			(uint8_t(0x00 & BIT_2_MASK))

void Display_example(void);

void Display_example2(void);

void Display_init_GPIO(void);

void Display_RW_pusle(void);

void Display_Write_Ins(char);

void Display_Write_Data(char);

void Display_Write_Data_Array(char *data, uint8_t length);

void Display_Init();

void Display_Write_srt(char *str, uint8_t length, uint8_t first_line_offset, uint8_t second_line_offset);

void Display_clear(void);

void Display_clear_field(uint8_t size);

void setup_Display(void);

//void Display_ctrl(void);

#endif /* DRIVERS_DISPLAY_WH1602B_4BIT_H_ */
