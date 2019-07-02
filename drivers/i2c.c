#include "i2c.h"
#include "LEDs.h"
#include "USART.h"

static void I2C_TransmitData(I2C_TypeDef* I2Cx, uint8_t Data)
{
	while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_TXE) == RESET){}
	I2C_SendData(I2Cx, Data);
}

void setup_I2C(I2C_TypeDef* I2Cx)
{
//	I2C_Cmd(I2Cx, DISABLE);
	setup_clock_for_I2C(I2Cx, ENABLE);
	setup_pinout_for_I2C(I2Cx);
	I2C_InitTypeDef i2c_InitStructure;
	i2c_InitStructure.I2C_Mode = I2C_Mode_I2C;
	i2c_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	i2c_InitStructure.I2C_ClockSpeed = 100000; // must be less then  400000
	i2c_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	i2c_InitStructure.I2C_Ack = I2C_Ack_Enable;
	i2c_InitStructure.I2C_OwnAddress1 = 0x0f;

	I2C_AnalogFilterCmd(I2Cx, ENABLE);
	I2C_DeInit(I2Cx);
	I2C_Init(I2Cx, &i2c_InitStructure);
	I2C_Cmd(I2Cx, ENABLE);

}

void I2C_transmit_byte(I2C_TypeDef* I2Cx, uint8_t address, uint8_t data)
{
	I2C_GenerateSTART(I2Cx, ENABLE);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)){}

	I2C_Send7bitAddress(I2Cx, address, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)){}

	I2C_TransmitData(I2Cx, data);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)){}

	I2C_GenerateSTOP(I2Cx,ENABLE);
	while (I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF));

}

void I2C_transmit_byte_to_reg(I2C_TypeDef* I2Cx, uint8_t address, uint8_t reg, uint8_t data)
{

	I2C_GenerateSTART(I2Cx, ENABLE);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)){}

	I2C_Send7bitAddress(I2Cx, address, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)){}

	I2C_TransmitData(I2Cx, reg);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)){}

	I2C_TransmitData(I2Cx, data);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)){}

	I2C_GenerateSTOP(I2Cx,ENABLE);
	while (I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF));
}

void I2C_receive_byte(I2C_TypeDef* I2Cx,uint8_t address, uint8_t *data)
{
	I2C_AcknowledgeConfig(I2C1, ENABLE);
	I2C_GenerateSTART(I2Cx, ENABLE);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)){}

	I2C_Send7bitAddress(I2Cx, address, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)){}

	I2C_GenerateSTART(I2Cx, ENABLE);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)){}

	I2C_Send7bitAddress(I2Cx, address, I2C_Direction_Receiver);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)){}

	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)){}
	*data = I2C_ReceiveData(I2Cx);

	I2C_NACKPositionConfig(I2Cx, I2C_NACKPosition_Current);
	I2C_AcknowledgeConfig(I2C1, DISABLE);

	I2C_GenerateSTOP(I2Cx,ENABLE);
	while (I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF));
}

void I2C_receive_byte_from_reg(I2C_TypeDef* I2Cx,uint8_t address, uint8_t reg, uint8_t *data)
{
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	I2C_GenerateSTART(I2Cx, ENABLE);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)){}

	I2C_Send7bitAddress(I2Cx, address, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)){}

	I2C_TransmitData(I2Cx, reg);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)){}

	I2C_GenerateSTART(I2Cx, ENABLE);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)){}

	I2C_Send7bitAddress(I2Cx, address, I2C_Direction_Receiver);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)){}

	I2C_NACKPositionConfig(I2Cx, I2C_NACKPosition_Current);
	I2C_AcknowledgeConfig(I2Cx, DISABLE);

	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)){}
	*data = I2C_ReceiveData(I2Cx);

	I2C_GenerateSTOP(I2Cx,ENABLE);
	while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF));
}

void I2C_receive_byte_array_from_reg(I2C_TypeDef* I2Cx, uint8_t address, uint8_t reg, uint8_t *array, uint16_t size)
{
	I2C_GenerateSTART(I2Cx, ENABLE);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2Cx, address, I2C_Direction_Receiver);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	I2C_TransmitData(I2Cx, reg);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)){}

	I2C_GenerateSTART(I2Cx, ENABLE);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)){}

	I2C_Send7bitAddress(I2Cx, address, I2C_Direction_Receiver);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)){}

	I2C_NACKPositionConfig(I2Cx, I2C_NACKPosition_Current);
	I2C_AcknowledgeConfig(I2C1, DISABLE);

	while(size--)
	{
		while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)){}
		*array = I2C_ReceiveData(I2Cx);
		array++;
	}

	I2C_GenerateSTOP(I2Cx,ENABLE);
	while (I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF));

}

void I2C_send_byte_array_to_reg(I2C_TypeDef* I2Cx, uint8_t address, uint8_t reg, uint8_t *array, uint16_t size)
{
	while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY)){};

	I2C_GenerateSTART(I2Cx, ENABLE);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)){}

	I2C_Send7bitAddress(I2Cx, address, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)){}

	I2C_TransmitData(I2Cx, reg);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)){}

	while(size--)
	{
		I2C_TransmitData(I2Cx, *array++);
	}

	I2C_GenerateSTOP(I2Cx,ENABLE);
	while (I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF));

}


