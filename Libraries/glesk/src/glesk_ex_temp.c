#include "glesk_ex_temp.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#define EX_TEMP_PIN			GPIO_Pin_1
#define EX_TEMP_PORT		GPIOB
#define EX_TEMP_PIN_PCLK	RCC_AHB1Periph_GPIOB
#define EX_TEMP_ADC			ADC1
#define EX_TEMP_ADC_CH		ADC_Channel_9
#define EX_TEMP_ADC_STIME	ADC_SampleTime_15Cycles
#define EX_TEMP_ADC_PCLK	RCC_APB2Periph_ADC1

#define EX_TEMP_MAX_TEMP	100
#define EX_TEMP_TEMP_RANGE	124
#define EX_TEMP_VOLT_RANGE	2.5

#define ADC_MAX_NUM			4096
#define ADC_REF_VOLT		3.3

int ex_temp_init(void)
{
	ADC_InitTypeDef adc_init;
	ADC_CommonInitTypeDef adc_common_init;
	GPIO_InitTypeDef gpio_init;

	RCC_AHB1PeriphClockCmd(EX_TEMP_PIN_PCLK, ENABLE);
	RCC_APB2PeriphClockCmd(EX_TEMP_ADC_PCLK, ENABLE);

	gpio_init.GPIO_Mode = GPIO_Mode_AN;
	gpio_init.GPIO_Pin = EX_TEMP_PIN;
	gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(EX_TEMP_PORT, &gpio_init);

	ADC_CommonStructInit(&adc_common_init);
	ADC_CommonInit(&adc_common_init);

	ADC_StructInit(&adc_init);
	ADC_Init(EX_TEMP_ADC, &adc_init);

	ADC_Cmd(EX_TEMP_ADC, ENABLE);

	return 0;
}

int ex_temp_read(float *temp)
{
	u16 adc_val;
	float voltage;
	float tmp;

	if (!temp) return -1;

	ADC_RegularChannelConfig(EX_TEMP_ADC, EX_TEMP_ADC_CH, 1, EX_TEMP_ADC_STIME);
	ADC_SoftwareStartConv(EX_TEMP_ADC);

	while (!ADC_GetFlagStatus(EX_TEMP_ADC, ADC_FLAG_EOC));
	adc_val = ADC_GetConversionValue(EX_TEMP_ADC);

	voltage = ADC_REF_VOLT / ADC_MAX_NUM * adc_val;
	// Can be up to -24 Celsius
	tmp = EX_TEMP_MAX_TEMP - (EX_TEMP_TEMP_RANGE / EX_TEMP_VOLT_RANGE * voltage);
	*temp = tmp;

	return 0;
}
