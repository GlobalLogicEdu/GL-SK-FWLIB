/*
 * MEMS.c
 *
 *  Created on: Jun 29, 2019
 *      Author: serhiy
 */
#include "MEMS.h"
#include "DISPLAY_WH1602B_4Bit.h"
#include "Buttons.h"

void MEMS_set_mode(MEMS_Mode mode)
{
	switch (mode) {
		case ACCELEROMETER:
			I2C_transmit_byte_to_reg(MEMS_I2C_PERIPH, MEMS_ACCEL_SLAVE_ADDRESS, CTRL_REG6_XL, ODR_MASK_952_HZ | ACCEL_SCALE_SELECTION_MASK_16G | ACCEL_BANDWIDTH_MASK_408_HZ);
			break;
		case ACCELEROMETER_AND_GYROSCOPE:
			I2C_transmit_byte_to_reg(MEMS_I2C_PERIPH, MEMS_ACCEL_SLAVE_ADDRESS, CTRL_REG1_G, ODR_MASK_952_HZ | GYRO_SCALE_SELECTION_MASK_245_DPS | GYRO_BANDWIDTH_MASK_0);
			break;
		case MAGNETOMETR:
			I2C_transmit_byte_to_reg(MEMS_I2C_PERIPH, MEMS_MAGNETIC_SLAVE_ADDRESS,  CTRL_REG1_M,  0x1C);
			I2C_transmit_byte_to_reg(MEMS_I2C_PERIPH, MEMS_MAGNETIC_SLAVE_ADDRESS,  CTRL_REG3_M,  MAGNETIC_OPERATING_MODE_CC_MASK);

			break;
		case POWER_DOWN:
			I2C_transmit_byte_to_reg(MEMS_I2C_PERIPH, MEMS_ACCEL_SLAVE_ADDRESS, CTRL_REG1_G, ODR_MASK_POWER_DOWN);
			I2C_transmit_byte_to_reg(MEMS_I2C_PERIPH, MEMS_ACCEL_SLAVE_ADDRESS, CTRL_REG6_XL, ODR_MASK_POWER_DOWN);
			break;
		default:
			break;
	}
}

void MEMS_Axis_state_ACCEL(void)
{
	I2C_transmit_byte_to_reg(MEMS_I2C_PERIPH, MEMS_ACCEL_SLAVE_ADDRESS, CTRL_REG5_XL, ACCEL_MASK_X_ENABLE | ACCEL_MASK_Y_ENABLE | ACCEL_MASK_Z_ENABLE);
}

void MEMS_Axis_state_GYRO(void)
{
	I2C_transmit_byte_to_reg(MEMS_I2C_PERIPH, MEMS_ACCEL_SLAVE_ADDRESS, CTRL_REG4, ACCEL_MASK_X_ENABLE | ACCEL_MASK_Y_ENABLE | ACCEL_MASK_Z_ENABLE);
}


void MEMS_Init(void)
{
	MEMS_set_mode(ACCELEROMETER);
	MEMS_set_mode(ACCELEROMETER_AND_GYROSCOPE);
	MEMS_set_mode(MAGNETOMETR);
//	MEMS_set_mode(POWER_DOWN);
	MEMS_Axis_state_ACCEL();
	MEMS_Axis_state_GYRO();
}

