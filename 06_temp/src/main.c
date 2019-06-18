#include <stdio.h>
#include "glesk_common.h"
#include "stm32f4xx.h"

void adc_setup(void)
{
	ADC_InitTypeDef adc_init;
	ADC_CommonInitTypeDef adc_common_init;
	GPIO_InitTypeDef gpio_init;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	gpio_init.GPIO_Mode = GPIO_Mode_AN;
	gpio_init.GPIO_Pin = GPIO_Pin_1;
	gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &gpio_init);

	ADC_CommonStructInit(&adc_common_init);
	ADC_CommonInit(&adc_common_init);

	ADC_StructInit(&adc_init);
	ADC_Init(ADC1, &adc_init);

	ADC_Cmd(ADC1, ENABLE);
}

uint16_t adc1_read(uint8_t adc_ch)
{
	ADC_RegularChannelConfig(ADC1, adc_ch, 1, ADC_SampleTime_15Cycles);
	ADC_SoftwareStartConv(ADC1);
	while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
	return ADC_GetConversionValue(ADC1);
}

int main(void)
{
	adc_setup();

	while (1) {
		uint16_t adc_val = adc1_read(ADC_Channel_9);
		float voltage = 2.5 / 4096 * adc_val;
		float temp = 100 - (124 / 2.5 * voltage);

		printf("ADC: %d, VOLT: %d.%d TEMP: %d.%d C\n\r",
				adc_val,
				(uint32_t)voltage,
				(uint32_t)((voltage - (float)((uint32_t)voltage)) * 100.0),
				(uint32_t)temp,
				(uint32_t)((temp - (float)((uint32_t)temp)) * 100.0));
		delay_ms(1000);
	}
}
