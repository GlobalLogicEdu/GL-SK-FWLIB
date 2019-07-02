
#ifndef DRIVERS_INTERRUPTS_H_
#define DRIVERS_INTERRUPTS_H_

#include "stm32f4xx.h"

//void TimingDelay_Decrement(void);

void USART3_IRQHandler(void);

void EXTI0_IRQHandler(void);

void EXTI9_5_IRQHandler(void);

void EXTI15_10_IRQHandler(void);

void CAN2_RX0_IRQHandler(void);




#endif /* DRIVERS_INTERRUPTS_H_ */