void MEMS_read_GYROSCOPE(MEMS_data *data)
{
	uint8_t tmp = 0;
	int16_t buff = 0;
	data->X = 0; data->Y = 0; data->Z = 0;

	I2C_receive_byte_from_reg(MEMS_I2C_PERIPH, MEMS_ACCEL_SLAVE_ADDRESS, OUT_X_H_G, &tmp);
	buff = tmp; buff <<= 8;
//	data->X = tmp; data->X <<= 8;
	I2C_receive_byte_from_reg(MEMS_I2C_PERIPH, MEMS_ACCEL_SLAVE_ADDRESS, OUT_X_L_G, &tmp);
	buff |= tmp;
//	data->X |= tmp;
	data->X = (float)(((0.732)*(float)(buff))/100);

	tmp=0;
	I2C_receive_byte_from_reg(MEMS_I2C_PERIPH, MEMS_ACCEL_SLAVE_ADDRESS, OUT_Y_H_G, &tmp);
	buff = tmp; buff <<= 8;
//	data->Y = tmp; data->Y <<= 8;
	I2C_receive_byte_from_reg(MEMS_I2C_PERIPH, MEMS_ACCEL_SLAVE_ADDRESS, OUT_Y_L_G, &tmp);
	buff |= tmp;
//	data->Y |= tmp;
	data->Y = (float)(((0.732)*(float)(buff))/100);

	tmp=0;
	I2C_receive_byte_from_reg(MEMS_I2C_PERIPH, MEMS_ACCEL_SLAVE_ADDRESS, OUT_Z_H_G, &tmp);
	buff = tmp; buff <<= 8;
//	data->Z = tmp; data->Z <<= 8;
	I2C_receive_byte_from_reg(MEMS_I2C_PERIPH, MEMS_ACCEL_SLAVE_ADDRESS, OUT_Z_L_G, &tmp);
	buff |= tmp;
//	data->Z |= tmp;
	data->Z = (float)(((0.732)*(float)(buff))/100);

}

void MEMS_read_ACCELEROMETR(MEMS_data *data)
{
	uint8_t tmp = 0;
	int16_t buff = 0;
	data->X = 0; data->Y = 0; data->Z = 0;

	I2C_receive_byte_from_reg(MEMS_I2C_PERIPH, MEMS_ACCEL_SLAVE_ADDRESS, OUT_X_H_XL, &tmp);
	buff = tmp; buff <<= 8;
//	data->X = tmp; data->X <<= 8;
	I2C_receive_byte_from_reg(MEMS_I2C_PERIPH, MEMS_ACCEL_SLAVE_ADDRESS, OUT_X_L_XL, &tmp);
	buff |= tmp;
//	data->X |= tmp;
	data->X = (float)(((0.061)*(float)(buff)));

	tmp=0;
	I2C_receive_byte_from_reg(MEMS_I2C_PERIPH, MEMS_ACCEL_SLAVE_ADDRESS, OUT_Y_H_XL, &tmp);
	buff = tmp; buff <<= 8;
//	data->Y = tmp; data->Y <<= 8;
	I2C_receive_byte_from_reg(MEMS_I2C_PERIPH, MEMS_ACCEL_SLAVE_ADDRESS, OUT_Y_L_XL, &tmp);
	buff |= tmp;
//	data->Y |= tmp;
	data->Y = (float)(((0.061)*(float)(buff)));

	tmp=0;
	I2C_receive_byte_from_reg(MEMS_I2C_PERIPH, MEMS_ACCEL_SLAVE_ADDRESS, OUT_Z_H_XL, &tmp);
	buff = tmp; buff <<= 8;
//	data->Z = tmp; data->Z <<= 8;
	I2C_receive_byte_from_reg(MEMS_I2C_PERIPH, MEMS_ACCEL_SLAVE_ADDRESS, OUT_Z_L_XL, &tmp);
	buff |= tmp;
//	data->Z |= tmp;
	data->Z = (float)(((0.061)*(float)(buff)));

}


void MEMS_read_MAGNETOMETR(MEMS_data *data)
{
	uint8_t tmp = 0;
	int16_t buff = 0;
	data->X = 0; data->Y = 0; data->Z = 0;

	I2C_receive_byte_from_reg(MEMS_I2C_PERIPH, MEMS_MAGNETIC_SLAVE_ADDRESS, OUT_X_H_M, &tmp);
	buff = tmp; buff <<= 8;
//	data->X = tmp; data->X <<= 8;
	I2C_receive_byte_from_reg(MEMS_I2C_PERIPH, MEMS_MAGNETIC_SLAVE_ADDRESS, OUT_X_L_M, &tmp);
	buff |= tmp;
//	data->X |= tmp;
	data->X = (float)(((0.14)*(float)(buff))/100);

	tmp=0;
	I2C_receive_byte_from_reg(MEMS_I2C_PERIPH, MEMS_MAGNETIC_SLAVE_ADDRESS, OUT_Y_H_M, &tmp);
	buff = tmp; buff <<= 8;
//	data->Y = tmp; data->Y <<= 8;
	I2C_receive_byte_from_reg(MEMS_I2C_PERIPH, MEMS_MAGNETIC_SLAVE_ADDRESS, OUT_Y_L_M, &tmp);
	buff |= tmp;
//	data->Y |= tmp;
	data->Y = (float)(((0.14)*(float)(buff))/100);

	tmp=0;
	I2C_receive_byte_from_reg(MEMS_I2C_PERIPH, MEMS_MAGNETIC_SLAVE_ADDRESS, OUT_Z_H_M, &tmp);
	buff = tmp; buff <<= 8;
//	data->Z = tmp; data->Z <<= 8;
	I2C_receive_byte_from_reg(MEMS_I2C_PERIPH, MEMS_MAGNETIC_SLAVE_ADDRESS, OUT_Z_L_M, &tmp);
	buff |= tmp;
//	data->Z |= tmp;
	data->Z = (float)(((0.14)*(float)(buff))/100);
}

