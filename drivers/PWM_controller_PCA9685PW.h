#ifndef DRIVERS_PWM_CONTROLLER_PCA9685PW_H_
#define DRIVERS_PWM_CONTROLLER_PCA9685PW_H_

// https://cdn-shop.adafruit.com/datasheets/PCA9685.pdf

#include "i2c.h"
#include "USART.h"

#define PCA_I2C_PERIPH				I2C1
#define PCA_BIT_DEPTH				(12)
#define PCA_SWRST					((uint8_t)(0x6))
#define PCA_MAX_VALUE				(1<<PCA_BIT_DEPTH) //4096
#define PCA_SLAVE_ADDRESS			((uint8_t)(0x40<<1)) //must be shifted left per 1
#define PCA_OSCCLK					(25000000) //25MHz (PCA9685 datasheet p.5 https://cdn-shop.adafruit.com/datasheets/PCA9685.pdf)
#define PCA_MAX_FREQUENCY			(1526)
#define PCA_MIN_FREQUENCY			(24)

#define PCA_REFRESH_RATE(frequency) 					((PCA_OSCCLK/(PCA_MAX_VALUE*(frequency)))-1) //(PCA9685 datasheet p.5 https://cdn-shop.adafruit.com/datasheets/PCA9685.pdf)
#define PCA_CALCULATE_SCALE_INTERVAL(frequency) 		(((double)((double)1/(double)frequency))/((double)PCA_MAX_VALUE))

#define PCA_MODE					((uint8_t)0x0)

#define PCA_MODE1_RESTART_ENABLE	((uint8_t)0x80)
#define PCA_MODE1_EXTCLK_ENABLE		((uint8_t)0x40)
#define PCA_MODE1_AI_ENABLE			((uint8_t)0x20)
#define PCA_MODE1_SLEEP_LOW_PWR		((uint8_t)0x10)
#define PCA_MODE1_SUB1_ENABLE		((uint8_t)0x08)
#define PCA_MODE1_SUB2_ENABLE		((uint8_t)0x04)
#define PCA_MODE1_SUB3_ENABLE		((uint8_t)0x02)
#define PCA_MODE1_ALLCALL_ENABLE	((uint8_t)0x01)

#define PCA_MODE2_INVERT_ENABLE					((uint8_t)0x10)
#define PCA_MODE2_OCH_ON_ACK					((uint8_t)0x08)
#define PCA_MODE2_OUTDRV_TOT_POLE				((uint8_t)0x04)
#define PCA_MODE2_OUTNE_TO_HIGH_IMPEDANCE1		((uint8_t)0x03)
#define PCA_MODE2_OUTNE_TO_HIGH_IMPEDANCE2		((uint8_t)0x02)
#define PCA_MODE2_OUTNE_TO_ONE					((uint8_t)0x01)


