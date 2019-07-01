#include "DISPLAY_WH1602B_4Bit.h"
//#include <stdio.h>

static char empty_field[] = "                                ";
void Display_Init()
{
	delay_milis(40);

	Display_Write_Ins(0x02); 	//as per documentation set 4-bit mode
	delay_milis(DISPLAY_DELAY);

//	Display_Write_Ins(0x28);
	Display_Write_Ins(TWO_LINE_MODE);
	delay_milis(DISPLAY_DELAY);

//	Display_Write_Ins(0x0F);
	Display_Write_Ins(DISPLAY_ON | CURSOR_OFF | CURSOR_BLINK_OFF);
	delay_milis(DISPLAY_DELAY);

//	Display_Write_Ins(0x01);
	Display_Write_Ins(DISPLAY_CLEAR);
	delay_milis(DISPLAY_DELAY);

//	Display_Write_Ins(0x06);
	Display_Write_Ins(INCREMENT_MODE | ENTIRE_SHIFT_OFF);
	delay_milis(DISPLAY_DELAY);

}

void Display_Write_Ins(char instruction)
{
	GPIO_ResetBits(DISPLAY_PORT, DISPLAY_RS);
	GPIO_ResetBits(DISPLAY_PORT, DISPLAY_RW);

	instruction & DISPLAY_BIT_7_MASK ? GPIO_SetBits(DISPLAY_PORT, DISPLAY_DB7) : GPIO_ResetBits(DISPLAY_PORT, DISPLAY_DB7);
	instruction & DISPLAY_BIT_6_MASK ? GPIO_SetBits(DISPLAY_PORT, DISPLAY_DB6) : GPIO_ResetBits(DISPLAY_PORT, DISPLAY_DB6);
	instruction & DISPLAY_BIT_5_MASK ? GPIO_SetBits(DISPLAY_PORT, DISPLAY_DB5) : GPIO_ResetBits(DISPLAY_PORT, DISPLAY_DB5);
	instruction & DISPLAY_BIT_4_MASK ? GPIO_SetBits(DISPLAY_PORT, DISPLAY_DB4) : GPIO_ResetBits(DISPLAY_PORT, DISPLAY_DB4);

	Display_RW_pusle();
	delay_milis(DISPLAY_DELAY);

	instruction & DISPLAY_BIT_3_MASK ? GPIO_SetBits(DISPLAY_PORT, DISPLAY_DB7) : GPIO_ResetBits(DISPLAY_PORT, DISPLAY_DB7);
	instruction & DISPLAY_BIT_2_MASK ? GPIO_SetBits(DISPLAY_PORT, DISPLAY_DB6) : GPIO_ResetBits(DISPLAY_PORT, DISPLAY_DB6);
	instruction & DISPLAY_BIT_1_MASK ? GPIO_SetBits(DISPLAY_PORT, DISPLAY_DB5) : GPIO_ResetBits(DISPLAY_PORT, DISPLAY_DB5);
	instruction & DISPLAY_BIT_0_MASK ? GPIO_SetBits(DISPLAY_PORT, DISPLAY_DB4) : GPIO_ResetBits(DISPLAY_PORT, DISPLAY_DB4);

	Display_RW_pusle();
	delay_milis(DISPLAY_DELAY);
}

void Display_Write_Data(char data)
{
	GPIO_SetBits(DISPLAY_PORT, DISPLAY_RS);
	GPIO_ResetBits(DISPLAY_PORT, DISPLAY_RW);

	data & DISPLAY_BIT_7_MASK ? GPIO_SetBits(DISPLAY_PORT, DISPLAY_DB7) : GPIO_ResetBits(DISPLAY_PORT, DISPLAY_DB7);
	data & DISPLAY_BIT_6_MASK ? GPIO_SetBits(DISPLAY_PORT, DISPLAY_DB6) : GPIO_ResetBits(DISPLAY_PORT, DISPLAY_DB6);
	data & DISPLAY_BIT_5_MASK ? GPIO_SetBits(DISPLAY_PORT, DISPLAY_DB5) : GPIO_ResetBits(DISPLAY_PORT, DISPLAY_DB5);
	data & DISPLAY_BIT_4_MASK ? GPIO_SetBits(DISPLAY_PORT, DISPLAY_DB4) : GPIO_ResetBits(DISPLAY_PORT, DISPLAY_DB4);

	Display_RW_pusle();
	delay_milis(DISPLAY_DELAY);

	data & DISPLAY_BIT_3_MASK ? GPIO_SetBits(DISPLAY_PORT, DISPLAY_DB7) : GPIO_ResetBits(DISPLAY_PORT, DISPLAY_DB7);
	data & DISPLAY_BIT_2_MASK ? GPIO_SetBits(DISPLAY_PORT, DISPLAY_DB6) : GPIO_ResetBits(DISPLAY_PORT, DISPLAY_DB6);
	data & DISPLAY_BIT_1_MASK ? GPIO_SetBits(DISPLAY_PORT, DISPLAY_DB5) : GPIO_ResetBits(DISPLAY_PORT, DISPLAY_DB5);
	data & DISPLAY_BIT_0_MASK ? GPIO_SetBits(DISPLAY_PORT, DISPLAY_DB4) : GPIO_ResetBits(DISPLAY_PORT, DISPLAY_DB4);

	Display_RW_pusle();
	delay_milis(DISPLAY_DELAY);
}

