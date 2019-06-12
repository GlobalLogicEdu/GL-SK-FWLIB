#include "glesk_uart.h"

int _write(int fd, char *str, int len)
{
	int ret;

	if (fd != 1) return -1;

	ret = uart_init(PRINTF_UART_NUM, PRINTF_UART_SPEED);
	if (ret < 0) return -1;

	ret = uart_write(PRINTF_UART_NUM, str, len);
	if (ret < 0) return -1;

	return len;
}

/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
