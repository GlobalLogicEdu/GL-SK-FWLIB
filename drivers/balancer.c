#include "balancer.h"
#include "DISPLAY_WH1602B_4Bit.h"
#include "PWM_controller_PCA9685PW.h"

#define MIDLE_POSITION (90)

void balancer_init(void)
{
	setup_Display();
	setup_MEMS();

	PCA9685_Data pca_data;
	Servo servo;
	servo.pwm_frequency = 50; // f=50Hz T=20ms
	servo.min_angle = 0;
	servo.max_angle = 180;
	servo.impuls_duration_for_MIN_angle = 0.0005;	// 0.5ms	2.5% duty cycle
	servo.impuls_duration_for_MAX_angle = 0.0025;	// 2.5ms	10% duty cycle
	PCA_fill_data_for_servo(&pca_data, servo, MIDLE_POSITION);
	PCA_Init(pca_data);
	PCA_set_data_for_channel(PCA9685_CHANNEL0, pca_data);

	MEMS_Init();
	MEMS_data XYZ;
	char tmp[32]; uint8_t len = 0;
	while(1)
	{
//		USART_printf(USART3, "START\n\r");
		MEMS_read_ACCELEROMETR(&XYZ);
		PCA_fill_data_for_servo(&pca_data, servo, MIDLE_POSITION + XYZ.X);
		PCA_set_data_for_channel(PCA9685_CHANNEL0, pca_data);
		Display_Write_Ins(GO_TO_START_FIRST_LINE);
		sprintf(tmp, "%u", (uint16_t)(MIDLE_POSITION + XYZ.X));
		len = strlen(tmp);
		Display_clear();
		Display_Write_Data_Array(tmp, len);
//		USART_printf(USART3, "angle = [%d]\n\r", MIDLE_POSITION + XYZ.X);


	}


}
