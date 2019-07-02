#include "PWM_controller_PCA9685PW.h"
#include "LEDs.h"
#include "DISPLAY_WH1602B_4Bit.h"

static char empty_field[] = "                                ";
static uint8_t default_mode1;

void PCA_Init(PCA9685_Data data)
{
	PCA_reset();
	PCA_sleep();
	PCA_set_prescale(data.PRE_SCALE);
	PCA_awake();
}

void PCA_reset(void)
{
	I2C_transmit_byte_to_reg(PCA_I2C_PERIPH, PCA_SLAVE_ADDRESS, PCA9685__MODE1, 0x0);
}

void PCA_sleep(void)
{
	uint8_t new_mode1 = 0;
	I2C_receive_byte_from_reg(PCA_I2C_PERIPH, PCA_SLAVE_ADDRESS, PCA9685__MODE1, &default_mode1);
	/**********TO SLEEP**********/
	new_mode1 = (default_mode1&(~PCA_MODE1_RESTART_ENABLE)) | PCA_MODE1_SLEEP_LOW_PWR;
	I2C_transmit_byte_to_reg(PCA_I2C_PERIPH, PCA_SLAVE_ADDRESS, PCA9685__MODE1, new_mode1);
	/***************************/
}

void PCA_awake(void)
{
	/**********AWAKE**********/
	I2C_transmit_byte_to_reg(PCA_I2C_PERIPH, PCA_SLAVE_ADDRESS, PCA9685__MODE1, default_mode1);
	I2C_transmit_byte_to_reg(PCA_I2C_PERIPH, PCA_SLAVE_ADDRESS, PCA9685__MODE1, default_mode1 | PCA_MODE1_RESTART_ENABLE  | PCA_MODE1_ALLCALL_ENABLE);
	/*************************/
}

void PCA_set_state(FunctionalState state)
{
	if (state == ENABLE)
	{
		GPIO_SetBits(PWM_CTRL_PORT, PWM_CTRL_ONOFF);
	}
	else
	{
		GPIO_ResetBits(PWM_CTRL_PORT, PWM_CTRL_ONOFF);
	}
}

void PCA_set_prescale(uint8_t pre_scale)
{
	I2C_transmit_byte_to_reg(PCA_I2C_PERIPH, PCA_SLAVE_ADDRESS, PCA9685__PRE_SCALE, pre_scale);
}

void PCA_fill_data_for_servo(PCA9685_Data *data, Servo servo, double angle)
{

	data->PRE_SCALE = PCA_REFRESH_RATE(servo.pwm_frequency);
	double tick_count_for_min_angle = servo.impuls_duration_for_MIN_angle/PCA_CALCULATE_SCALE_INTERVAL(servo.pwm_frequency);
	double tick_count_for_max_angle = servo.impuls_duration_for_MAX_angle/PCA_CALCULATE_SCALE_INTERVAL(servo.pwm_frequency);

	double servo_tick_range = tick_count_for_max_angle - tick_count_for_min_angle;

	double ticks_per_one_degree = servo_tick_range/servo.max_angle;

	double ticks_for_angle = ticks_per_one_degree*angle+tick_count_for_min_angle;

	double pwm_duration_for_angle = tick_count_for_min_angle + ticks_for_angle;

	data->LEDx_ON_Low = ((uint16_t)tick_count_for_min_angle & 0x00FF);
	data->LEDx_ON_High = ((uint16_t)tick_count_for_min_angle >> 8);

	data->LEDx_OFF_Low = ((uint16_t)pwm_duration_for_angle & 0x00FF);
	data->LEDx_OFF_High = ((uint16_t)pwm_duration_for_angle >> 8);
}
/**
  * @brief  Set data to PCA9685 .
  * @param  channel:
  *  PCA9685_CHANNEL0
  *	 PCA9685_CHANNEL1
  *	 PCA9685_CHANNEL2
  *	 PCA9685_CHANNEL3
  *	 PCA9685_CHANNEL4
  *	 PCA9685_CHANNEL5
  *	 PCA9685_CHANNEL6
  *	 PCA9685_CHANNEL7
  *	 PCA9685_CHANNEL8
  *	 PCA9685_CHANNEL9
  *	 PCA9685_CHANNEL10
  *	 PCA9685_CHANNEL11
  *	 PCA9685_CHANNEL12
  *	 PCA9685_CHANNEL13
  *	 PCA9685_CHANNEL14
  *	 PCA9685_CHANNEL15
  * @param  data: PCA9685_Data
*/
void PCA_set_data_for_channel(uint8_t channel, PCA9685_Data data)
{
	I2C_transmit_byte_to_reg(PCA_I2C_PERIPH, PCA_SLAVE_ADDRESS, channel + PCA9685_CHANNEL_ON_LOW_OFFSET, data.LEDx_ON_Low);
	I2C_transmit_byte_to_reg(PCA_I2C_PERIPH, PCA_SLAVE_ADDRESS, channel + PCA9685_CHANNEL_ON_HIGH_OFFSET, data.LEDx_ON_High);
	I2C_transmit_byte_to_reg(PCA_I2C_PERIPH, PCA_SLAVE_ADDRESS, channel + PCA9685_CHANNEL_OFF_LOW_OFFSET, data.LEDx_OFF_Low);
	I2C_transmit_byte_to_reg(PCA_I2C_PERIPH, PCA_SLAVE_ADDRESS, channel + PCA9685_CHANNEL_OFF_HIGH_OFFSET, data.LEDx_OFF_High);
}