void Display_Write_Data_Array(char *data, uint8_t length)
{
	if(length > DISPLAY_MAX_CHARACKTERS_COUNT)
	{
		error_signal(LED_PORT, RED_LED);
	}
	while(length--)
	{
		Display_Write_Data(*data++);
	}
	delay_milis(DISPLAY_DELAY);
}

void Display_init_GPIO(void)
{
	delay_milis(400);
	setup_clock_for_GPIO(DISPLAY_PORT, ENABLE);
	GPIO_InitTypeDef DISPLAY_GPIO;
	DISPLAY_GPIO.GPIO_Mode = GPIO_Mode_OUT;
	DISPLAY_GPIO.GPIO_Speed = GPIO_Speed_50MHz;
	DISPLAY_GPIO.GPIO_OType = GPIO_OType_PP;
	DISPLAY_GPIO.GPIO_PuPd = GPIO_PuPd_NOPULL;

	DISPLAY_GPIO.GPIO_Pin = DISPLAY_RS |  DISPLAY_RW | DISPLAY_ENA | DISPLAY_DB7 | DISPLAY_DB6 | DISPLAY_DB5 | DISPLAY_DB4;
	GPIO_Init(DISPLAY_PORT, &DISPLAY_GPIO);
	GPIO_SetBits(DISPLAY_PORT, DISPLAY_GPIO.GPIO_Pin);
}

//pulse
void Display_RW_pusle(void)
{
    GPIO_SetBits(DISPLAY_PORT, DISPLAY_ENA);
    delay_milis(DISPLAY_DELAY);
    GPIO_ResetBits(DISPLAY_PORT, DISPLAY_ENA);
}

void Display_Write_srt(char *str, uint8_t length, uint8_t first_line_offset, uint8_t second_line_offset)
{
	if(length > DISPLAY_MAX_CHARACKTERS_COUNT)
	{
		error_signal(LED_PORT, RED_LED);
	}

	Display_Write_Ins(GO_TO_START_FIRST_LINE + first_line_offset);

	uint8_t i = 0;

	while(str[i] != '\0' && i < DISPLAY_MAX_FIRST_LINE)
	{
		Display_Write_Data(str[i++]);
	}

	if(i <= length)
	{
		Display_Write_Ins(GO_TO_START_SECOND_LINE + second_line_offset);
		while(str[i] != '\0' && i < DISPLAY_MAX_CHARACKTERS_COUNT)
		{
			Display_Write_Data(str[i++]);
		}
	}

}

void Display_clear(void)
{
	Display_Write_Ins(DISPLAY_CLEAR);
	delay_milis(2);
}


void Display_clear_field(uint8_t size)
{
	while(size--)
	{
		Display_Write_Data(' ');
	}
}

void setup_Display(void)
{
	Display_init_GPIO();
	Display_Init();
}

void Display_example(void)
{
	Display_init_GPIO();

	Display_Init();

	Display_Write_Ins(GO_TO_START_FIRST_LINE);
	Display_Write_Data('H');
	Display_Write_Data('e');
	Display_Write_Data('l');
	Display_Write_Data('l');
	Display_Write_Data('o');
	Display_Write_Data(',');
	Display_Write_Data(' ');
	Display_Write_Data('E');
	Display_Write_Data('m');
	Display_Write_Data('b');
	Display_Write_Data('e');
	Display_Write_Data('d');
	Display_Write_Data('d');
	Display_Write_Data('e');
	Display_Write_Data('d');


	delay_milis(1);

	Display_Write_Ins(GO_TO_START_SECOND_LINE+5);
	Display_Write_Data('N');
	Display_Write_Data('U');
	Display_Write_Data(' ');
	Display_Write_Data('L');
	Display_Write_Data('P');
//	Display_Write_Data(' ');
//	Display_Write_Data('F');
//	Display_Write_Data('O');
//	Display_Write_Data('R');
//	Display_Write_Data('E');
//	Display_Write_Data('V');
//	Display_Write_Data('E');
//	Display_Write_Data('R');
//	Display_Write_Data('!');
//	Display_Write_Data('!');
//	Display_Write_Data('!');
}

void Display_example2(void)
{
	Display_init_GPIO();
	Display_Init();

	char buff[31];
	uint32_t c = 1;
	char *header = "count = ";
	uint8_t header_len = strlen(header);

	Display_clear();
	Display_Write_srt(header ,header_len, 0, 0);
	while(c < 100)
	{
		Display_Write_Ins(GO_TO_START_FIRST_LINE + header_len);
		sprintf(buff, "%ld", c++);
		Display_Write_Data_Array(buff ,strlen(buff));
//		delay_milis(100);
		Display_Write_Data_Array(empty_field ,strlen(buff)); //clear field
	}
	delay_milis(1000);
	c--;
	while(c > 0)
	{
		Display_Write_Ins(GO_TO_START_FIRST_LINE + header_len);
		sprintf(buff, "%ld", c--);
		Display_Write_Data_Array(buff, strlen(buff));
//		delay_milis(100);
		Display_Write_Data_Array(empty_field ,strlen(buff)); //clear field
	}
}

