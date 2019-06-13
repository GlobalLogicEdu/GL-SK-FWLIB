#include "DISPLAY_WH1602B_4Bit.h"



void Display_Init()
{
	Display_Write_Ins(0x20);//As per specification
	delay_milis(DISPLAY_DELAY);
	Display_Write_Ins(0x28);
	delay_milis(DISPLAY_DELAY);
	Display_Write_Ins(0x28);
	delay_milis(DISPLAY_DELAY);
	Display_Write_Ins(0x0f);
	delay_milis(DISPLAY_DELAY);
	Display_Write_Ins(0x01);
	delay_milis(DISPLAY_DELAY);
	Display_Write_Ins(0x06);
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
//	GPIO_SetBits(DISPLAY_PORT, DISPLAY_DB4 | DISPLAY_DB5 | DISPLAY_DB6 | DISPLAY_DB7);

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

void Display_init_GPIO(void)
{
	delay_milis1(40);
	setup_clock_for_GPIO(DISPLAY_PORT, ENABLE);
	GPIO_InitTypeDef DISPLAY_GPIO;
	DISPLAY_GPIO.GPIO_Mode = GPIO_Mode_OUT;
	DISPLAY_GPIO.GPIO_Speed = GPIO_Speed_50MHz;
	DISPLAY_GPIO.GPIO_OType = GPIO_OType_PP;
	DISPLAY_GPIO.GPIO_PuPd = GPIO_PuPd_NOPULL;

	DISPLAY_GPIO.GPIO_Pin = DISPLAY_RS |  DISPLAY_RW | DISPLAY_ENA | DISPLAY_DB7 | DISPLAY_DB6 | DISPLAY_DB5 | DISPLAY_DB4;
	GPIO_Init(DISPLAY_PORT, &DISPLAY_GPIO);
	GPIO_ResetBits(DISPLAY_PORT, DISPLAY_GPIO.GPIO_Pin);
}

//pulse
void Display_RW_pusle(void)
{
    GPIO_SetBits(DISPLAY_PORT, DISPLAY_ENA);
    delay_milis(DISPLAY_DELAY);
    GPIO_ResetBits(DISPLAY_PORT, DISPLAY_ENA);
}

void Display_example(void)
{
	Display_init_GPIO();

	Display_Init();

	Display_Write_Ins(START_FIRST_LINE);
	Display_Write_Data('H');
	Display_Write_Data('e');
	Display_Write_Data('l');
	Display_Write_Data('l');
	Display_Write_Data('o');
	Display_Write_Data(',');
	delay_milis(40);
	Display_Write_Ins(START_SECOND_LINE);
	Display_Write_Data('E');
	Display_Write_Data('m');
	Display_Write_Data('b');
	Display_Write_Data('e');
	Display_Write_Data('d');
	Display_Write_Data('d');
	Display_Write_Data('e');
	Display_Write_Data('d');
	Display_Write_Data('!');
}