typedef enum PCA9685_reg_map
{
	PCA9685__MODE1 = 0,				//!< register MODE1
	PCA9685__MODE2,					//!< register MODE2
	PCA9685__SUBADR1,				//!< register SUBADR1
	PCA9685__SUBADR2,				//!< register SUBADR2
	PCA9685__SUBADR3,				//!< register SUBADR3
	PCA9685__ALLCALLADR,			//!< register ALLCALLADR
	PCA9685__LED0_ON_L,				//!< register LED 0 ON Low
	PCA9685__LED0_ON_H,				//!< register LED 0 ON High
	PCA9685__LED0_OFF_L,			//!< register LED 0 OFF Low
	PCA9685__LED0_OFF_H,			//!< register LED 0 OFF High
	PCA9685__LED1_ON_L,				//!< register LED 1 ON Low
	PCA9685__LED1_ON_H,				//!< register LED 1 ON High
	PCA9685__LED1_OFF_L,			//!< register LED 1 OFF Low
	PCA9685__LED1_OFF_H,			//!< register LED 1 OFF High
	PCA9685__LED2_ON_L,				//!< register LED 2 ON Low
	PCA9685__LED2_ON_H,				//!< register LED 2 ON High
	PCA9685__LED2_OFF_L,			//!< register LED 2 OFF Low
	PCA9685__LED2_OFF_H,			//!< register LED 2 OFF High
	PCA9685__LED3_ON_L,				//!< register LED 3 ON Low
	PCA9685__LED3_ON_H,				//!< register LED 3 ON High
	PCA9685__LED3_OFF_L,			//!< register LED 3 OFF Low
	PCA9685__LED3_OFF_H,			//!< register LED 3 OFF High
	PCA9685__LED4_ON_L,				//!< register LED 4 ON Low
	PCA9685__LED4_ON_H,				//!< register LED 4 ON High
	PCA9685__LED4_OFF_L,			//!< register LED 4 OFF Low
	PCA9685__LED4_OFF_H,			//!< register LED 4 OFF High
	PCA9685__LED5_ON_L,				//!< register LED 5 ON Low
	PCA9685__LED5_ON_H,				//!< register LED 5 ON High
	PCA9685__LED5_OFF_L,			//!< register LED 5 OFF Low
	PCA9685__LED5_OFF_H,			//!< register LED 5 OFF High
	PCA9685__LED6_ON_L,				//!< register LED 6 ON Low
	PCA9685__LED6_ON_H,				//!< register LED 6 ON High
	PCA9685__LED6_OFF_L,			//!< register LED 6 OFF Low
	PCA9685__LED6_OFF_H,			//!< register LED 6 OFF High
	PCA9685__LED7_ON_L,				//!< register LED 7 ON Low
	PCA9685__LED7_ON_H,				//!< register LED 7 ON High
	PCA9685__LED7_OFF_L,			//!< register LED 7 OFF Low
	PCA9685__LED7_OFF_H,			//!< register LED 7 OFF High
	PCA9685__LED8_ON_L,				//!< register LED 8 ON Low
	PCA9685__LED8_ON_H,				//!< register LED 8 ON High
	PCA9685__LED8_OFF_L,			//!< register LED 8 OFF Low
	PCA9685__LED8_OFF_H,			//!< register LED 8 OFF High
	PCA9685__LED9_ON_L,				//!< register LED 9 ON Low
	PCA9685__LED9_ON_H,				//!< register LED 9 ON High
	PCA9685__LED9_OFF_L,			//!< register LED 9 OFF Low
	PCA9685__LED9_OFF_H,			//!< register LED 9 OFF High
	PCA9685__LED10_ON_L,			//!< register LED 10 ON Low
	PCA9685__LED10_ON_H,			//!< register LED 10 ON High
	PCA9685__LED10_OFF_L,			//!< register LED 10 OFF Low
	PCA9685__LED10_OFF_H,			//!< register LED 10 OFF High
	PCA9685__LED11_ON_L,			//!< register LED 11 ON Low
	PCA9685__LED11_ON_H,			//!< register LED 11 ON High
	PCA9685__LED11_OFF_L,			//!< register LED 11 OFF Low
	PCA9685__LED11_OFF_H,			//!< register LED 11 OFF High
	PCA9685__LED12_ON_L,			//!< register LED 12 ON Low
	PCA9685__LED12_ON_H,			//!< register LED 12 ON High
	PCA9685__LED12_OFF_L,			//!< register LED 12 OFF Low
	PCA9685__LED12_OFF_H,			//!< register LED 12 OFF High
	PCA9685__LED13_ON_L,			//!< register LED 13 ON Low
	PCA9685__LED13_ON_H,			//!< register LED 13 ON High
	PCA9685__LED13_OFF_L,			//!< register LED 13 OFF Low
	PCA9685__LED13_OFF_H,			//!< register LED 13 OFF High
	PCA9685__LED14_ON_L,			//!< register LED 14 ON Low
	PCA9685__LED14_ON_H,			//!< register LED 14 ON High
	PCA9685__LED14_OFF_L,			//!< register LED 14 OFF Low
	PCA9685__LED14_OFF_H,			//!< register LED 14 OFF High
	PCA9685__LED15_ON_L,			//!< register LED 15 ON Low
	PCA9685__LED15_ON_H,			//!< register LED 15 ON High
	PCA9685__LED15_OFF_L,			//!< register LED 15 OFF Low
	PCA9685__LED15_OFF_H,			//!< register LED 15 OFF High
	PCA9685__ALL_LED_ON_L = 0xFA,	//!< register ALL LED ON Low
	PCA9685__ALL_LED_ON_H,			//!< register ALL LED ON High
	PCA9685__ALL_LED_OFF_L,			//!< register ALL LED OFF Low
	PCA9685__ALL_LED_OFF_H,			//!< register ALL LED OFF High
	PCA9685__PRE_SCALE,				//!< register PRE_SCALE
	PCA9685__TestMode				//!< register TestMode
} PCA9685_reg;

