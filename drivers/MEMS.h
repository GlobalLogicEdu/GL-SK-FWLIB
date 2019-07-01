
#ifndef DRIVERS_MEMS_H_
#define DRIVERS_MEMS_H_

// https://www.st.com/resource/en/datasheet/DM00103319.pdf

#include "i2c.h"
#include "USART.h"


#define MEMS_I2C_PERIPH						I2C1
#define MEMS_ACCEL_SLAVE_ADDRESS			((uint8_t)(0x6B<<1)) //must be shifted left per 1
#define MEMS_MAGNETIC_SLAVE_ADDRESS			((uint8_t)(0x1E<<1)) //must be shifted left per 1

#define MEMS_INT_M_PORT						GPIOB
#define MEMS_INT_M							GPIO_Pin_8

#define MEMS_INT_AG_PORT					GPIOE
#define MEMS_INT1_AG						GPIO_Pin_4
#define MEMS_INT2_AG						GPIO_Pin_2


/*  ACCELEROMETER AND GYROSCOPE REGISTER ADDRESS MAP */
#define ACT_THS 			((uint8_t)(0x04))
#define ACT_DUR 			((uint8_t)(0x05))
#define INT_GEN_CFG_XL 		((uint8_t)(0x06))
#define INT_GEN_THS_X_XL 	((uint8_t)(0x07))
#define INT_GEN_THS_Y_XL 	((uint8_t)(0x08))
#define INT_GEN_THS_Z_XL 	((uint8_t)(0x09))
#define INT_GEN_DUR_XL 		((uint8_t)(0x0A))
#define REFERENCE_G 		((uint8_t)(0x0B))
#define INT1_CTRL 			((uint8_t)(0x0C))
#define INT2_CTRL			((uint8_t)(0x0D))
#define WHO_AM_I_ACCEL		((uint8_t)(0x0F))
#define CTRL_REG1_G 		((uint8_t)(0x10))
#define CTRL_REG2_G 		((uint8_t)(0x11))
#define CTRL_REG3_G 		((uint8_t)(0x12))
#define ORIENT_CFG_G 		((uint8_t)(0x13))
#define INT_GEN_SRC_G 		((uint8_t)(0x14))
#define OUT_TEMP_L 			((uint8_t)(0x15))
#define OUT_TEMP_H 			((uint8_t)(0x16))
#define STATUS_REG_ACCEL 	((uint8_t)(0x17))
#define OUT_X_L_G 			((uint8_t)(0x18))
#define OUT_X_H_G 			((uint8_t)(0x19))
#define OUT_Y_L_G 			((uint8_t)(0x1A))
#define OUT_Y_H_G 			((uint8_t)(0x1B))
#define OUT_Z_L_G 			((uint8_t)(0x1C))
#define OUT_Z_H_G 			((uint8_t)(0x1D))
#define CTRL_REG4 			((uint8_t)(0x1E))
#define CTRL_REG5_XL 		((uint8_t)(0x1F))
#define CTRL_REG6_XL 		((uint8_t)(0x20))
#define CTRL_REG7_XL 		((uint8_t)(0x21))
#define CTRL_REG8 			((uint8_t)(0x22))
#define CTRL_REG9			((uint8_t)(0x23))
#define CTRL_REG10 			((uint8_t)(0x24))
#define INT_GEN_SRC_XL 		((uint8_t)(0x26))
#define STATUS_REG_GYRO 	((uint8_t)(0x27))
#define OUT_X_L_XL 			((uint8_t)(0x28))
#define OUT_X_H_XL 			((uint8_t)(0x29))
#define OUT_Y_L_XL 			((uint8_t)(0x2A))
#define OUT_Y_H_XL 			((uint8_t)(0x2B))
#define OUT_Z_L_XL 			((uint8_t)(0x2C))
#define OUT_Z_H_XL 			((uint8_t)(0x2D))
#define FIFO_CTRL 			((uint8_t)(0x2E))
#define FIFO_SRC 			((uint8_t)(0x2F))
#define INT_GEN_CFG_G 		((uint8_t)(0x30))
#define INT_GEN_THS_XH_G 	((uint8_t)(0x31))
#define INT_GEN_THS_XL_G 	((uint8_t)(0x32))
#define INT_GEN_THS_YH_G 	((uint8_t)(0x33))
#define INT_GEN_THS_YL_G 	((uint8_t)(0x34))
#define INT_GEN_THS_ZH_G 	((uint8_t)(0x35))
#define INT_GEN_THS_ZL_G 	((uint8_t)(0x36))
#define INT_GEN_DUR_G 		((uint8_t)(0x37))
/*-----------------------------------------------------*/

