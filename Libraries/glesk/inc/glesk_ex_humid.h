#ifndef __GLESK_EX_HUMID_H__
#define __GLESK_EX_HUMID_H__

#include "glesk_common.h"

int ex_humid_init(void);
int ex_humid_read(u8 *humid, u8 *temp);

#endif // ifndef __GLESK_EX_HUMID_H__