#define PCA9685_CHANNEL0 	((uint8_t)PCA9685__LED0_ON_L)
#define PCA9685_CHANNEL1 	((uint8_t)PCA9685__LED1_ON_L)
#define PCA9685_CHANNEL2 	((uint8_t)PCA9685__LED2_ON_L)
#define PCA9685_CHANNEL3 	((uint8_t)PCA9685__LED3_ON_L)
#define PCA9685_CHANNEL4 	((uint8_t)PCA9685__LED4_ON_L)
#define PCA9685_CHANNEL5 	((uint8_t)PCA9685__LED5_ON_L)
#define PCA9685_CHANNEL6 	((uint8_t)PCA9685__LED6_ON_L)
#define PCA9685_CHANNEL7 	((uint8_t)PCA9685__LED7_ON_L)
#define PCA9685_CHANNEL8 	((uint8_t)PCA9685__LED8_ON_L)
#define PCA9685_CHANNEL9 	((uint8_t)PCA9685__LED9_ON_L)
#define PCA9685_CHANNEL10	((uint8_t)PCA9685__LED10_ON_L)
#define PCA9685_CHANNEL11	((uint8_t)PCA9685__LED11_ON_L)
#define PCA9685_CHANNEL12	((uint8_t)PCA9685__LED12_ON_L)
#define PCA9685_CHANNEL13 	((uint8_t)PCA9685__LED13_ON_L)
#define PCA9685_CHANNEL14 	((uint8_t)PCA9685__LED14_ON_L)
#define PCA9685_CHANNEL15 	((uint8_t)PCA9685__LED15_ON_L)

#define PCA9685_CHANNEL_ON_LOW_OFFSET		((uint8_t)0)
#define PCA9685_CHANNEL_ON_HIGH_OFFSET		((uint8_t)1)
#define PCA9685_CHANNEL_OFF_LOW_OFFSET		((uint8_t)2)
#define PCA9685_CHANNEL_OFF_HIGH_OFFSET		((uint8_t)3)


typedef struct PWM_configuration_parameters
{
	double pwm_frequency;
	double duty_cycle;
	double delay_time;

} PWM_cfg;

typedef struct PCA9685_DataStruct
{
	uint8_t LEDx_ON_Low;
	uint8_t LEDx_ON_High;
	uint8_t LEDx_OFF_Low;
	uint8_t LEDx_OFF_High;
	uint8_t PRE_SCALE;

} PCA9685_Data;

typedef struct servo_parameters
{
	double pwm_frequency;
	double impuls_duration_for_MIN_angle; //1.0ms
	double impuls_duration_for_MAX_angle; //2.0ms
	uint16_t min_angle; //0
	uint16_t max_angle; //180

} Servo;

void PCA_servo_example2(void);

void PCA_servo_example(void);

void PCA_Init(PCA9685_Data data);

void PCA_reset(void);

void PCA_sleep(void);

void PCA_awake(void);

void PCA_set_prescale(uint8_t pre_scale);

void PCA_set_state(FunctionalState state);

void PCA_fill_data_for_servo(PCA9685_Data *data, Servo servo, double angle);

//void PWM_FILL_DATA_PWM(PCA9685_Data *data, PWM_cfg pwm_cfg);

void PCA_set_data_for_channel(uint8_t channel, PCA9685_Data data);
void PCA_get_data_for_channel(uint8_t channel, PCA9685_Data *data);

//void PWM_set_reg(uint8_t reg, uint8_t data);
//void PWM_get_reg(uint8_t reg, uint8_t *data, uint16_t count);


#endif /* DRIVERS_PWM_CONTROLLER_PCA9685PW_H_ */