void PCA_get_data_for_channel(uint8_t channel, PCA9685_Data *data)
{
	I2C_receive_byte_from_reg(PCA_I2C_PERIPH, PCA_SLAVE_ADDRESS, PCA9685__PRE_SCALE, &data->PRE_SCALE);
	I2C_receive_byte_from_reg(PCA_I2C_PERIPH, PCA_SLAVE_ADDRESS, channel + PCA9685_CHANNEL_ON_LOW_OFFSET, &data->LEDx_ON_Low);
	I2C_receive_byte_from_reg(PCA_I2C_PERIPH, PCA_SLAVE_ADDRESS, channel + PCA9685_CHANNEL_ON_HIGH_OFFSET, &data->LEDx_ON_High);
	I2C_receive_byte_from_reg(PCA_I2C_PERIPH, PCA_SLAVE_ADDRESS, channel + PCA9685_CHANNEL_OFF_LOW_OFFSET, &data->LEDx_OFF_Low);
	I2C_receive_byte_from_reg(PCA_I2C_PERIPH, PCA_SLAVE_ADDRESS, channel + PCA9685_CHANNEL_OFF_HIGH_OFFSET, &data->LEDx_OFF_High);
}

void PCA_servo_example(void)
{
	setup_clock();
	setup_I2C(PCA_I2C_PERIPH);
	PCA9685_Data pca_data;
	Servo servo;
	servo.pwm_frequency = 50; // f=50Hz T=20ms
	servo.min_angle = 0;
	servo.max_angle = 180;
	servo.impuls_duration_for_MIN_angle = 0.0005;	// 0.5ms	2.5% duty cycle
	servo.impuls_duration_for_MAX_angle = 0.0025;	// 2.5ms	10% duty cycle
	PCA_fill_data_for_servo(&pca_data, servo, 0);
	PCA_Init(pca_data);
	uint32_t cycles = 100;

	while(cycles)
	{
		uint16_t angle = 0;
		while(angle <= servo.max_angle)
		{
			PCA_fill_data_for_servo(&pca_data, servo, angle++);
			PCA_set_data_for_channel(PCA9685_CHANNEL0, pca_data);
		}
		while(angle > servo.min_angle)
		{
			PCA_fill_data_for_servo(&pca_data, servo, angle--);
			PCA_set_data_for_channel(PCA9685_CHANNEL0, pca_data);
		}
	}

}

void PCA_servo_example2(void)
{
	setup_clock();
	setup_I2C(I2C1);

	Display_init_GPIO();
	Display_Init();

	char buff[31];
	char *header = "angle = ";
	uint8_t header_len = strlen(header);

	Display_clear();
	Display_Write_srt(header ,header_len, 0, 0);

	PCA9685_Data pca_data;
	Servo servo;
	servo.pwm_frequency = 50; // f=50Hz T=20ms
	servo.min_angle = 0;
	servo.max_angle = 180;
	servo.impuls_duration_for_MIN_angle = 0.0005;	// 0.5ms	2.5% duty cycle
	servo.impuls_duration_for_MAX_angle = 0.0025;	// 2.5ms	10% duty cycle
	PCA_fill_data_for_servo(&pca_data, servo, 0);
	PCA_Init(pca_data);
	uint32_t cycles = 100;

	while(cycles)
	{
		uint16_t angle = 0;
		while(angle < servo.max_angle)
		{
			Display_Write_Ins(GO_TO_START_FIRST_LINE + header_len);
			sprintf(buff, "%u%c", angle,0xEF);

			PCA_fill_data_for_servo(&pca_data, servo, angle+=10);
			PCA_set_data_for_channel(PCA9685_CHANNEL0, pca_data);

			Display_Write_Data_Array(buff ,strlen(buff));
			Display_Write_Data_Array(empty_field ,strlen(buff)); //clear field
			delay_milis(500);
		}
		while(angle > servo.min_angle)
		{
			Display_Write_Ins(GO_TO_START_FIRST_LINE + header_len);
			sprintf(buff, "%u%c", angle, 0xEF);

			PCA_fill_data_for_servo(&pca_data, servo, angle-=10);
			PCA_set_data_for_channel(PCA9685_CHANNEL0, pca_data);

			Display_Write_Data_Array(buff ,strlen(buff));
			Display_Write_Data_Array(empty_field ,strlen(buff)); //clear field
			delay_milis(500);

		}
	}

}

