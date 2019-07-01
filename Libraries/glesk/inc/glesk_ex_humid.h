#ifndef __GLESK_EX_HUMID_H__
#define __GLESK_EX_HUMID_H__

#include "glesk_common.h"

int ex_humid_init(void);

// First byte - Decimal part of temp
// Second byte - Integral part of temp
// Third byte - Decimal part of humidity
// Fourth byte - Decimal part of humidity
// Fifth byte - Checksum = (First + Second + Third + Fourth)
int ex_humid_read(u8 *data, ssize_t len);

#endif // ifndef __GLESK_EX_HUMID_H__