void setup_MEMS(void)
{
//	setup_Display();
	setup_I2C(I2C1);
	MEMS_Init();
}

void MEMS_example(void)
{
	setup_Display();
	setup_MEMS();
	MEMS_Init();
	MEMS_data XYZ;
	char tmp[32];


	//	uint16_t x=0, y=10, z=100;
	uint16_t len = 0;
	Display_Write_Ins(GO_TO_START_FIRST_LINE);
	Display_Write_Data_Array("x=", 2);

	Display_Write_Ins(GO_TO_START_FIRST_LINE+8);
	Display_Write_Data_Array("y=", 2);
	Display_Write_Ins(GO_TO_START_SECOND_LINE);
	Display_Write_Data_Array("z=", 2);

	Display_Write_Ins(GO_TO_START_SECOND_LINE+8);
	Display_Write_Data_Array("MODE=", 5);

	while(1)
	{
//		MEMS_read_GYROSCOPE(&XYZ);
//		MEMS_read_ACCELEROMETR(&XYZ);
		MEMS_read_MAGNETOMETR(&XYZ);
		sprintf(tmp, "%.1f", XYZ.X);
		len = strlen(tmp);
		Display_Write_Ins(GO_TO_START_FIRST_LINE+2);
		Display_clear_field(6);
		Display_Write_Ins(GO_TO_START_FIRST_LINE+2);
		Display_Write_Data_Array(tmp, len);

		sprintf(tmp, "%.1f", XYZ.Y);
		len = strlen(tmp);
		Display_Write_Ins(GO_TO_START_FIRST_LINE+8+2);
		Display_clear_field(6);
		Display_Write_Ins(GO_TO_START_FIRST_LINE+8+2);
		Display_Write_Data_Array(tmp, len);

		sprintf(tmp, "%.1f", XYZ.Z);
		len = strlen(tmp);
		Display_Write_Ins(GO_TO_START_SECOND_LINE+2);
		Display_clear_field(6);
		Display_Write_Ins(GO_TO_START_SECOND_LINE+2);
		Display_Write_Data_Array(tmp, len);

		sprintf(tmp, "ALL");
		len = strlen(tmp);
		Display_Write_Ins(GO_TO_START_SECOND_LINE+8+5);
		Display_clear_field(6);
		Display_Write_Ins(GO_TO_START_SECOND_LINE+8+5);
		Display_Write_Data_Array(tmp, len);

	}
}