/*  MAGNETIC SENSOR REGISTER ADDRESS MAP */
#define OFFSET_X_REG_L_M 	((uint8_t)(0x05))
#define OFFSET_X_REG_H_M 	((uint8_t)(0x06))
#define OFFSET_Y_REG_L_M 	((uint8_t)(0x07))
#define OFFSET_Y_REG_H_M 	((uint8_t)(0x08))
#define OFFSET_Z_REG_L_M 	((uint8_t)(0x09))
#define OFFSET_Z_REG_H_M 	((uint8_t)(0x0A))
#define WHO_AM_I_M 			((uint8_t)(0x0F))
#define CTRL_REG1_M 		((uint8_t)(0x20))
#define CTRL_REG2_M 		((uint8_t)(0x21))
#define CTRL_REG3_M 		((uint8_t)(0x22))
#define CTRL_REG4_M 		((uint8_t)(0x23))
#define CTRL_REG5_M 		((uint8_t)(0x24))
#define STATUS_REG_M 		((uint8_t)(0x27))
#define OUT_X_L_M 			((uint8_t)(0x28))
#define OUT_X_H_M 			((uint8_t)(0x29))
#define OUT_Y_L_M 			((uint8_t)(0x2A))
#define OUT_Y_H_M 			((uint8_t)(0x2B))
#define OUT_Z_L_M 			((uint8_t)(0x2C))
#define OUT_Z_H_M 			((uint8_t)(0x2D))
#define INT_CFG_M 			((uint8_t)(0x30))
#define INT_SRC_M 			((uint8_t)(0x31))
#define INT_THS_L_M 		((uint8_t)(0x32))
#define INT_THS_H_M 		((uint8_t)(0x33))
/*-----------------------------------------------------*/


/* Table 68 in datasheet----------------------------------*/
#define ODR_MASK_POWER_DOWN		((uint8_t)(0x00))
#define ODR_MASK_10_HZ			((uint8_t)(0x20))
#define ODR_MASK_50_HZ			((uint8_t)(0x40))
#define ODR_MASK_119_HZ			((uint8_t)(0x60))
#define ODR_MASK_238_HZ			((uint8_t)(0x80))
#define ODR_MASK_476_HZ			((uint8_t)(0xA0))
#define ODR_MASK_952_HZ			((uint8_t)(0xC0))
/*---------------------------------------------------------*/

/* CTRL_REG6_XL description --------------------------------*/
#define ACCEL_SCALE_SELECTION_MASK_2G		((uint8_t)(0x00))
#define ACCEL_SCALE_SELECTION_MASK_16G		((uint8_t)(0x08))
#define ACCEL_SCALE_SELECTION_MASK_4G		((uint8_t)(0x10))
#define ACCEL_SCALE_SELECTION_MASK_8G		((uint8_t)(0x18))

#define BANDWIDTH_SELECTION_MASK_BY_ODR	((uint8_t)(0x00))
#define BANDWIDTH_SELECTION_MASK_BY_REG	((uint8_t)(0x04)) // bandwidth selected according to BW_XL [2:1] selection) see below

#define ACCEL_BANDWIDTH_MASK_408_HZ   ((uint8_t)(0x00))
#define ACCEL_BANDWIDTH_MASK_211_HZ   ((uint8_t)(0x01))
#define ACCEL_BANDWIDTH_MASK_105_HZ   ((uint8_t)(0x02))
#define ACCEL_BANDWIDTH_MASK_50_HZ	  ((uint8_t)(0x03))
/*----------------------------------------------------------*/

/* CTRL_REG1_G  description --------------------------------*/
#define GYRO_SCALE_SELECTION_MASK_245_DPS		((uint8_t)(0x00))
#define GYRO_SCALE_SELECTION_MASK_500_DPS		((uint8_t)(0x08))
#define GYRO_SCALE_SELECTION_MASK_2000_DPS		((uint8_t)(0x18))

