#ifndef DRIVERS_CAN_BUS_H_
#define DRIVERS_CAN_BUS_H_

#include "clock_config.h"
#include "peripheral_pinout.h"
#include "LEDs.h"
#include "USART.h"
#include <stdio.h>

#define CAN_MASSEGE_ID_REQ 	(0xA1)
#define CAN_MASSEGE_ID_RESP (0xA2)

void setup_CAN(void);

void CAN_BUS_init(void);

void CAN_transmit_data(void);

void CAN_receive_data(void);

void CAN_example(void);


#endif /* DRIVERS_CAN_BUS_H_ */