void MEMS_example_with_menu(void)
{
	Init_ONBOARD_BUTTONs();
	setup_Display();
	char MEMS_modes_list[3][16] = {"ACCELEROMETER", "GYROSCOPE", "MAGNETOMETER"};
	char MEMS_axises_list[4][16] = {"Only X", "Only Y", "Only Z", "All axises"};
	Display_Write_Ins(GO_TO_START_FIRST_LINE);
	Display_Write_Data_Array("<----[MODE]---->", 16);


	uint8_t i = 0, select = 1;
	MEMS_Mode mode; uint8_t axis = 0;
	while(1)
	{

		if(OK_BUTTON_state)
		{
			OK_BUTTON_state=~OK_BUTTON_state;
			Display_Write_Ins(GO_TO_START_SECOND_LINE + 15);
			Display_Write_Data_Array("*", 1);
			delay_milis(500);
			mode = i;
			i=0; select = 1;
			break;
		}
		if(LEFT_BUTTON_state)
		{
			(i > 0 && i < 3)? (i--) : (i=2);
			LEFT_BUTTON_state=~LEFT_BUTTON_state;
			select = 1;
		}

		if(RIGHT_BUTTON_state)
		{
			(i >= 0 && i < 2)? (i++) : (i=0);
			RIGHT_BUTTON_state=~RIGHT_BUTTON_state;
			select = 1;
		}
		if(select)
		{
			Display_Write_Ins(GO_TO_START_SECOND_LINE);
			Display_clear_field(DISPLAY_MAX_SECOND_LINE);
			uint8_t offset = (DISPLAY_MAX_SECOND_LINE - strlen(MEMS_modes_list[i]))/2;
			Display_Write_Ins(GO_TO_START_SECOND_LINE + offset);
			Display_Write_Data_Array(MEMS_modes_list[i], strlen(MEMS_modes_list[i]));
			select = 0;
		}

	}


	Display_clear();
	Display_Write_Ins(GO_TO_START_FIRST_LINE);
	Display_Write_Data_Array("<----[AXIS]---->", 16);



	while(1)
	{

		if(OK_BUTTON_state)
		{
			OK_BUTTON_state=~OK_BUTTON_state;
			Display_Write_Ins(GO_TO_START_SECOND_LINE + 15);
			Display_Write_Data_Array("*", 1);
			delay_milis(500);
			axis = i;
			i=0;
			break;
		}
		if(LEFT_BUTTON_state)
		{
			(i > 0 && i < 4)? (i--) : (i=3);
			LEFT_BUTTON_state=~LEFT_BUTTON_state;
			select = 1;
		}

		if(RIGHT_BUTTON_state)
		{
			(i >= 0 && i < 3)? (i++) : (i=0);
			RIGHT_BUTTON_state=~RIGHT_BUTTON_state;
			select = 1;
		}
		if(select)
		{
			Display_Write_Ins(GO_TO_START_SECOND_LINE);
			Display_clear_field(DISPLAY_MAX_SECOND_LINE);
			uint8_t offset = (DISPLAY_MAX_SECOND_LINE - strlen(MEMS_axises_list[i]))/2;
			Display_Write_Ins(GO_TO_START_SECOND_LINE + offset);
			Display_Write_Data_Array(MEMS_axises_list[i], strlen(MEMS_axises_list[i]));
			select = 0;
		}

	}


	Display_clear();
	Display_Write_Ins(GO_TO_START_FIRST_LINE);
	Display_Write_Data_Array("M->", 3);
	Display_Write_Data_Array(MEMS_modes_list[mode], strlen(MEMS_modes_list[mode]));

	Display_Write_Ins(GO_TO_START_SECOND_LINE);
	Display_Write_Data_Array("XYZ->", 5);
	Display_Write_Data_Array(MEMS_axises_list[axis], strlen(MEMS_axises_list[axis]));
	delay_milis(500);

	Display_clear();


	if(axis == Axis_All)
	{
		Display_Write_Ins(GO_TO_START_FIRST_LINE);
		Display_Write_Data_Array("x=", 2);

		Display_Write_Ins(GO_TO_START_FIRST_LINE+8);
		Display_Write_Data_Array("y=", 2);
		Display_Write_Ins(GO_TO_START_SECOND_LINE);
		Display_Write_Data_Array("z=", 2);

		Display_Write_Ins(GO_TO_START_SECOND_LINE+8);
		Display_Write_Data_Array("MODE=", 5);
		Display_Write_Data_Array(MEMS_modes_list[mode], 3);
	}
	if(axis == Axis_X)
	{
		Display_Write_Ins(GO_TO_START_FIRST_LINE);
		Display_Write_Data_Array(MEMS_modes_list[mode], strlen(MEMS_modes_list[mode]));
		Display_Write_Ins(GO_TO_START_SECOND_LINE);
		Display_Write_Data_Array("X=", 2);
	}
	if(axis == Axis_Y)
	{
		Display_Write_Ins(GO_TO_START_FIRST_LINE);
		Display_Write_Data_Array(MEMS_modes_list[mode], strlen(MEMS_modes_list[mode]));
		Display_Write_Ins(GO_TO_START_SECOND_LINE);
		Display_Write_Data_Array("Y=", 2);
	}
	if(axis == Axis_Z)
	{
		Display_Write_Ins(GO_TO_START_FIRST_LINE);
		Display_Write_Data_Array(MEMS_modes_list[mode], strlen(MEMS_modes_list[mode]));
		Display_Write_Ins(GO_TO_START_SECOND_LINE);
		Display_Write_Data_Array("Z=", 2);
	}
	setup_MEMS();
	MEMS_data XYZ;
	char tmp[32];
	uint8_t len = 0;
	while(1)
	{
		mode == ACCELEROMETER ? MEMS_read_ACCELEROMETR(&XYZ) : __NOP;
		mode == ACCELEROMETER_AND_GYROSCOPE ? MEMS_read_GYROSCOPE(&XYZ) : __NOP;
		mode == MAGNETOMETR ? MEMS_read_MAGNETOMETR(&XYZ) : __NOP;
		if (axis == Axis_All)
		{
			sprintf(tmp, "%.1f", XYZ.X);
			len = strlen(tmp);
			Display_Write_Ins(GO_TO_START_FIRST_LINE + 2);
			Display_clear_field(6);
			Display_Write_Ins(GO_TO_START_FIRST_LINE + 2);
			Display_Write_Data_Array(tmp, len);

			sprintf(tmp, "%.1f", XYZ.Y);
			len = strlen(tmp);
			Display_Write_Ins(GO_TO_START_FIRST_LINE + 8 + 2);
			Display_clear_field(6);
			Display_Write_Ins(GO_TO_START_FIRST_LINE + 8 + 2);
			Display_Write_Data_Array(tmp, len);

			sprintf(tmp, "%.1f", XYZ.Z);
			len = strlen(tmp);
			Display_Write_Ins(GO_TO_START_SECOND_LINE + 2);
			Display_clear_field(6);
			Display_Write_Ins(GO_TO_START_SECOND_LINE + 2);
			Display_Write_Data_Array(tmp, len);

			sprintf(tmp, "ALL");
			len = strlen(tmp);
			Display_Write_Ins(GO_TO_START_SECOND_LINE + 8 + 5);
			Display_clear_field(6);
			Display_Write_Ins(GO_TO_START_SECOND_LINE + 8 + 5);
			Display_Write_Data_Array(tmp, len);
		}
		if (axis == Axis_X)
		{
			Display_Write_Ins(GO_TO_START_FIRST_LINE);
			Display_Write_Data_Array(MEMS_modes_list[mode],strlen(MEMS_modes_list[mode]));
			sprintf(tmp, "%.1f", XYZ.X);
			len = strlen(tmp);
			Display_Write_Ins(GO_TO_START_SECOND_LINE+2);
			Display_clear_field(14);
			Display_Write_Ins(GO_TO_START_SECOND_LINE+2);
			Display_Write_Data_Array(tmp, len);
		}
		if (axis == Axis_Y)
		{
			Display_Write_Ins(GO_TO_START_FIRST_LINE);
			Display_Write_Data_Array(MEMS_modes_list[mode], strlen(MEMS_modes_list[mode]));
			sprintf(tmp, "%.1f", XYZ.Y);
			len = strlen(tmp);
			Display_Write_Ins(GO_TO_START_SECOND_LINE+2);
			Display_clear_field(14);
			Display_Write_Ins(GO_TO_START_SECOND_LINE+2);
			Display_Write_Data_Array(tmp, len);
		}
		if (axis == Axis_Z)
		{
			Display_Write_Ins(GO_TO_START_FIRST_LINE);
			Display_Write_Data_Array(MEMS_modes_list[mode],strlen(MEMS_modes_list[mode]));
			sprintf(tmp, "%.1f", XYZ.Z);
			len = strlen(tmp);
			Display_Write_Ins(GO_TO_START_SECOND_LINE+2);
			Display_clear_field(14);
			Display_Write_Ins(GO_TO_START_SECOND_LINE+2);
			Display_Write_Data_Array(tmp, len);
		}


	}


}