// Gyroscope bandwidth depend from ODR see Table 47
#define GYRO_BANDWIDTH_MASK_0   ((uint8_t)(0x00))
#define GYRO_BANDWIDTH_MASK_1   ((uint8_t)(0x01))
#define GYRO_BANDWIDTH_MASK_2   ((uint8_t)(0x02))
#define GYRO_BANDWIDTH_MASK_3	((uint8_t)(0x03))
/*---------------------------------------------------------*/


/*  CTRL_REG3_M description -------------------------------------------------------*/
#define MAGNETIC_I2C_MODE_MASK				((uint8_t)(0x00)) //always MUST be in zero
#define MAGNETIC_LOW_POWER_MASK				((uint8_t)(0x00))
#define MAGNETIC_SIM_MASK					((uint8_t)(0x00))
#define MAGNETIC_OPERATING_MODE_CC_MASK 	((uint8_t)(0x00)) //Table 117
#define MAGNETIC_OPERATING_MODE_SC_MASK 	((uint8_t)(0x01)) //Table 117
#define MAGNETIC_OPERATING_MODE_PD1_MASK	((uint8_t)(0x00)) //Table 117
#define MAGNETIC_OPERATING_MODE_PD2_MASK	((uint8_t)(0x00)) //Table 117
/*----------------------------------------------------------------------------------*/


/*  CTRL_REG5_XL description -------------------------------------------------------*/
#define ACCEL_DECIMATION_OF_ACCELERATION_MASK_NO						((uint8_t)(0x00))
#define ACCEL_DECIMATION_OF_ACCELERATION_MASK_UPDATE_EVERY_2_SAMPLES	((uint8_t)(0x40))
#define ACCEL_DECIMATION_OF_ACCELERATION_MASK_UPDATE_EVERY_4_SAMPLES	((uint8_t)(0x80))
#define ACCEL_DECIMATION_OF_ACCELERATION_MASK_UPDATE_EVERY_8_SAMPLES	((uint8_t)(0xC0))

#define ACCEL_Z_ENABLE		((uint8_t)(0x20))
#define ACCEL_Y_ENABLE		((uint8_t)(0x10))
#define ACCEL_X_ENABLE		((uint8_t)(0x08))
/*----------------------------------------------------------------------------------*/

/*  CTRL_REG5_XL description ---------------------------------------------------------------*/
#define ACCEL_DECIMATION_OF_ACCELERATION_MASK_NO						((uint8_t)(0x00))
#define ACCEL_DECIMATION_OF_ACCELERATION_MASK_UPDATE_EVERY_2_SAMPLES	((uint8_t)(0x40))
#define ACCEL_DECIMATION_OF_ACCELERATION_MASK_UPDATE_EVERY_4_SAMPLES	((uint8_t)(0x80))
#define ACCEL_DECIMATION_OF_ACCELERATION_MASK_UPDATE_EVERY_8_SAMPLES	((uint8_t)(0xC0))
/*----------------------------------------------------------------------------------------*/


#define ACCEL_MASK_Z_ENABLE		((uint8_t)(0x20))
#define ACCEL_MASK_Y_ENABLE		((uint8_t)(0x10))
#define ACCEL_MASK_X_ENABLE		((uint8_t)(0x08))

/*  CTRL_REG4 description ---------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------*/



typedef enum MEMS_Mode_Enum
{
	ACCELEROMETER,
	ACCELEROMETER_AND_GYROSCOPE,
	MAGNETOMETR,
	POWER_DOWN,

} MEMS_Mode;

typedef enum MEMS_Axis_Enum
{
	Axis_X,
	Axis_Y,
	Axis_Z,
	Axis_All,
} MEMS_Axis;


typedef struct MEMS_dataStruct
{
	float  X;
	float  Y;
	float  Z;
} MEMS_data;

void setup_MEMS(void);

void MEMS_set_mode(MEMS_Mode mode);

void MEMS_Axis_state_ACCEL(void);

void MEMS_Axis_state_GYRO(void);

void MEMS_Init(void);

void MEMS_read_GYROSCOPE(MEMS_data *data);

void MEMS_read_ACCELEROMETR(MEMS_data *data);

void MEMS_read_MAGNETOMETR(MEMS_data *data);

void MEMS_example(void);

void MEMS_example_with_menu(void);



#endif /* DRIVERS_MEMS_H_ */
